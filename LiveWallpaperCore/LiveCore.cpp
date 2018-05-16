/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCore.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-11-29
*/
#include "LiveCore.h"
#include "LiveCoreThread.h"
#include "LiveCoreThread2.h"
#include "LiveCoreMonitor.h"
#include "LiveCoreUnpackThread.h"
#include "LiveCoreWaitThread.h"
#include "LiveCoreFunction.h"

#include "WinProcess.h"
#include "WinUtilities.h"

#include "DirectCommon.h"
#include "DirectGraphics.h"
#include "DirectSurface.h"
#include "DirectThreadSafe.h"
#include "Cherryfps.h"

#include "PlumLog.h"

// Variable Definition
IDirect3DDevice9* g_pD3D9Device = NULL;		// D3D9绘制设备
IDirect3DSurface9* g_pD3D9Surface = NULL;	// D3D9绘制表面

DirectGraphics* g_pMainGraphics = NULL;		// DirectGraphics类实例
CCherryfps* g_pMainfps = NULL;				// CCherryfps类实例

CLiveCoreThread g_cLiveCoreThread;			// CLiveCoreThread类实例
CPlumThread* g_pPlumThread = NULL;			// CPlumThread类指针

CLiveCoreThread2 g_cLiveCoreThread2;		// CLiveCoreThread类实例
CPlumThread* g_pPlumThread2 = NULL;			// CPlumThread类指针

CLiveCoreMonitor g_cLiveCoreMonitor;		// CLiveCoreMonitor类实例
CPlumThread* g_pPlumMonitor = NULL;			// CPlumThread类指针

CLiveCoreUnpackThread g_cLiveCoreUnpack;	// CLiveCoreMonitor类实例
CPlumThread* g_pPlumUnpack = NULL;			// CPlumThread类指针

CLiveCoreWaitThread g_cLiveCoreWait;		// CLiveCoreWait类实例
CPlumThread* g_pPlumWait = NULL;			// CPlumThread类指针

CPlumLog g_pPlumLogMain;					// CPlumLog类实例

bool g_bReStart = false;
bool g_bMonitorFlag = false;
volatile bool g_bDecodeFlag = false;
CRITICAL_SECTION g_csDecode;				// CriticalSection临界区

volatile bool g_bWaitFlag = false;
CRITICAL_SECTION g_csWait;					// CriticalSection临界区

int g_nDeskTopWidth = 0;
int g_nDeskTopHeight = 0;

int g_nVideoWidth = 0;
int g_nVideoHeight = 0;

int g_nVideoFreq = 0;						// Video freq

char g_chDefaultVideoAddress[MAX_PATH] = { 0 };
char g_chDefaultVideoDirector[MAX_PATH] = { 0 };
char g_chDefaultVideoUnpack[MAX_PATH] = { 0 };

unsigned char* g_pArrayY = NULL;
unsigned char* g_pArrayU = NULL;
unsigned char* g_pArrayV = NULL;

//------------------------------------------------------------------
// @Function:	 LiveWallpaperInit()
// @Purpose: LiveWallpaperCore初始化函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL LiveWallpaperInit()
{
	HRESULT hr;

	// 初始化PlumLog日志
	g_pPlumLogMain.PlumLogInit();

	// 获取桌面窗口分辨率
	g_nDeskTopWidth = GetSystemMetrics(SM_CXSCREEN);
	g_nDeskTopHeight = GetSystemMetrics(SM_CYSCREEN);

	// 分析配置文件
	AnalyzeConfigFile();
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Analyze Config File. Para:LiveCoreMode=%d, Para:LiveCoreShowGraphics=%d, Para:LiveCoreShowGraphicsFont=%d, "\
		"Para:LiveCoreWallpaperMode=%d, Para:LiveCoreWallpaperAudioMode=%d, Para:LiveCoreLogProcess=%d.\n", g_nLiveCoreMode, g_nLiveCoreShowGraphics, g_nLiveCoreShowGraphicsFont, g_nLiveCoreWallpaperMode, g_nLiveCoreWallpaperAudioMode, g_nLiveCoreLogProcess);

	// 记录配置文件
	RecordConfigFile();

	// 检测模块进程是否存在
	if (g_nLiveCoreMode == 0)
	{
		if (!IsProcessExist(L"LiveWallpaperUI.exe"))
		{
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Can not find LiveWallpaperUI.exe Process.\n");
			return FALSE;
		}
	}

	// 初始化等待线程临界区
	InitializeCriticalSection(&g_csWait);

	// 是否启用默认视频
	if (g_nLiveCoreVideoMode == 0)
	{
		char* pTemp = NULL;

		GetModuleFileNameA(NULL, g_chDefaultVideoDirector, MAX_PATH);
		pTemp = strrchr(g_chDefaultVideoDirector, '\\');
		if (pTemp) *pTemp = '\0';
		strcat_s(g_chDefaultVideoDirector, "\\data\\");

		memcpy_s(g_chDefaultVideoAddress, MAX_PATH, g_chDefaultVideoDirector, MAX_PATH);
		strcat_s(g_chDefaultVideoAddress, g_chLiveCoreVideoName);

		g_bWaitFlag = true;	// 等待标识...

		// 开启等待线程
		g_pPlumWait = new CPlumThread(&g_cLiveCoreWait);
		g_pPlumWait->PlumThreadInit();
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Start Wait Thread.\n");

		// 开启解包线程
		g_pPlumUnpack = new CPlumThread(&g_cLiveCoreUnpack);
		g_pPlumUnpack->PlumThreadInit();
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Start Unpack Thread.\n");

		g_pPlumUnpack->PlumThreadJoin();	// 等待进程执行
		if (g_pPlumUnpack)
		{
			g_pPlumUnpack->PlumThreadExit();
			SAFE_DELETE(g_pPlumUnpack);
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Unpack Thread Exit.\n");
		}

		ZeroMemory(g_chLiveCoreVideoAddress, MAX_PATH);
		memcpy_s(g_chLiveCoreVideoAddress, MAX_PATH, g_chDefaultVideoUnpack, MAX_PATH);

		EnterCriticalSection(&g_csWait);
		g_bWaitFlag = false;
		LeaveCriticalSection(&g_csWait);

		g_pPlumWait->PlumThreadJoin();	// 等待进程执行
		if (g_pPlumWait)
		{
			g_pPlumWait->PlumThreadExit();
			SAFE_DELETE(g_pPlumWait);
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Wait Thread Exit.\n");
		}
	}

	// 开启监视线程
	g_pPlumMonitor = new CPlumThread(&g_cLiveCoreMonitor);
	g_pPlumMonitor->PlumThreadInit();
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Start Monitor Thread.\n");

	// 执行分离桌面图标小程序
	if (!LiveRunPreProcess())
	{
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Run Monitor PreProcess.\n");
		return FALSE;
	}
	
	g_pPlumMonitor->PlumThreadJoin();	// 等待进程执行
	if (g_pPlumMonitor)
	{
		g_pPlumMonitor->PlumThreadExit();
		SAFE_DELETE(g_pPlumMonitor);
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Monitor Thread Exit.\n");
	}

	// 设置动态壁纸窗口
	LiveCoreSetChildWindow(g_hWnd);
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Set Window Handle.\n");

	// 初始化Direct3D
	g_pMainGraphics = new DirectGraphics;
	hr = g_pMainGraphics->DirectGraphicsInit(g_hWnd, true, g_nDeskTopWidth, g_nDeskTopHeight);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Init Direct3D Graphics.\n");
		return FALSE;
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Direct3D Graphics.\n");

	// 是否显示显卡型号和帧速率(Debug Mode)
	if (g_nLiveCoreShowGraphics != 0)
	{
		// 初始化Direct3DFont
		hr = g_pMainGraphics->DirectGraphicsFontInit(g_nLiveCoreShowGraphicsFont);
		if (FAILED(hr))
		{
			MessageBox(g_hWnd, _T("Direct3DFont初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Init Direct3D Font.\n");
			return FALSE;
		}
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Direct3D Font.\n");
	}

	g_pD3D9Device = g_pMainGraphics->DirectGraphicsGetDevice();	// 获取D3D9绘制设备

	// 分析视频信息
	if (!AnalyzeVideoInfo(g_hWnd, g_chLiveCoreVideoAddress, &g_nVideoWidth, &g_nVideoHeight, &g_nVideoFreq))
	{
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Analyze Video Infomation.\n");
		return FALSE;
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Analyze Video Infomation.\n");
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Para:VideoWidth=%d, Para:VideoHeight=%d, Para:VideoFreq=%d.\n", g_nVideoWidth, g_nVideoHeight, g_nVideoFreq);

	if (g_nVideoFreq == 0)
	{
		g_nVideoFreq = 60;	// fps!=0
	}

	// 初始化Direct3DSurface
	hr = g_pD3D9Device->CreateOffscreenPlainSurface(g_nVideoWidth, g_nVideoHeight, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), D3DPOOL_DEFAULT, &g_pD3D9Surface, NULL);
	if (hr)
	{
		MessageBox(g_hWnd, L"Direct3DSurface初始化失败!", L"错误", MB_OK | MB_ICONERROR);
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Init Direct3D Surface.\n");
		return FALSE;
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Direct3D Surface.\n");

	// 初始化CherryFPS
	if (g_nLiveCoreShowGraphics != 0)
	{
		g_pMainfps = new CCherryfps(g_pD3D9Device);
		g_pMainfps->CherryfpsInit(g_nLiveCoreShowGraphicsFont, (LPWSTR)_T("Consolas"));
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Cherry FPS.\n");
	}

	// 初始化临界区
	InitializeCriticalSection(&g_csDecode);
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Critical Section.\n");

	g_pPlumThread = new CPlumThread(&g_cLiveCoreThread);
	g_pPlumThread->PlumThreadInit();
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Decode Video Thread.\n");

	// 播放视频音频
	if (g_nLiveCoreWallpaperAudioMode != 0)
	{
		g_pPlumThread2 = new CPlumThread(&g_cLiveCoreThread2);
		g_pPlumThread2->PlumThreadInit();
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Decode Audio Thread.\n");
	}

	return TRUE;
}


//------------------------------------------------------------------
// @Function:	 LiveWallpaperRelease()
// @Purpose: LiveWallpaperCore释放资源函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LiveWallpaperRelease()
{
	// 删除临界区
	DeleteCriticalSection(&g_csWait);
	DeleteCriticalSection(&g_csDecode);

	SAFE_DELETE_ARRAY(g_pArrayY);
	SAFE_DELETE_ARRAY(g_pArrayU);
	SAFE_DELETE_ARRAY(g_pArrayV);

	if (g_nLiveCoreWallpaperAudioMode != 0)
	{
		if (g_pPlumThread2)
		{
			g_pPlumThread2->PlumThreadExit();
			SAFE_DELETE(g_pPlumThread2);
		}
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Decode Audio Thread Exit.\n");
	}

	if (g_pPlumThread)
	{
		g_pPlumThread->PlumThreadExit();
		SAFE_DELETE(g_pPlumThread);
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Decode Video Thread Exit.\n");

	SAFE_DELETE(g_pMainfps);
	SAFE_DELETE(g_pMainGraphics);

	if (g_nLiveCoreVideoMode == 0)
	{
		LiveCoreCleanUp(g_chDefaultVideoUnpack);
	}

	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Process Exit.\n");
	g_pPlumLogMain.PlumLogExit();
}


//------------------------------------------------------------------
// @Function:	 LiveWallpaperUpdate()
// @Purpose: LiveWallpaperCore同步函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LiveWallpaperUpdate()
{
	D3DLOCKED_RECT Rect;

	if (g_bDecodeFlag)
	{
		HRESULT hr;

		if (!g_bActive)
		{
			Sleep(50);
		}

		EnterCriticalSection(&g_csDecode);
		hr = g_pMainGraphics->DirectGraphicsTestCooperativeLevel();
		if (hr != S_OK)
		{
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Direct3D Lost Device!\n");
			if (hr == D3DERR_DEVICELOST)
			{
				LeaveCriticalSection(&g_csDecode);
				return;
			}

			if (hr == D3DERR_DEVICENOTRESET)
			{
				IDirect3DSurface9* pD3D9BackBuffer = NULL;

				if (g_nLiveCoreShowGraphics != 0)
				{
					g_pMainGraphics->DirectGraphicsReset();
					g_pMainfps->CherryfpsReset();
				}

				g_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer);
				SAFE_RELEASE(pD3D9BackBuffer);
				SAFE_RELEASE(g_pD3D9Surface);

				g_pMainGraphics->DirectGraphicsResetDevice();

				g_pD3D9Device->CreateOffscreenPlainSurface(g_nVideoWidth, g_nVideoHeight, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), D3DPOOL_DEFAULT, &g_pD3D9Surface, NULL);
				g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Direct3D Reset Device!\n");
			}
		}

		g_pD3D9Surface->LockRect(&Rect, 0, 0);
		for (int i = 0; i < g_nVideoHeight; ++i)
		{
			memcpy((BYTE*)(Rect.pBits) + i * Rect.Pitch, (BYTE*)g_pArrayY + i * g_nVideoWidth, g_nVideoWidth);
		}
		for (int i = 0; i < g_nVideoHeight / 2; ++i)
		{
			memcpy((BYTE*)(Rect.pBits) + Rect.Pitch * g_nVideoHeight + (Rect.Pitch / 2) * i, (BYTE*)g_pArrayV + i * g_nVideoWidth / 2, g_nVideoWidth / 2);
		}
		for (int i = 0; i < g_nVideoHeight / 2; ++i)
		{
			memcpy((BYTE*)(Rect.pBits) + Rect.Pitch * g_nVideoHeight + Rect.Pitch * g_nVideoHeight / 4 + (Rect.Pitch / 2) * i, (BYTE*)g_pArrayU + i * g_nVideoWidth / 2, g_nVideoWidth / 2);
		}
		g_pD3D9Surface->UnlockRect();

		g_bReStart = true;
		g_bDecodeFlag = false;

		if (g_nLiveCoreLogProcess)
		{
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Direct3D Update One frame.\n");
		}

		LeaveCriticalSection(&g_csDecode);
	}
}


//------------------------------------------------------------------
// @Function:	 LiveWallpaperRender()
// @Purpose: LiveWallpaperCore渲染函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LiveWallpaperRender()
{
	IDirect3DSurface9* pD3D9BackBuffer = NULL;
	RECT SrcRect;
	RECT DestRect;

	if (g_bReStart)
	{
		g_pMainGraphics->DirectGraphicsBegin();

		SrcRect.left = 0;
		SrcRect.top = 0;
		SrcRect.right = g_nVideoWidth;
		SrcRect.bottom = g_nVideoHeight;

		if (g_nLiveCoreWallpaperMode == 0) // 填充模式
		{
			DestRect.left = 0;
			DestRect.top = 0;
			DestRect.right = g_nDeskTopWidth;
			DestRect.bottom = g_nDeskTopHeight;
		}
		else if (g_nLiveCoreWallpaperMode == 1) // 适应模式
		{
			float fVideoRate = 0.0f;
			float fScreenRate = 0.0f;

			fVideoRate = (float)g_nVideoWidth / (float)g_nVideoHeight;
			fScreenRate = (float)g_nDeskTopWidth / (float)g_nDeskTopHeight;

			if (fVideoRate >= fScreenRate)
			{
				DestRect.left = 0;
				DestRect.right = g_nDeskTopWidth;
				DestRect.top = (int)(((float)g_nDeskTopHeight - (float)g_nDeskTopWidth / fVideoRate) / 2.0f);
				DestRect.bottom = DestRect.top + (int)((float)g_nDeskTopWidth / fVideoRate);
			}
			else
			{
				DestRect.left = (int)(((float)g_nDeskTopWidth - (float)g_nDeskTopHeight * fVideoRate) / 2.0f);
				DestRect.right = DestRect.left + (int)((float)g_nDeskTopHeight * fVideoRate);
				DestRect.top = 0;
				DestRect.bottom = g_nDeskTopHeight;
			}
		}
		else if (g_nLiveCoreWallpaperMode == 2)	// 拉伸模式
		{
			float fVideoRate = 0.0f;
			float fScreenRate = 0.0f;

			fVideoRate = (float)g_nVideoWidth / (float)g_nVideoHeight;
			fScreenRate = (float)g_nDeskTopWidth / (float)g_nDeskTopHeight;

			if (fVideoRate >= fScreenRate)
			{
				DestRect.left = (int)(((float)g_nDeskTopWidth - (float)g_nDeskTopHeight * fVideoRate) / 2.0f);
				DestRect.right = DestRect.left + (int)((float)g_nDeskTopHeight * fVideoRate);
				DestRect.top = 0;
				DestRect.bottom = g_nDeskTopHeight;
			}
			else
			{
				DestRect.left = 0;
				DestRect.right = g_nDeskTopWidth;
				DestRect.top = (int)(((float)g_nDeskTopHeight - (float)g_nDeskTopWidth / fVideoRate) / 2.0f);
				DestRect.bottom = DestRect.top + (int)((float)g_nDeskTopWidth / fVideoRate);
			}
		}
		else if (g_nLiveCoreWallpaperMode == 3)	// 平铺模式(暂未完成)
		{
			DestRect.left = 0;
			DestRect.top = 0;
			DestRect.right = g_nDeskTopWidth;
			DestRect.bottom = g_nDeskTopHeight;
		}
		else if (g_nLiveCoreWallpaperMode == 4)	// 居中模式(原始尺寸)
		{
			if (g_nDeskTopWidth >= g_nVideoWidth && g_nDeskTopHeight >= g_nVideoHeight)
			{
				DestRect.left = (g_nDeskTopWidth - g_nVideoWidth) >> 1;
				DestRect.top = (g_nDeskTopHeight - g_nVideoHeight) >> 1;
				DestRect.right = DestRect.left + g_nVideoWidth;
				DestRect.bottom = DestRect.top + g_nVideoHeight;
			}
		}

		g_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer);
		g_pD3D9Device->StretchRect(g_pD3D9Surface, &SrcRect, pD3D9BackBuffer, &DestRect, D3DTEXF_NONE);

		if (g_nLiveCoreShowGraphics != 0)
		{
			g_pMainfps->CherryfpsGetfps();
			g_pMainfps->CherryfpsDrawfps(g_hWnd, DIRECTFONT_FORMAT_TOPRIGHT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
			g_pMainGraphics->DirectGraphicsFontDrawText(g_hWnd);
		}

		g_pMainGraphics->DirectGraphicsEnd();
		SAFE_RELEASE(pD3D9BackBuffer);

		EnterCriticalSection(&g_csDecode);
		if (g_nLiveCoreLogProcess)
		{
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Direct3D Render One frame.\n");
		}
		LeaveCriticalSection(&g_csDecode);

	}
}