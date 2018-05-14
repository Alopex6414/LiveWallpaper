/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTip.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-14
*/
#pragma once

#ifndef __LIVETIP_H_
#define __LIVETIP_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveTip
{
protected:
	int m_nPosX;						//<<<Tip控件X坐标
	int m_nPosY;						//<<<Tip控件Y坐标
	int m_nWidth;						//<<<Tip控件宽度
	int m_nHeight;						//<<<Tip控件高度

	bool m_bShow;						//<<<Tip展示
	int m_nAlpha;						//<<<TipAlpha

protected:
	TCHAR m_tcFilePath[MAX_PATH];		//<<<Tip图片路径
	CImage m_iMage;						//<<<Tip图片

public:
	int m_nDeltaX;
	int m_nDeltaY;

public:
	CLiveTip();		// 构造
	~CLiveTip();	// 析构

	void LiveTip_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	BOOL LiveTip_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	void LiveTip_SetShowFlag(bool bShow) { m_bShow = bShow; }
	bool LiveTip_GetShowFlag(void) { return m_bShow; }

	BOOL LiveTipInit(LPCSTR szFile);
	VOID LiveTipPaint(HDC& hDC);
};


#endif // !__LIVETIP_H_

