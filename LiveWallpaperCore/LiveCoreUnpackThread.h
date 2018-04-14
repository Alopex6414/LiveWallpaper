/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreUnpackThread.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-4-12
*/
#pragma once

#include "PlumThread.h"

class CLiveCoreUnpackThread :public CPlumThreadBase
{
public:
	CLiveCoreUnpackThread();
	~CLiveCoreUnpackThread();
	virtual void WINAPI PlumThreadRun();
};
