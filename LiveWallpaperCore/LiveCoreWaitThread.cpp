/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreWaitThread.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-05-02
*/
#include "LiveCore.h"
#include "LiveCoreWaitThread.h"

//------------------------------------------------------------------
// @Function:	 CLiveCoreWaitThread()
// @Purpose: CLiveCoreWaitThread构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWaitThread::CLiveCoreWaitThread()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreWaitThread()
// @Purpose: CLiveCoreWaitThread析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWaitThread::~CLiveCoreWaitThread()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThreadRun等待线程
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CLiveCoreWaitThread::PlumThreadRun()
{
	m_cLiveCoreWait.LiveCoreWaitInit();

	while (true)	//这里需要添加推出等待的条件...
	{
		m_cLiveCoreWait.LiveCoreWaitUpdate();
		m_cLiveCoreWait.LiveCoreWaitRender();

		if (m_cLiveCoreWait.m_bUnpackStop)
		{
			if (m_cLiveCoreWait.m_bSakuraStop)
			{
				break;
			}
		}
		
		EnterCriticalSection(&g_csWait);
		if (!g_bWaitFlag)
		{
			m_cLiveCoreWait.m_bUnpackStop = true;
			//LeaveCriticalSection(&g_csWait);
			//break;
		}
		LeaveCriticalSection(&g_csWait);
	}
}