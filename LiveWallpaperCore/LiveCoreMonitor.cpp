/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreMonitor.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-11-29
*/
#include "LiveCore.h"
#include "LiveCoreMonitor.h"
#include "LiveCoreFunction.h"

CLiveCoreMonitor::CLiveCoreMonitor()
{
	m_bProcess = false;
}

CLiveCoreMonitor::~CLiveCoreMonitor()
{
}

void WINAPI CLiveCoreMonitor::PlumThreadRun()
{
	while (!g_bMonitorFlag)
	{
		if (!m_bProcess)
		{
			if (IsProcessExist(L"LiveWallpaperPre.dll"))
			{
				m_bProcess = true;
			}
		}
		else
		{
			if (!IsProcessExist(L"LiveWallpaperPre.dll"))
			{
				m_bProcess = false;
				g_bMonitorFlag = true;
			}
		}
	}
}