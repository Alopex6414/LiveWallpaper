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
#include "DirectCommon.h"
#include "DirectGraphics.h"
#include "DirectSurface.h"

#define LIVECOREWAIT_CALLMODE	__stdcall

//Class Definition
class CLiveCoreWait
{
private:
	DirectGraphics* m_pLiveWaitGraphics;

private:
	HWND m_hWnd;

public:
	CLiveCoreWait();
	~CLiveCoreWait();

	HRESULT LIVECOREWAIT_CALLMODE LiveCoreWaitInit();

};

#endif // !__LIVECOREWAIT_H_


