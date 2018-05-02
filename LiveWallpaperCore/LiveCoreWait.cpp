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
// @Purpose: CLiveCoreWait���캯��
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
// @Purpose: CLiveCoreWait��������
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
// @Purpose: CLiveCoreWait��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitInit()
{
	RECT Rect;

	SetRect(&Rect, 0, 0, 640, 480);//���ô����������
	AdjustWindowRect(&Rect, WS_POPUP, false);//���ھ��б��������˵�������С������

	return S_OK;
}