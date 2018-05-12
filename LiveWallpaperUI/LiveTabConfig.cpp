/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTabConfig.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-07
*/
#include "LiveTabConfig.h"

//LiveUI LiveTabConfig->>Tab��

//------------------------------------------------------------------
// @Function:	 CLiveTabConfig()
// @Purpose: CLiveTabConfig���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConfig::CLiveTabConfig()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveTabConfig()
// @Purpose: CLiveTabConfig��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConfig::~CLiveTabConfig()
{
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigInit()
// @Purpose: CLiveTabConfig��ʼ��Tabҳ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigInit(void)
{
	LiveTab_SetWindow(640, 480);
	LiveTabInit("frame\\Bk\\Config.png");

	m_cLabelTitle.LiveButton_SetWindow(0, 0, 120, 40);
	m_cLabelTitle.LiveButtonInit("frame\\Label\\Config.png");

	LiveTabSetShowState(false);
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfig()
// @Purpose: CLiveTabConfig�ػ�Tabҳ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigPaint(HDC& hDC)
{
	LiveTabPaint(hDC);

	m_cLabelTitle.LiveButtonPaint(hDC, m_nAlpha);
	
}