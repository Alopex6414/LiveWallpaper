/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		Live.cpp
* @brief	This Program is LiveWallpaper Project.
* @author	alopex
* @version	v1.00a
* @date		2018-03-24
*/
#include "Live.h"

//------------------------------------------------------------------
// @Function:	 CreateLiveUIProcess()
// @Purpose: LiveUI启动进程
// @Since: v1.00a
// @Para: NULL
// @Return: BOOL (TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
BOOL CreateLiveUIProcess()
{
	BOOL bResult;

	STARTUPINFOA si = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFOA);
	GetStartupInfoA(&si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&pi, sizeof(pi));

	char chProcessPath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chProcessPath, MAX_PATH);
	pTemp = strrchr(chProcessPath, '\\');
	if (pTemp) *pTemp = '\0';
	strcat_s(chProcessPath, "\\");
	strcat_s(chProcessPath, "LiveWallpaperUI.exe");

	bResult = CreateProcessA(chProcessPath, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	if (bResult)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return bResult;
}