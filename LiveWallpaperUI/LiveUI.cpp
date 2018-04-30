/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveUI.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-27
*/
#include "LiveUI.h"
#include "WinProcess.h"
#include "WinUtilities.h"

// LiveWallpaperUI 窗口类
#define LIVEUI_TIMER_ALPHA		0
#define LIVEUI_TIMER_REPAINT	1

CLiveUI g_cLiveUI;
CLiveUI* g_pLiveUI;

//------------------------------------------------------------------
// @Function:	 CLiveUI()
// @Purpose: CLiveUI构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveUI::CLiveUI()
{
	ConstructExtra();
}

//------------------------------------------------------------------
// @Function:	 ~CLiveUI()
// @Purpose: CLiveUI析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveUI::~CLiveUI()
{
	DestructExtra();
}

//------------------------------------------------------------------
// @Function:	 ConstructExtra()
// @Purpose: CLiveUI构造窗口资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::ConstructExtra()
{
	g_pLiveUI = this;
	m_nWindowAlpha = 0;
	m_bWindowState = false;
	m_bWindowClosed = false;
	m_bWindowClosing = false;

	m_pLiveLua = NULL;
	m_nAnimationAlphaMin = 0;
	m_nAnimationAlphaMax = 255;
	m_nAnimationAlphaStep = 1;
}

//------------------------------------------------------------------
// @Function:	 DestructExtra()
// @Purpose: CLiveUI析构窗口资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::DestructExtra()
{
	if (m_pLiveLua)
	{
		delete m_pLiveLua;
		m_pLiveLua = NULL;
	}
}

//------------------------------------------------------------------
// @Function:	 InitWindowExtra()
// @Purpose: CLiveUI初始化窗口资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveUI::InitWindowExtra()
{
	BOOL bRet = FALSE;

	//初始化Lua
	m_pLiveLua = new CLiveLua("script\\LiveUI.lua");
	bRet = m_pLiveLua->LiveLuaInit();
	if (!bRet)
	{
		return FALSE;
	}

	//获取Lua配置
	m_pLiveLua->LiveLuaGetGlobalInt("Animation_Alpha_Min", m_nAnimationAlphaMin);
	m_pLiveLua->LiveLuaGetGlobalInt("Animation_Alpha_Max", m_nAnimationAlphaMax);
	m_pLiveLua->LiveLuaGetGlobalInt("Animation_Alpha_Step", m_nAnimationAlphaStep);

	//修改窗口样式
	::SetWindowLong(g_hWnd, GWL_EXSTYLE, ::GetWindowLong(g_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetTimer(g_hWnd, LIVEUI_TIMER_ALPHA, 10, NULL);

	//重绘窗口定时器
	SetTimer(g_hWnd, LIVEUI_TIMER_REPAINT, 10, NULL);

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 ReleaseWindowExtra()
// @Purpose: CLiveUI释放窗口资源
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::ReleaseWindowExtra()
{

}

//------------------------------------------------------------------
// @Function:	 RePaintWindow()
// @Purpose: CLiveUI窗口重绘
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::RePaintWindow()
{
	HDC hDC;
	HDC hMemDC;
	HBITMAP hBitmap;
	HBRUSH hBrush;
	RECT Rect;
	int nWidth;
	int nHeight;

	GetClientRect(g_hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	hDC = GetDC(g_hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	hBitmap = CreateCompatibleBitmap(hMemDC, nWidth, nHeight);

	hBrush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hMemDC, hBrush);
	SelectObject(hMemDC, hBitmap);
	FillRect(hMemDC, &Rect, hBrush);

	BitBlt(hDC, 0, 0, USER_SCREENWIDTH, USER_SCREENHEIGHT, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(hBrush);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(g_hWnd, hDC);
}


//------------------------------------------------------------------
// @Function:	 ShowWindowAlpha()
// @Purpose: CLiveUI窗口Alpha变化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::ShowWindowAlpha(bool& bState, int& nAlpha)
{
	if (!bState)
	{
		nAlpha += m_nAnimationAlphaStep;
		if (nAlpha > 255)
		{
			nAlpha = 255;
			KillTimer(g_hWnd, LIVEUI_TIMER_ALPHA);
		}
	}
	else
	{
		nAlpha -= m_nAnimationAlphaStep;
		if (nAlpha < 0)
		{
			nAlpha = 0;
			KillTimer(g_hWnd, LIVEUI_TIMER_ALPHA);
			m_bWindowClosed = true;
			::PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
	}

	SetLayeredWindowAttributes(g_hWnd, 0, nAlpha, LWA_ALPHA);
}

//==================================================================
// ~消息响应
//==================================================================

//------------------------------------------------------------------
// @Function:	 OnTimer()
// @Purpose: CLiveUI定时器响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnTimer(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case LIVEUI_TIMER_ALPHA:
		ShowWindowAlpha(m_bWindowState, m_nWindowAlpha);
		break;
	case LIVEUI_TIMER_REPAINT:
		RePaintWindow();
		break;
	default:
		break;
	}

	return DefWindowProc(g_hWnd, WM_TIMER, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnClose()
// @Purpose: CLiveUI窗口关闭响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnClose(WPARAM wParam, LPARAM lParam)
{
	LRESULT lr = 0;

	if (!m_bWindowClosed)
	{
		if (!m_bWindowClosing)
		{
			m_bWindowState = true;
			m_bWindowClosing = true;
			SetTimer(g_hWnd, LIVEUI_TIMER_ALPHA, 10, NULL);
		}
	}
	else
	{
		lr = DefWindowProc(g_hWnd, WM_CLOSE, wParam, lParam);
	}

	return lr;
}

//------------------------------------------------------------------
// @Function:	 OnMouseMove()
// @Purpose: CLiveUI鼠标移动响应
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(g_hWnd, WM_MOUSEMOVE, wParam, lParam);
}