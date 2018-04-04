/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		WinMain.cpp
* @brief	This Program is LiveWallpaper Project.
* @author	alopex
* @version	v1.00a
* @date		2018-03-24
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

	g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "Live Process Created Succeed.\n");

	BOOL bResult;

	bResult = CreateLiveUIProcess();
	if (!bResult)
	{
		g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "LiveUI Process Created FAIL! Return Value=-1.\n");
		g_cPlumLog.PlumLogExit();
		return -1;
	}

	g_cPlumLog.PlumLogWriteExtend(__FILE__, __LINE__, "LiveUI Process Created Succeed. Return Value=0.\n");
	g_cPlumLog.PlumLogExit();
	return 0;
}
