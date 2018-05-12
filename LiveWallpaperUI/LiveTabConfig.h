/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTabConfig.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-07
*/
#pragma once

#ifndef __LIVETABCONFIG_H_
#define __LIVETABCONFIG_H_

//Include Common Header File
#include "Common.h"
#include "LiveTab.h"
#include "LiveButton.h"

//Class Definition
class CLiveTabConfig :public CLiveTab
{
protected:
	CLiveButton m_cLabelTitle;

public:
	CLiveTabConfig();
	~CLiveTabConfig();

	VOID LiveTabConfigInit(void);
	VOID LiveTabConfigPaint(HDC& hDC);

};

#endif // !__LIVETABCONFIG_H_
