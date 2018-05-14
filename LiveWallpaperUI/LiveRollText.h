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
	int m_nPosX;						//<<<RollText�ؼ�X����
	int m_nPosY;						//<<<RollText�ؼ�Y����
	int m_nWidth;						//<<<RollText�ؼ����
	int m_nHeight;						//<<<RollText�ؼ��߶�

	int m_nTextX;
	int m_nTextY;

protected:
	int m_nFontSize;					//<<<RollText�����С
	char m_chFontType[MAX_PATH];		//<<<RollText��������

	TCHAR m_tcFilePath[MAX_PATH];		//<<<RollTextͼƬ·��
	CImage m_iMage;						//<<<RollTextͼƬ

public:
	CLiveRollText();	// ����
	~CLiveRollText();	// ����

	VOID LiveRollText_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	VOID LiveRollText_SetFont(const char* szFontType, int nFontSize);
	BOOL LiveRollText_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	BOOL LiveRollTextInit(LPCSTR szFile);
	VOID LiveRollTextPaint(HDC& hDC, const char* szText, bool bLoad, int nAlpha);
};

#endif // !__LIVEROLLTEXT_H_
