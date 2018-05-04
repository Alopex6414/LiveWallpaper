/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveButton.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-04
*/
#pragma once

#ifndef __LIVEBUTTON_H_
#define __LIVEBUTTON_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveButton
{
protected:
	int m_nPosX;						//<<<Button�ؼ�X����
	int m_nPosY;						//<<<Button�ؼ�Y����
	int m_nWidth;						//<<<Button�ؼ����
	int m_nHeight;						//<<<Button�ؼ��߶�

protected:
	TCHAR m_tcFilePath[MAX_PATH];		//<<<ͼƬ·��
	CImage m_iMage;						//<<<ͼƬ

public:
	CLiveButton();
	~CLiveButton();

	CLiveButton(int nPosX, int nPosY, int nWidth, int nHeight);

	int LiveButtonGetPosX();
	int LiveButtonGetPosY();
	int LiveButtonGetWidth();
	int LiveButtonGetHeight();

	void LiveButton_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	BOOL LiveButton_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	BOOL LiveButtonInit(LPCSTR szFile);
	VOID LiveButtonPaint(HDC& hDC);
};

#endif // !__LIVEBUTTON_H_

