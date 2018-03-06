/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		Cherryfps.cpp
* @brief	This File is Cherryfps DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-1	v1.00a	alopex	Create This File
*/
#include "DirectCommon.h"
#include "DirectFont.h"
#include "Cherryfps.h"

//Cherryfps类用于绘制和显示当前游戏帧速率(fps)

//------------------------------------------------------------------
// @Function:	 CCherryfps()
// @Purpose: CCherryfps构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCherryfps::CCherryfps()
{
	m_pFont = NULL;
	m_fps = 0.0f;
}

//------------------------------------------------------------------
// @Function:	 ~CCherryfps()
// @Purpose: CCherryfps析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CCherryfps::~CCherryfps()
{
	SAFE_DELETE(m_pFont);
}

//------------------------------------------------------------------
// @Function:	 CCherryfps(IDirect3DDevice9* pD3D9Device)
// @Purpose: CCherryfps构造函数
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D绘制设备
// @Return: None
//------------------------------------------------------------------
CCherryfps::CCherryfps(IDirect3DDevice9* pD3D9Device)
{
	m_pFont = new DirectFont(pD3D9Device);
	m_fps = 0.0f;
}

//------------------------------------------------------------------
// @Function:	 CherryfpsInit(int nFontSize, LPWSTR lpszFontType)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//------------------------------------------------------------------
void CCherryfps::CherryfpsInit(int nFontSize, LPWSTR lpszFontType)
{
	m_pFont->DirectFontInit(nFontSize, lpszFontType);
}

//------------------------------------------------------------------
// @Function:	 CherryfpsGetfps(void)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CCherryfps::CherryfpsGetfps(void)
{
	static int FrameCount = 0;
	static DWORD TimeLast = 0;
	DWORD TimeCurrent = 0;
	float TimeElapsed = 0.0f;

	FrameCount++;
	timeBeginPeriod(1);
	TimeCurrent = timeGetTime();
	timeEndPeriod(1);
	TimeElapsed = (TimeCurrent - TimeLast) * 0.001f;

	if (TimeElapsed >= 1.0f)
	{
		m_fps = (float)(FrameCount * 1.0f / TimeElapsed);
		TimeLast = TimeCurrent;
		FrameCount = 0;
	}
}

//------------------------------------------------------------------
// @Function:	 CherryfpsGetfpsEx(float fTimeDelta, float* pfps)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: float fTimeDelta		//时间间隔(ms)
// @Para: float* pfps			//帧速率fps
// @Return: None
//------------------------------------------------------------------
void CCherryfps::CherryfpsGetfpsEx(float fTimeDelta, float* pfps)
{
	static int FrameCount = 0;
	static float TimeElapsed = 0.0f;

	FrameCount++;
	TimeElapsed += fTimeDelta;

	if (TimeElapsed >= 1.0f)
	{
		*pfps = (float)(FrameCount * 1.0f / TimeElapsed);
		FrameCount = 0;
		TimeElapsed = 0.0f;
	}
}

//------------------------------------------------------------------
// @Function:	 CherryfpsGetfpsEx(float* pfps)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: float* pfps			//帧速率fps
// @Return: None
//------------------------------------------------------------------
void CCherryfps::CherryfpsGetfpsEx(float* pfps)
{
	static int FrameCount = 0;
	static DWORD TimeLast = 0;
	DWORD TimeCurrent = 0;
	float TimeElapsed = 0.0f;

	FrameCount++;
	timeBeginPeriod(1);
	TimeCurrent = timeGetTime();
	timeEndPeriod(1);
	TimeElapsed = (TimeCurrent - TimeLast) * 0.001f;

	if (TimeElapsed >= 1.0f)
	{
		*pfps = (float)(FrameCount * 1.0f / TimeElapsed);
		TimeLast = TimeCurrent;
		FrameCount = 0;
	}
}

//------------------------------------------------------------------
// @Function:	 CherryfpsGetfpsEx(float fTimeDelta)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: float fTimeDelta		//时间间隔(ms)
// @Return: float fps			//帧速率fps
//------------------------------------------------------------------
float CCherryfps::CherryfpsGetfpsEx(float fTimeDelta)
{
	static int FrameCount = 0;
	static float TimeElapsed = 0.0f;
	float fps = 0.0f;

	FrameCount++;
	TimeElapsed += fTimeDelta;

	if (TimeElapsed >= 1.0f)
	{
		fps = (float)(FrameCount * 1.0f / TimeElapsed);
		FrameCount = 0;
		TimeElapsed = 0.0f;
	}

	return fps;
}

//------------------------------------------------------------------
// @Function:	 CherryfpsGetfpsEx(void)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: None
// @Return: float fps			//帧速率fps
//------------------------------------------------------------------
float CCherryfps::CherryfpsGetfpsEx(void)
{
	static int FrameCount = 0;
	static DWORD TimeLast = 0;
	DWORD TimeCurrent = 0;
	float TimeElapsed = 0.0f;
	float fps;

	FrameCount++;
	timeBeginPeriod(1);
	TimeCurrent = timeGetTime();
	timeEndPeriod(1);
	TimeElapsed = (TimeCurrent - TimeLast) * 0.001f;

	if (TimeElapsed >= 1.0f)
	{
		fps = (float)(FrameCount * 1.0f / TimeElapsed);
		TimeLast = TimeCurrent;
		FrameCount = 0;
	}

	return fps;
}

//------------------------------------------------------------------------
// @Function:	 CherryfpsDrawfps(HWND hWnd)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: HWND hWnd		//窗口句柄
// @Return: None
//------------------------------------------------------------------------
void CCherryfps::CherryfpsDrawfps(HWND hWnd)
{
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_fps);
	m_pFont->DirectFontDrawText(hWnd, fpsArr, DIRECTFONT_FORMAT_BOTTOMRIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//------------------------------------------------------------------------
// @Function:	 CherryfpsDrawfps(HWND hWnd)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: HWND hWnd		//窗口句柄
// @Para: DWORD Format	//字体样式
// @Return: None
//------------------------------------------------------------------------
void CCherryfps::CherryfpsDrawfps(HWND hWnd, DWORD Format)
{
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_fps);
	m_pFont->DirectFontDrawText(hWnd, fpsArr, Format, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//------------------------------------------------------------------------
// @Function:	 CherryfpsDrawfps(HWND hWnd, DWORD Format, D3DCOLOR Color)
// @Purpose: CCherryfps获取帧速率fps
// @Since: v1.00a
// @Para: HWND hWnd		//窗口句柄
// @Para: DWORD Format	//字体样式
// @Para: D3DCOLOR Color//字体颜色
// @Return: None
//------------------------------------------------------------------------
void CCherryfps::CherryfpsDrawfps(HWND hWnd, DWORD Format, D3DCOLOR Color)
{
	wchar_t fpsArr[20];
	int ArrSize;

	ArrSize = swprintf_s(fpsArr, 20, _T("%0.1ffps"), m_fps);
	m_pFont->DirectFontDrawText(hWnd, fpsArr, Format, Color);
}