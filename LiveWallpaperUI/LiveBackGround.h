/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveBackGround.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-03
*/
#pragma once

#ifndef __LIVEBACKGROUND_H_
#define __LIVEBACKGROUND_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveBackGround
{
private:
	int m_nScreenWidth;		//<<<窗口宽度
	int m_nScreenHeight;	//<<<窗口高度

	TCHAR m_tcFilePath[MAX_PATH];		//<<<图片路径
	CImage m_iMage;						//<<<图片

public:
	CLiveBackGround();
	~CLiveBackGround();

	CLiveBackGround(int nWidth, int nHeight);

	void LiveBackGround_SetWindow(int nWidth, int nHeight);
	BOOL LiveBackGround_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	BOOL LiveBackGroundInit(LPCSTR szFile);
	VOID LiveBackGroundPaint(HDC& hDC);

};

#endif // !__LIVEBACKGROUND_H_
