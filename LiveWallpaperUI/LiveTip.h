/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTip.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-14
*/
#pragma once

#ifndef __LIVETIP_H_
#define __LIVETIP_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveTip
{
protected:
	int m_nPosX;						//<<<Tip�ؼ�X����
	int m_nPosY;						//<<<Tip�ؼ�Y����
	int m_nWidth;						//<<<Tip�ؼ����
	int m_nHeight;						//<<<Tip�ؼ��߶�

	bool m_bShow;						//<<<Tipչʾ
	int m_nAlpha;						//<<<TipAlpha

protected:
	TCHAR m_tcFilePath[MAX_PATH];		//<<<TipͼƬ·��
	CImage m_iMage;						//<<<TipͼƬ

public:
	int m_nDeltaX;
	int m_nDeltaY;

public:
	CLiveTip();		// ����
	~CLiveTip();	// ����

	void LiveTip_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	BOOL LiveTip_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	void LiveTip_SetShowFlag(bool bShow) { m_bShow = bShow; }
	bool LiveTip_GetShowFlag(void) { return m_bShow; }

	BOOL LiveTipInit(LPCSTR szFile);
	VOID LiveTipPaint(HDC& hDC);
};


#endif // !__LIVETIP_H_

