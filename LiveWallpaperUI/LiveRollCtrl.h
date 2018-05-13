/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveRollCtrl.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-13
*/
#pragma once

#ifndef __LIVEROLLCTRL_H_
#define __LIVEROLLCTRL_H_

//Include Common Header File
#include "Common.h"

//Class Definition
class CLiveRollCtrl
{
private:
	int m_nPosX;						//<<<RollCtrl�ؼ�X����
	int m_nPosY;						//<<<RollCtrl�ؼ�Y����
	int m_nWidth;						//<<<RollCtrl�ؼ����
	int m_nHeight;						//<<<RollCtrl�ؼ��߶�

	int m_nMoveX;
	int m_nMoveY;

	bool m_bSelectLeft;					//<<<RollCtrlѡ�������־
	bool m_bSelectRight;				//<<<RollCtrlѡ���Ҽ���־
	int m_nLeftAlpha;					//<<<RollCtrl���Alpha
	int m_nRightAlpha;					//<<<RollCtrl�Ҽ�Alpha

protected:
	TCHAR m_tcFilePathLeft[MAX_PATH];		//<<<ͼƬ·��(Left)
	TCHAR m_tcFilePathRight[MAX_PATH];		//<<<ͼƬ·��(Right)
	TCHAR m_tcFilePathText[MAX_PATH];		//<<<����·��(Text)

	CImage m_iMageLeft;						//<<<ͼƬ(Left)
	CImage m_iMageRight;					//<<<ͼƬ(Right)
	CImage m_iMageText;						//<<<ͼƬ(Text)

public:
	CLiveRollCtrl();		//����
	~CLiveRollCtrl();		//����

	void LiveRollCtrl_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight);
	BOOL LiveRollCtrl_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);

	void LiveRollCtrl_SetLeftClick(bool bClick) { m_bSelectLeft = bClick; }
	bool LiveRollCtrl_GetLeftClick(void) { return m_bSelectLeft; }
	void LiveRollCtrl_SetRightClick(bool bClick) { m_bSelectRight = bClick; }
	bool LiveRollCtrl_GetRightClick(void) { return m_bSelectRight; }

	bool LiveRollCtrlIsLeftHover(POINT pt);
	bool LiveRollCtrlIsRightHover(POINT pt);

	BOOL LiveRollCtrlInit(LPCSTR szFileLeft, LPCSTR szFileRight, LPCSTR szFileText);
	VOID LiveRollCtrlPaint(HDC& hDC, POINT pt, bool bLoad, int nAlpha);

};

#endif // !__LIVEROLLCTRL_H_

