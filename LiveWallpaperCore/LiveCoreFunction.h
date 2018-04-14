/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreFunction.h
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2018-3-10
*/
#pragma once

//Include Windows Header File
#include <Windows.h>
#include <TlHelp32.h>

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

//Variable Declaration
extern int g_nLiveCoreMode;
extern int g_nLiveCoreShowGraphics;
extern int g_nLiveCoreShowGraphicsFont;
extern int g_nLiveCoreWallpaperMode;
extern int g_nLiveCoreWallpaperAudioMode;
extern int g_nLiveCoreLogProcess;
extern int g_nLiveCoreVideoMode;
extern char g_chLiveCoreVideoName[MAX_PATH];
extern char g_chLiveCoreVideoAddress[MAX_PATH];

//Function Declaration
extern void AnalyzeConfigFile();
extern BOOL LiveRunPreProcess();
extern BOOL AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight);
extern BOOL IsProcessExist(const WCHAR* strFilename);
extern BOOL LiveCoreReStartProcess(const char* pStrArr);
extern BOOL LiveCoreCleanUp(const char* pStrArr);
extern void LiveCoreSetChildWindow(HWND hChildWindow);
