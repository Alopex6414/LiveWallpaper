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
	int m_nPosX;						//<<<Radio�ؼ�X����
	int m_nPosY;						//<<<Radio�ؼ�Y����
	int m_nWidth;						//<<<Radio�ؼ����
	int m_nHeight;						//<<<Radio�ؼ��߶�

	bool m_bSelect;						//<<<Radio�ؼ�ѡ��״̬
	int m_nAlpha;						//<<<Radio�ؼ�Alpha

protected:
	TCHAR m_tcFilePathUp[MAX_PATH];		//<<<ͼƬ·��(Up)
	TCHAR m_tcFilePathDown[MAX_PATH];	//<<<ͼƬ·��(Down)
	CImage m_iMageUp;					//<<<ͼƬ(Up)
	CImage m_iMageDown;					//<<<ͼƬ(Down)

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

