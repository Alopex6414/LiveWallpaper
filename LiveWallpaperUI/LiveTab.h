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
	int m_nScreenWidth;		//<<<���ڿ��
	int m_nScreenHeight;	//<<<���ڸ߶�

protected:
	TCHAR m_tcFilePath[MAX_PATH];		//<<<ͼƬ·��
	CImage m_iMage;						//<<<ͼƬ

public:
	CLiveTab();
	~CLiveTab();

	void LiveTab_SetWindow(int nWidth, int nHeight);
	BOOL LiveTab_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

};


#endif // !__LIVETAB_H_

