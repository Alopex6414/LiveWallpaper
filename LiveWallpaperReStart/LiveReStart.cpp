/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveReStart.cpp
* @brief	This Program is LiveWallpaperReStart Project.
* @author	alopex
* @version	v1.00a
* @date		2018-03-21
*/
#include "LiveReStart.h"

//------------------------------------------------------------------
// @Function:	 LiveReStartProcess()
// @Purpose: LiveReStart启动进程
// @Since: v1.00a
// @Para: const char* pStrArr	//进程名称
// @Return: BOOL (TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
BOOL LiveReStartProcess(const char* pStrArr)
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
	strcat_s(chProcessPath, pStrArr);

	bResult = CreateProcessA(chProcessPath, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	if (bResult)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return bResult;
}

//------------------------------------------------------------------
// @Function:	 IsProcessExist()
// @Purpose: LiveWallpaperCore检测进程是否存在
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL IsProcessExist(const WCHAR* strFilename)
{
	BOOL bRet = FALSE;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32)) {
		do {
			if (_wcsicmp(pe32.szExeFile, strFilename) == 0) {
				bRet = TRUE;
				break;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}
	else {
		bRet = FALSE;
	}
	CloseHandle(hProcessSnap);
	return bRet;
}