/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectCommon.h
* @brief	This File is DirectX Library Common Header.
* @author	Alopex/Helium
* @version	v1.21a
* @date		2017-10-27	v1.00a	alopex	Create This File.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-2	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-18	v1.21a	alopex	Code Add assert Header File.
*/
#pragma once

#ifndef __DIRECTCOMMON_H_
#define __DIRECTCOMMON_H_

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

//Include Assert Header File
#include <assert.h>

//Include DirectX Support Header File
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <dinput.h>
#include <dsound.h>
#include <dxerr.h>
#include <d3dcompiler.h>

//Include Static Library File
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxerr.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"WinMM.lib")

//Macro Check Unicode
#ifndef UNICODE
#error "DirectX requires a Unicode build."
#endif

//Macro Definition
#define SAFE_RELEASE(Pointer)	{if(Pointer){(Pointer)->Release();(Pointer) = NULL;}}//Release Pointer
#define SAFE_DELETE(Pointer)	{if(Pointer){delete(Pointer);(Pointer) = NULL;}}//Delete Pointer
#define SAFE_DELETE_ARRAY(Pointer) {if(Pointer){delete[](Pointer);(Pointer) = NULL;}}//Delete Pointer Array

//Macro Verify And Check
#if defined (DEBUG) || defined (_DEBUG)
#ifndef CHECK
#define CHECK(x)	{HRESULT hr = (x); if(FAILED(hr)){DXTRACE_ERR_MSGBOX(L#x, hr);}}//Check Expression
#endif
#ifndef VERIFY
#define VERIFY(x)	{HRESULT hr = (x); if(FAILED(hr)){DXTRACE_ERR_MSGBOX(L#x, hr); return E_FAIL;}}//Verify Expression
#endif
#else
#ifndef CHECK
#define CHECK(x)	{HRESULT hr = (x);}//Check Expression
#endif
#ifndef VERIFY
#define VERIFY(x)	{HRESULT hr = (x); if(FAILED(hr)){return E_FAIL;}}//Verify Expression
#endif
#endif

#endif