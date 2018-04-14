/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveCleanUp.h
* @brief	This Program is LiveWallpaperCleanUp Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-14
*/
#pragma once

#ifndef __LIVECLEANUP_H_
#define __LIVECLEANUP_H_

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

//Function Declaration
extern BOOL LiveCleanUpFile(const char* pStrArr);
extern BOOL IsProcessExist(const WCHAR* strFilename);

#endif // !__LIVECLEANUP_H_
