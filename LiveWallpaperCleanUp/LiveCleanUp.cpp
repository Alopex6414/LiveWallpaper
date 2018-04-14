/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveCleanUp.cpp
* @brief	This Program is LiveWallpaperCleanUp Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-14
*/
#include "LiveCleanUp.h"

//------------------------------------------------------------------
// @Function:	 LiveCleanUpFile()
// @Purpose: LiveCleanUp清理解包文件
// @Since: v1.00a
// @Para: const char* pStrArr	//解包文件名称
// @Return: BOOL (TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
BOOL LiveCleanUpFile(const char* pStrArr)
{
	BOOL bRet = FALSE;

	bRet = DeleteFileA(pStrArr);
	if (!bRet) return FALSE;

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 IsProcessExist()
// @Purpose: LiveCleanUp检测进程是否存在
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