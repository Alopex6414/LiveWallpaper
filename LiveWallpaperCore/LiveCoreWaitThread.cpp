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
// @Purpose: CLiveCoreWaitThread���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWaitThread::CLiveCoreWaitThread()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreWaitThread()
// @Purpose: CLiveCoreWaitThread��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWaitThread::~CLiveCoreWaitThread()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThreadRun�ȴ��߳�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CLiveCoreWaitThread::PlumThreadRun()
{
	m_cLiveCoreWait.LiveCoreWaitInit();

	//while (true)	//������Ҫ����Ƴ��ȴ�������...
	//{
		m_cLiveCoreWait.LiveCoreWaitUpdate();
		m_cLiveCoreWait.LiveCoreWaitRender();
	//}
}