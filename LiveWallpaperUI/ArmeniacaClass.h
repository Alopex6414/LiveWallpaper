/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		ArmeniacaClass.h
* @brief	This Program is Armeniaca Dynamic Link Library Class Project.
* @author	alopex
* @version	v0.01a
* @date		2018-4-21	v0.01a	alopex	Create Project.
*/
#pragma once

#ifndef __ARMENIACACLASS_H_
#define __ARMENIACACLASS_H_

//Include Windows Header File
#include <Windows.h>

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
#include <assert.h>

//Macro Definition
#ifdef ARMENIACACLASS_EXPORTS
#define ARMENIACACLASS_API __declspec(dllexport)
#else
#define ARMENIACACLASS_API __declspec(dllimport)
#endif

#define ARMENIACACLASS_CALLBACK __cdecl
#define	ARMENIACACLASS_CALLMODE __stdcall

//CallBack Definition
typedef BOOL(ARMENIACACLASS_CALLBACK*ARMENIACA_ISPROCESSEXISTA)(const char*);
typedef BOOL(ARMENIACACLASS_CALLBACK*ARMENIACA_ISPROCESSEXISTW)(const wchar_t*);
typedef BOOL(ARMENIACACLASS_CALLBACK*ARMENIACA_STARTPROCESSA)(const char*);
typedef BOOL(ARMENIACACLASS_CALLBACK*ARMENIACA_STARTPROCESSW)(const wchar_t*);
typedef BOOL(ARMENIACACLASS_CALLBACK*ARMENIACA_CONVERT_A2W_SAFE)(const char*, const wchar_t*, int);
typedef BOOL(ARMENIACACLASS_CALLBACK*ARMENIACA_CONVERT_W2A_SAFE)(const wchar_t*, const char*, int);
typedef void (ARMENIACACLASS_CALLBACK*ARMENIACA_CONVERT_A2W_UNSAFE)(const char*, wchar_t*);
typedef void (ARMENIACACLASS_CALLBACK*ARMENIACA_CONVERT_W2A_UNSAFE)(const wchar_t*, char*);
typedef wchar_t* (ARMENIACACLASS_CALLBACK*ARMENIACA_CONVERT_A2W_UNSAFE2)(const char*);
typedef char* (ARMENIACACLASS_CALLBACK*ARMENIACA_CONVERT_W2A_UNSAFE2)(const wchar_t*);

//Class Definition
class CArmeniacaExport
{
private:
	HMODULE m_hModule;		//Dynamic Link Library Handle(~句柄)

public:
	ARMENIACA_ISPROCESSEXISTA Armeniaca_IsProcessExistA;
	ARMENIACA_ISPROCESSEXISTW Armeniaca_IsProcessExistW;
	ARMENIACA_STARTPROCESSA Armeniaca_StartProcessA;
	ARMENIACA_STARTPROCESSW Armeniaca_StartProcessW;
	ARMENIACA_CONVERT_A2W_SAFE Armeniaca_Convert_A2W_Safe;
	ARMENIACA_CONVERT_W2A_SAFE Armeniaca_Convert_W2A_Safe;
	ARMENIACA_CONVERT_A2W_UNSAFE Armeniaca_Convert_A2W_UnSafe;
	ARMENIACA_CONVERT_W2A_UNSAFE Armeniaca_Convert_W2A_UnSafe;
	ARMENIACA_CONVERT_A2W_UNSAFE2 Armeniaca_Convert_A2W_UnSafe2;
	ARMENIACA_CONVERT_W2A_UNSAFE2 Armeniaca_Convert_W2A_UnSafe2;

public:
	CArmeniacaExport();		//Construction Function(~构造)
	~CArmeniacaExport();	//Destruction Function(~析构)

	// 初始化
	virtual BOOL ARMENIACACLASS_CALLMODE ArmeniacaExportInit();	//ArmeniacaExport Initialize(~初始化)
	virtual BOOL ARMENIACACLASS_CALLMODE ArmeniacaImportFunctionAll();	//ArmeniacaExport Import Function All(~导入函数)

};

#endif // !__ARMENIACACLASS_H_

