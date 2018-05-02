/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreWaitThread.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-05-02
*/
#pragma once

#include "PlumThread.h"

class CLiveCoreWaitThread :public CPlumThreadBase
{
public:
	CLiveCoreWaitThread();
	~CLiveCoreWaitThread();
	virtual void WINAPI PlumThreadRun();
};

