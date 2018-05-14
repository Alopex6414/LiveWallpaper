/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveRollText.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-14
*/
#pragma once

#ifndef __LIVEROLLTEXT_H_
#define __LIVEROLLTEXT_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveRollText
{
private:
	int m_nPosX;						//<<<RollText控件X坐标
	int m_nPosY;						//<<<RollText控件Y坐标
	int m_nWidth;						//<<<RollText控件宽度
	int m_nHeight;						//<<<RollText控件高度

	int m_nTextX;
	int m_nTextY;

protected:
	int m_nFontSize;					//<<<RollText字体大小
	char m_chFontType[MAX_PATH];		//<<<RollText字体类型

	TCHAR m_tcFilePath[MAX_PATH];		//<<<RollText图片路径
	CImage m_iMage;						//<<<RollText图片

public:
	CLiveRollText();	// 构造
	~CLiveRollText();	// 析构

	VOID LiveRollText_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	VOID LiveRollText_SetFont(const char* szFontType, int nFontSize);
	BOOL LiveRollText_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	BOOL LiveRollTextInit(LPCSTR szFile);
	VOID LiveRollTextPaint(HDC& hDC, const char* szText, bool bLoad, int nAlpha);
};

#endif // !__LIVEROLLTEXT_H_
