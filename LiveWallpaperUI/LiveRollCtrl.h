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
	int m_nPosX;						//<<<RollCtrl控件X坐标
	int m_nPosY;						//<<<RollCtrl控件Y坐标
	int m_nWidth;						//<<<RollCtrl控件宽度
	int m_nHeight;						//<<<RollCtrl控件高度

	int m_nMoveX;
	int m_nMoveY;

	bool m_bSelectLeft;					//<<<RollCtrl选中左键标志
	bool m_bSelectRight;				//<<<RollCtrl选中右键标志
	int m_nLeftAlpha;					//<<<RollCtrl左键Alpha
	int m_nRightAlpha;					//<<<RollCtrl右键Alpha

protected:
	TCHAR m_tcFilePathLeft[MAX_PATH];		//<<<图片路径(Left)
	TCHAR m_tcFilePathRight[MAX_PATH];		//<<<图片路径(Right)
	TCHAR m_tcFilePathText[MAX_PATH];		//<<<文字路径(Text)

	CImage m_iMageLeft;						//<<<图片(Left)
	CImage m_iMageRight;					//<<<图片(Right)
	CImage m_iMageText;						//<<<图片(Text)

public:
	CLiveRollCtrl();		//构造
	~CLiveRollCtrl();		//析构

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

