/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		WinMain.cpp
* @brief	This Program is LiveWallpaperCleanUp Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-14
*/
#include "WinMain.h"

//Variable Definition
CPlumLog g_cPlumLog;

/*
** WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
** Purpose:  窗口主函数
** Para: IN HINSTANCE hInstance			// 窗口实例句柄(Win32)
** Para: IN HINSTANCE hPrevInstance		// 窗口实例句柄(Win16)
** Para: IN LPSTR lpCmdLine				// 窗口命令行参数数组<char*[]>
** Para: IN int nCmdShow				// 窗口命令行参数数量<int>
** Return: INT Msg						// 返回值(消息参数)
*/
int WINAPI WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nCmdShow)
{
	int nResult = 0;

	g_cPlumLog.PlumLogInit();

	g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "CleanUp File Path: %s\n", lpCmdLine);

	nResult = strcmp(lpCmdLine, "");
	if (nResult == 0)
	{
		g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "Process Exception Exit! Return Value=1, No CmdLine Parameter!\n");
		g_cPlumLog.PlumLogExit();
		return 1;
	}

	while (true)
	{
		if (!IsProcessExist(L"LiveWallpaperCore.exe"))
		{
			g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "Check Process Status: Process Exit.\n");
			Sleep(100);
			break;
		}
		g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "Check Process Status: Process Exist.\n");
		Sleep(100);
	}

	BOOL bResult;

	bResult = LiveCleanUpFile(lpCmdLine);
	if (!bResult)
	{
		g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "Process Exception Exit! Return Value=2, Can not CleanUp File!\n");
		g_cPlumLog.PlumLogExit();
		return 2;
	}

	g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "Process Exit! Return Value=0.\n");
	g_cPlumLog.PlumLogExit();
	return 0;
}
