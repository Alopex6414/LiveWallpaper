/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		WinMain.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-11-29
*/
#include "WinMain.h"

/*
** WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
** Purpose:  ´°¿ÚÖ÷º¯Êý
*/
int WINAPI WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
{
	int Msg;

	InitWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow, (LPCALLBACKSETWNDPARAFUNC)(&SetWindowParameterCallBack), (LPCALLBACKINITWNDEXTRAFUNC)(&InitWindowExtraCallBack));
	Msg = WinMainLoop((LPCALLBACKDIRECT3DRENDERFUNC)(&Direct3DRenderCallBack), (LPCALLBACKRELEASEWNDEXTRAFUNC)(&ReleaseWindowExtraCallBack));

	return Msg;
}