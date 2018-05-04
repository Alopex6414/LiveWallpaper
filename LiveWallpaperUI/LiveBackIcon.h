/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveBackIcon.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-04
*/
#pragma once

#ifndef __LIVEBACKICON_H_
#define __LIVEBACKICON_H_

//Include Common Header File
#include "Common.h"
#include "LiveButton.h"

//Class Definition
class CLiveBackIcon :public CLiveButton
{
private:
	int m_nAlpha;
	bool m_bClick;

public:
	int m_nMoveX;						//<<<移动的X坐标
	int m_nMoveY;						//<<<移动的Y坐标

public:
	CLiveBackIcon();
	~CLiveBackIcon();

	bool LiveBackIconIsHover(POINT pt);
	VOID LiveBackIconSetClick(bool bClick);
	VOID LiveBackIconSetMove(int nMoveX, int nMoveY);

	VOID LiveBackIconPaint(HDC& hDC, POINT pt);
	VOID LiveBackIconPaint(HDC& hDC, UCHAR ucAlpha);
};

#endif // !__LIVEBACKICON_H_
