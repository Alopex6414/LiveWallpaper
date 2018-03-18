/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreThread2.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-3-11
*/
#pragma once

#include "PlumThread.h"

class CLiveCoreThread2 :public CPlumThreadBase
{
public:
	CLiveCoreThread2();
	~CLiveCoreThread2();
	virtual void WINAPI PlumThreadRun();
};
