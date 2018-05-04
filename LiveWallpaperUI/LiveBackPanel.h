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
	int m_nPosX;						//<<<Panel�ؼ�X����
	int m_nPosY;						//<<<Panel�ؼ�Y����
	int m_nWidth;						//<<<Panel�ؼ����
	int m_nHeight;						//<<<Panel�ؼ��߶�

	TCHAR m_tcFilePath[MAX_PATH];		//<<<ͼƬ·��
	CImage m_iMage;						//<<<ͼƬ

public:
	int m_nMoveX;						//<<<�ƶ���X����
	int m_nMoveY;						//<<<�ƶ���Y����

public:
	CLiveBackPanel();					//<<<����
	~CLiveBackPanel();					//<<<����

	CLiveBackPanel(int nPosX, int nPosY, int nWidth, int nHeight);

	void LiveBackPanel_SetMove(int nMoveX, int nMoveY);
	void LiveBackPanel_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	BOOL LiveBackPanel_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	BOOL LiveBackPanelInit(LPCSTR szFile);
	VOID LiveBackPanelPaint(HDC& hDC);
};


#endif // !__LIVEBACKPANEL_H_


