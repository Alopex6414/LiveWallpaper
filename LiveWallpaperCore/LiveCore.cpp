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
IDirect3DDevice9* g_pD3D9Device = NULL;		// D3D9�����豸
IDirect3DSurface9* g_pD3D9Surface = NULL;	// D3D9���Ʊ���

DirectGraphics* g_pMainGraphics = NULL;		// DirectGraphics��ʵ��
CCherryfps* g_pMainfps = NULL;				// CCherryfps��ʵ��

CLiveCoreThread g_cLiveCoreThread;			// CLiveCoreThread��ʵ��
CPlumThread* g_pPlumThread = NULL;			// CPlumThread��ָ��

CLiveCoreThread2 g_cLiveCoreThread2;		// CLiveCoreThread��ʵ��
CPlumThread* g_pPlumThread2 = NULL;			// CPlumThread��ָ��

CLiveCoreMonitor g_cLiveCoreMonitor;		// CLiveCoreMonitor��ʵ��
CPlumThread* g_pPlumMonitor = NULL;			// CPlumThread��ָ��

CPlumLog g_pPlumLogMain;					// CPlumLog��ʵ��

bool g_bReStart = false;
bool g_bMonitorFlag = false;
volatile bool g_bDecodeFlag = false;
CRITICAL_SECTION g_csDecode;				// CriticalSection�ٽ���

HWND g_hDeskTop = NULL;
int g_nDeskTopWidth = 0;
int g_nDeskTopHeight = 0;

int g_nVideoWidth = 0;
int g_nVideoHeight = 0;

unsigned char* g_pArrayY = NULL;
unsigned char* g_pArrayU = NULL;
unsigned char* g_pArrayV = NULL;

//------------------------------------------------------------------
// @Function:	 LiveWallpaperInit()
// @Purpose: LiveWallpaperCore��ʼ������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL LiveWallpaperInit()
{
	HRESULT hr;
	HWND hDeskTop = NULL;
	HWND hShellDefView = NULL;
	HWND hSysListView32 = NULL;

	// ��ʼ��PlumLog��־
	g_pPlumLogMain.PlumLogInit();

	// ��ȡ���洰�ڷֱ���
	g_nDeskTopWidth = GetSystemMetrics(SM_CXSCREEN);
	g_nDeskTopHeight = GetSystemMetrics(SM_CYSCREEN);

	// ���������߳�
	g_pPlumMonitor = new CPlumThread(&g_cLiveCoreMonitor);
	g_pPlumMonitor->PlumThreadInit();
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Start Monitor Thread.\n");

	// ִ�з�������ͼ��С����
	if (!LiveRunPreProcess())
	{
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Run Monitor PreProcess.\n");
		return FALSE;
	}
	
	g_pPlumMonitor->PlumThreadJoin();	// �ȴ�����ִ��
	if (g_pPlumMonitor)
	{
		g_pPlumMonitor->PlumThreadExit();
		SAFE_DELETE(g_pPlumMonitor);
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Monitor Thread Exit.\n");
	}

	// ��ȡ���洰�ھ��
	hDeskTop = FindWindowEx(GetDesktopWindow(), NULL, L"Progman", L"Program Manager");
	hShellDefView = FindWindowEx(hDeskTop, NULL, L"SHELLDLL_DefView", 0);
	hSysListView32 = FindWindowEx(hShellDefView, NULL, L"SysListView32", L"FolderView");

	g_hDeskTop = hDeskTop;
	SetParent(g_hWnd, g_hDeskTop);
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Set Window Handle.\n");

	// ���������ļ�
	AnalyzeConfigFile();
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Analyze Config File. Para:LiveCoreMode=%d, Para:LiveCoreShowGraphics=%d, Para:LiveCoreShowGraphicsFont=%d, "\
		"Para:LiveCoreWallpaperMode=%d, Para:LiveCoreWallpaperAudioMode=%d, Para:LiveCoreLogProcess=%d.\n", g_nLiveCoreMode, g_nLiveCoreShowGraphics, g_nLiveCoreShowGraphicsFont, g_nLiveCoreWallpaperMode, g_nLiveCoreWallpaperAudioMode, g_nLiveCoreLogProcess);

	// ���ģ������Ƿ����
	if (g_nLiveCoreMode == 0)
	{
		if (!IsProcessExist(L"LiveWallpaper.exe"))
		{
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Can not find LiveWallpaper.exe Process.\n");
			return FALSE;
		}
	}

	// ��ʼ��Direct3D
	g_pMainGraphics = new DirectGraphics;
	hr = g_pMainGraphics->DirectGraphicsInit(g_hWnd, true, g_nDeskTopWidth, g_nDeskTopHeight);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Init Direct3D Graphics.\n");
		return FALSE;
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Direct3D Graphics.\n");

	// �Ƿ���ʾ�Կ��ͺź�֡����(Debug Mode)
	if (g_nLiveCoreShowGraphics != 0)
	{
		// ��ʼ��Direct3DFont
		hr = g_pMainGraphics->DirectGraphicsFontInit(g_nLiveCoreShowGraphicsFont);
		if (FAILED(hr))
		{
			MessageBox(g_hWnd, _T("Direct3DFont��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
			g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Init Direct3D Font.\n");
			return FALSE;
		}
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Direct3D Font.\n");
	}

	g_pD3D9Device = g_pMainGraphics->DirectGraphicsGetDevice();	// ��ȡD3D9�����豸

	// ������Ƶ��Ϣ
	if (!AnalyzeVideoInfo(g_hWnd, g_chLiveCoreVideoAddress, &g_nVideoWidth, &g_nVideoHeight))
	{
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Analyze Video Infomation.\n");
		return FALSE;
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Analyze Video Infomation.\n");
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Para:VideoWidth=%d, Para:VideoHeight=%d.\n", g_nVideoWidth, g_nVideoHeight);

	// ��ʼ��Direct3DSurface
	hr = g_pD3D9Device->CreateOffscreenPlainSurface(g_nVideoWidth, g_nVideoHeight, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), D3DPOOL_DEFAULT, &g_pD3D9Surface, NULL);
	if (hr)
	{
		MessageBox(g_hWnd, L"Direct3DSurface��ʼ��ʧ��!", L"����", MB_OK | MB_ICONERROR);
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Fail Init Direct3D Surface.\n");
		return FALSE;
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Direct3D Surface.\n");

	// ��ʼ��CherryFPS
	if (g_nLiveCoreShowGraphics != 0)
	{
		g_pMainfps = new CCherryfps(g_pD3D9Device);
		g_pMainfps->CherryfpsInit(g_nLiveCoreShowGraphicsFont, (LPWSTR)_T("Consolas"));
		g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Cherry FPS.\n");
	}

	// ��ʼ���ٽ���
	InitializeCriticalSection(&g_csDecode);
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Critical Section.\n");

	g_pPlumThread = new CPlumThread(&g_cLiveCoreThread);
	g_pPlumThread->PlumThreadInit();
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Succeed Init Decode Thread.\n");

	//g_pPlumThread2 = new CPlumThread(&g_cLiveCoreThread2);
	//g_pPlumThread2->PlumThreadInit();

	return TRUE;
}


//------------------------------------------------------------------
// @Function:	 LiveWallpaperRelease()
// @Purpose: LiveWallpaperCore�ͷ���Դ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LiveWallpaperRelease()
{
	// ɾ���ٽ���
	DeleteCriticalSection(&g_csDecode);

	SAFE_DELETE_ARRAY(g_pArrayY);
	SAFE_DELETE_ARRAY(g_pArrayU);
	SAFE_DELETE_ARRAY(g_pArrayV);

	if (g_pPlumThread2)
	{
		g_pPlumThread2->PlumThreadExit();
		SAFE_DELETE(g_pPlumThread2);
	}

	if (g_pPlumThread)
	{
		g_pPlumThread->PlumThreadExit();
		SAFE_DELETE(g_pPlumThread);
	}
	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Decode Thread Exit.\n");

	SAFE_DELETE(g_pMainfps);
	SAFE_DELETE(g_pMainGraphics);

	g_pPlumLogMain.PlumLogWriteExtend(__FILE__, __LINE__, "Process Exit.\n");
	g_pPlumLogMain.PlumLogExit();
}


//------------------------------------------------------------------
// @Function:	 LiveWallpaperUpdate()
// @Purpose: LiveWallpaperCoreͬ������
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
// @Purpose: LiveWallpaperCore��Ⱦ����
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

		if (g_nLiveCoreWallpaperMode == 0) // ���ģʽ
		{
			DestRect.left = 0;
			DestRect.top = 0;
			DestRect.right = g_nDeskTopWidth;
			DestRect.bottom = g_nDeskTopHeight;
		}
		else if (g_nLiveCoreWallpaperMode == 1) // ��Ӧģʽ
		{
			float fVideoRate = 0.0f;
			float fScreenRate = 0.0f;

			fVideoRate = (float)g_nVideoWidth / (float)g_nVideoHeight;
			fScreenRate = (float)g_nDeskTopWidth / (float)g_nDeskTopHeight;

			if (fVideoRate >= fScreenRate)
			{
				DestRect.left = 0;
				DestRect.right = g_nDeskTopWidth;
				DestRect.top = (int)((float)g_nDeskTopWidth / (fVideoRate * 2.0f));
				DestRect.bottom = DestRect.top + (int)((float)g_nDeskTopWidth / fVideoRate);
			}
			else
			{
				DestRect.left = (int)((float)g_nDeskTopHeight * fVideoRate / 2.0f);
				DestRect.right = DestRect.left + (int)((float)g_nDeskTopHeight * fVideoRate);
				DestRect.top = 0;
				DestRect.bottom = g_nDeskTopHeight;
			}
		}
		else if (g_nLiveCoreWallpaperMode == 2)	// ����ģʽ
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
		else if (g_nLiveCoreWallpaperMode == 3)	// ƽ��ģʽ(��δ���)
		{
			DestRect.left = 0;
			DestRect.top = 0;
			DestRect.right = g_nDeskTopWidth;
			DestRect.bottom = g_nDeskTopHeight;
		}
		else if (g_nLiveCoreWallpaperMode == 4)	// ����ģʽ(ԭʼ�ߴ�)
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