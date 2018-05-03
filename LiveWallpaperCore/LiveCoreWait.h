/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreWait.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-05-02
*/
#pragma once

#ifndef __LIVECOREWAIT_H_
#define __LIVECOREWAIT_H_

//Include Header File
#include "WinUtilities.h"

#include "DirectCommon.h"
#include "DirectGraphics.h"
#include "DirectSurface.h"
#include "DirectTexture.h"

//Include Resource File
#include "resource.h"

#define LIVECOREWAIT_CALLMODE	__stdcall

//Macro Definition
#define LIVECOREWAIT_DLG_WIDTH	640
#define LIVECOREWAIT_DLG_HEIGHT	480

//Class Definition
class CLiveCoreWait
{
private:
	DirectGraphics* m_pLiveWaitGraphics;
	DirectTexture* m_pLiveWaitTexture;

private:
	HWND m_hWnd;
	TCHAR m_tcTexturePath[MAX_PATH];

protected:
	BOOL LIVECOREWAIT_CALLMODE LiveCoreWait_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize);
	BOOL LIVECOREWAIT_CALLMODE LiveCoreWait_Texture_GetPath(LPCSTR szFile);

public:
	CLiveCoreWait();
	~CLiveCoreWait();

	BOOL LIVECOREWAIT_CALLMODE LiveCoreWaitInit();
	void LIVECOREWAIT_CALLMODE LiveCoreWaitUpdate();
	void LIVECOREWAIT_CALLMODE LiveCoreWaitRender();

public:
	static LRESULT LiveCoreWaitProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

};

#endif // !__LIVECOREWAIT_H_


