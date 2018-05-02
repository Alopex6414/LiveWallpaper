/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreWait.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-05-02
*/
#include "LiveCoreWait.h"

//------------------------------------------------------------------
// @Function:	 CLiveCoreWait()
// @Purpose: CLiveCoreWait构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWait::CLiveCoreWait()
{
	m_pLiveWaitGraphics = new DirectGraphics();
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreWait()
// @Purpose: CLiveCoreWait析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWait::~CLiveCoreWait()
{
	SAFE_DELETE(m_pLiveWaitGraphics);
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitInit()
// @Purpose: CLiveCoreWait初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitInit()
{
	RECT Rect;

	SetRect(&Rect, 0, 0, 640, 480);//设置窗口区域矩形
	AdjustWindowRect(&Rect, WS_POPUP, false);//窗口具有标题栏、菜单栏、最小化窗口

	return S_OK;
}