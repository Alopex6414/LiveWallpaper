/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreMonitor.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-11-29
*/
#pragma once

#include "PlumThread.h"

class CLiveCoreMonitor :public CPlumThreadBase
{
private:
	bool m_bProcess;

public:
	CLiveCoreMonitor();
	~CLiveCoreMonitor();
	virtual void WINAPI PlumThreadRun();
};
