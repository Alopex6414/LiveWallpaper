/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTab.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-07
*/
#pragma once

#ifndef __LIVETAB_H_
#define __LIVETAB_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveTab
{
protected:
	int m_nScreenWidth;		//<<<窗口宽度
	int m_nScreenHeight;	//<<<窗口高度

	bool m_bLoadWindow;		//<<<加载窗口标志		
	bool m_bShowWindow;		//<<<是否显示窗口
	int m_nAlpha;			//<<<窗口Alpha

protected:
	TCHAR m_tcFilePath[MAX_PATH];		//<<<图片路径
	CImage m_iMage;						//<<<图片

public:
	CLiveTab();				//LiveTab构造函数
	~CLiveTab();			//LiveTab析构函数

	void LiveTab_SetWindow(int nWidth, int nHeight);
	BOOL LiveTab_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	void LiveTabSetShowState(bool bShow);
	bool LiveTabGetShowState(void);

	BOOL LiveTabInit(LPCSTR szFile);
	VOID LiveTabPaint(HDC& hDC);
};


#endif // !__LIVETAB_H_

