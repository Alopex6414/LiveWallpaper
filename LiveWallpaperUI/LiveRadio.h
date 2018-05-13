/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveRadio.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-13
*/
#pragma once

#ifndef __LIVERADIO_H_
#define __LIVERADIO_H_

//Include Common Header File
#include "Common.h"
#include "LiveButton.h"

//Class Definition
class CLiveRadio
{
protected:
	int m_nPosX;						//<<<Radio控件X坐标
	int m_nPosY;						//<<<Radio控件Y坐标
	int m_nWidth;						//<<<Radio控件宽度
	int m_nHeight;						//<<<Radio控件高度

	bool m_bSelect;						//<<<Radio控件选中状态
	int m_nAlpha;						//<<<Radio控件Alpha

protected:
	TCHAR m_tcFilePathUp[MAX_PATH];		//<<<图片路径(Up)
	TCHAR m_tcFilePathDown[MAX_PATH];	//<<<图片路径(Down)
	CImage m_iMageUp;					//<<<图片(Up)
	CImage m_iMageDown;					//<<<图片(Down)

public:
	CLiveRadio();
	~CLiveRadio();

	void LiveRadio_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	BOOL LiveRadio_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	void LiveRadioSetSelectState(bool bSelect) { m_bSelect = bSelect; }
	bool LiveRadioGetSelectState(void) { return m_bSelect; }

	bool LiveRadioIsHover(POINT pt);

	BOOL LiveRadioInit(LPCSTR szFileUp, LPCSTR szFileDown);
	VOID LiveRadioPaint(HDC& hDC, POINT pt, bool bLoad, int nAlpha);
};


#endif // !__LIVERADIO_H_

