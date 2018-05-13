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
	int m_nScreenWidth;		//<<<���ڿ��
	int m_nScreenHeight;	//<<<���ڸ߶�

	bool m_bLoadWindow;		//<<<���ش��ڱ�־		
	bool m_bShowWindow;		//<<<�Ƿ���ʾ����
	int m_nAlpha;			//<<<����Alpha

protected:
	TCHAR m_tcFilePath[MAX_PATH];		//<<<ͼƬ·��
	CImage m_iMage;						//<<<ͼƬ

public:
	CLiveTab();				//LiveTab���캯��
	~CLiveTab();			//LiveTab��������

	void LiveTab_SetWindow(int nWidth, int nHeight);
	BOOL LiveTab_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	void LiveTabSetShowState(bool bShow);
	bool LiveTabGetShowState(void);

	BOOL LiveTabInit(LPCSTR szFile);
	VOID LiveTabPaint(HDC& hDC);
};


#endif // !__LIVETAB_H_

