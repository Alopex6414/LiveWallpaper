/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveBackPanel.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-04
*/
#pragma once

#ifndef __LIVEBACKPANEL_H_
#define __LIVEBACKPANEL_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveBackPanel
{
private:
	int m_nPosX;						//<<<Panel控件X坐标
	int m_nPosY;						//<<<Panel控件Y坐标
	int m_nWidth;						//<<<Panel控件宽度
	int m_nHeight;						//<<<Panel控件高度

	TCHAR m_tcFilePath[MAX_PATH];		//<<<图片路径
	CImage m_iMage;						//<<<图片

public:
	int m_nMoveX;						//<<<移动的X坐标
	int m_nMoveY;						//<<<移动的Y坐标

public:
	CLiveBackPanel();					//<<<构造
	~CLiveBackPanel();					//<<<析构

	CLiveBackPanel(int nPosX, int nPosY, int nWidth, int nHeight);

	void LiveBackPanel_SetMove(int nMoveX, int nMoveY);
	void LiveBackPanel_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	BOOL LiveBackPanel_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	BOOL LiveBackPanelInit(LPCSTR szFile);
	VOID LiveBackPanelPaint(HDC& hDC);
};


#endif // !__LIVEBACKPANEL_H_


