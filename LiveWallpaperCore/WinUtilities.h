/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		WinUtilities.h
* @brief	This Program is WinUtilities DLL Project.
* @author	Alopex/Helium
* @version	v1.10a
* @date		2017-11-28	v1.00a	alopex	Create Project
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
*/
#pragma once

#ifndef __WINUTILITIES_H_
#define __WINUTILITIES_H_

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

//Macro Definition
#ifdef WINUTILITIES_EXPORTS
#define WINUTILITIES_API extern "C" __declspec(dllexport)
#else
#define WINUTILITIES_API extern "C" __declspec(dllimport)
#endif

//Struct Definition
typedef struct WndPara
{
	int nWndWidth;		//Window Area Width
	int nWndHeight;		//Window Area Height
	LPCWSTR lpszTitle;	//Window Title Name
	WORD wIcon;			//Window Icon Resource Number
} WndPara;

//CallBack Definition
typedef WndPara*	(CALLBACK*LPCALLBACKSETWNDPARAFUNC)(void);//Init Window Parameter
typedef BOOL		(CALLBACK*LPCALLBACKINITWNDEXTRAFUNC)(void);//Init Window Extra
typedef void		(CALLBACK*LPCALLBACKRELEASEWNDEXTRAFUNC)(void);//Release Window Extra
typedef void		(CALLBACK*LPCALLBACKDIRECT3DRENDERFUNC)(void);//Direct3D Render

//Variable Definition
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;

//Function Definition
extern ATOM MyRegisterClass(HINSTANCE hInstance, WndPara* lpsWndPara);//Register Window Class
extern BOOL InitWndInstance(HINSTANCE hInstance, int nCmdShow, WndPara* lpsWndPara, LPCALLBACKINITWNDEXTRAFUNC pCallBackInitWndExtra);//Initialization Window Instance
extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//Window Process Function
extern HRESULT InitWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LPCALLBACKSETWNDPARAFUNC pCallBackSetWndPara, LPCALLBACKINITWNDEXTRAFUNC pCallBackInitWndExtra);//Initialization WinMain
extern int WinMainLoop(LPCALLBACKDIRECT3DRENDERFUNC pCallBackDirect3DRender, LPCALLBACKRELEASEWNDEXTRAFUNC pCallBackReleaseWndExtra);//Window WinMain Loop

#endif