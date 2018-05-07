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
private:
	int m_nScreenWidth;		//<<<窗口宽度
	int m_nScreenHeight;	//<<<窗口高度

protected:
	TCHAR m_tcFilePath[MAX_PATH];		//<<<图片路径
	CImage m_iMage;						//<<<图片

public:
	CLiveTab();
	~CLiveTab();

	void LiveTab_SetWindow(int nWidth, int nHeight);
	BOOL LiveTab_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

};


#endif // !__LIVETAB_H_

