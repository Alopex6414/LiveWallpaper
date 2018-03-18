/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCore.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-11-29
*/
#pragma once

//Include Windows Header File
#include <Windows.h>

//Include CommCtrl Header File
#include <CommCtrl.h>

//Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>

//Include PlumLibrary
#include "PlumLog.h"

//Variable Declaration
extern bool g_bReStart;
extern bool g_bMonitorFlag;
extern volatile bool g_bDecodeFlag;
extern CRITICAL_SECTION g_csDecode;

extern unsigned char* g_pArrayY;
extern unsigned char* g_pArrayU;
extern unsigned char* g_pArrayV;

extern int g_nVideoWidth;
extern int g_nVideoHeight;

extern CPlumLog g_pPlumLogMain;

//Function Declaration
extern BOOL LiveWallpaperInit();
extern void LiveWallpaperRelease();
extern void LiveWallpaperUpdate();
extern void LiveWallpaperRender();
