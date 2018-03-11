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
#include "LiveCoreFunction.h"

#include "WinProcess.h"
#include "WinUtilities.h"

#include "DirectCommon.h"
#include "DirectGraphics.h"
#include "DirectSurface.h"
#include "DirectThreadSafe.h"
#include "Cherryfps.h"

// Variable Definition
IDirect3DDevice9* g_pD3D9Device = NULL;		// D3D9�����豸
IDirect3DSurface9* g_pD3D9Surface = NULL;	// D3D9���Ʊ���

DirectGraphics* g_pMainGraphics = NULL;		// DirectGraphics��ʵ��
CCherryfps* g_pMainfps = NULL;				// CCherryfps��ʵ��

CLiveCoreThread g_cLiveCoreThread;			// CLiveCoreThread��ʵ��
CPlumThread* g_pPlumThread = NULL;			// CPlumThread��ָ��

bool g_bReStart = false;
bool g_bDecodeFlag = false;
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

	// ��ȡ���洰�ڷֱ���
	g_nDeskTopWidth = GetSystemMetrics(SM_CXSCREEN);
	g_nDeskTopHeight = GetSystemMetrics(SM_CYSCREEN);

	// ִ�з�������ͼ��С����
	if (!LiveRunPreProcess())
	{
		return FALSE;
	}
	
	Sleep(1000);	// �ȴ�����ִ��

	// ��ȡ���洰�ھ��
	hDeskTop = FindWindowEx(GetDesktopWindow(), NULL, L"Progman", L"Program Manager");
	hShellDefView = FindWindowEx(hDeskTop, NULL, L"SHELLDLL_DefView", 0);
	hSysListView32 = FindWindowEx(hShellDefView, NULL, L"SysListView32", L"FolderView");

	g_hDeskTop = hDeskTop;
	SetParent(g_hWnd, g_hDeskTop);

	// ���������ļ�
	AnalyzeConfigFile();

	// ���ģ������Ƿ����
	if (g_nLiveCoreMode == 0)
	{
		if (!IsProcessExist(L"LiveWallpaper.exe"))
		{
			return FALSE;
		}
	}

	// ��ʼ��Direct3D
	g_pMainGraphics = new DirectGraphics;
	hr = g_pMainGraphics->DirectGraphicsInit(g_hWnd, true, g_nDeskTopWidth, g_nDeskTopHeight);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// �Ƿ���ʾ�Կ��ͺź�֡����(Debug Mode)
	if (g_nLiveCoreShowGraphics != 0)
	{
		// ��ʼ��Direct3DFont
		hr = g_pMainGraphics->DirectGraphicsFontInit(g_nLiveCoreShowGraphicsFont);
		if (FAILED(hr))
		{
			MessageBox(g_hWnd, _T("Direct3DFont��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}

	g_pD3D9Device = g_pMainGraphics->DirectGraphicsGetDevice();	// ��ȡD3D9�����豸

	// ������Ƶ��Ϣ
	if (!AnalyzeVideoInfo(g_hWnd, g_chLiveCoreVideoAddress, &g_nVideoWidth, &g_nVideoHeight))
	{
		return FALSE;
	}

	// ��ʼ��Direct3DSurface
	hr = g_pD3D9Device->CreateOffscreenPlainSurface(g_nVideoWidth, g_nVideoHeight, (D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'), D3DPOOL_DEFAULT, &g_pD3D9Surface, NULL);
	if (hr)
	{
		MessageBox(g_hWnd, L"Direct3DSurface��ʼ��ʧ��!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// ��ʼ��CherryFPS
	if (g_nLiveCoreShowGraphics != 0)
	{
		g_pMainfps = new CCherryfps(g_pD3D9Device);
		g_pMainfps->CherryfpsInit(g_nLiveCoreShowGraphicsFont, (LPWSTR)_T("Consolas"));
	}

	// ��ʼ���ٽ���
	InitializeCriticalSection(&g_csDecode);

	g_pPlumThread = new CPlumThread(&g_cLiveCoreThread);
	g_pPlumThread->PlumThreadInit();

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

	if (g_pPlumThread)
	{
		g_pPlumThread->PlumThreadExit();
		SAFE_DELETE(g_pPlumThread);
	}

	SAFE_DELETE(g_pMainfps);
	SAFE_DELETE(g_pMainGraphics);
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

		DestRect.left = 0;
		DestRect.top = 0;
		DestRect.right = g_nDeskTopWidth;
		DestRect.bottom = g_nDeskTopHeight;

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
	}
}