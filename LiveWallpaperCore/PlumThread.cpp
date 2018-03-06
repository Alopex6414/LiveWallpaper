/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumThread.cpp
* @brief	This Program is PlumThread DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-14	v1.00a	alopex	Create Project.
*/
#include "PlumThread.h"

//------------------------------------------------------------------
// @Function:	 CPlumThreadBase()
// @Purpose: PlumThreadBase构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumThreadBase::CPlumThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 ~CPlumThreadBase()
// @Purpose: PlumThreadBase析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumThreadBase::~CPlumThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 CPlumThread()
// @Purpose: PlumThread构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumThread::CPlumThread()
{
	m_pThreadBase = NULL;
	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 ~CWinThread()
// @Purpose: PlumThread析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumThread::~CPlumThread()
{
}

//------------------------------------------------------------------
// @Function:	 CPlumThread(CWinThreadBase* pThreadBase)
// @Purpose: PlumThread构造函数
// @Since: v1.00a
// @Para: CPlumThreadBase* pThreadBase	//线程基类指针
// @Return: None
//------------------------------------------------------------------
CPlumThread::CPlumThread(CPlumThreadBase* pThreadBase)
{
	m_pThreadBase = pThreadBase;
	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadInit(bool bSuspend)
// @Purpose: PlumThread线程初始化
// @Since: v1.00a
// @Para: bool bSuspend	//运行是否挂起
// @Return: None
//------------------------------------------------------------------
bool WINAPI CPlumThread::PlumThreadInit(bool bSuspend)
{
	//线程正在运行状态
	if (m_bThreadRun) return true;

	//线程初始化挂起
	if (bSuspend)
	{
		m_hThread = CreateThread(NULL, 0, PlumThreadProc, this, CREATE_SUSPENDED, &m_dwThreadID);
	}
	else
	{
		m_hThread = CreateThread(NULL, 0, PlumThreadProc, this, 0, &m_dwThreadID);
	}

	//线程状态
	m_bThreadRun = (m_hThread != NULL);

	return m_bThreadRun;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadSetPriority(int nPriority)
// @Purpose: PlumThread线程设置优先级
// @Since: v1.00a
// @Para: int nPriority		//线程优先级
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadSetPriority(int nPriority)
{
	SetThreadPriority(m_hThread, nPriority);	//线程优先级
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThread线程运行
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadRun()
{
	//线程未运行
	if (!m_bThreadRun) return;

	//线程运行
	if (m_pThreadBase != NULL)
	{
		m_pThreadBase->PlumThreadRun();
	}

	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadJoin()
// @Purpose: PlumThread线程等待
// @Since: v1.00a
// @Para: int nTimeOut	//等待时间
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadJoin(int nTimeOut)
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	//线程等待时间
	if (nTimeOut < 0)
	{
		nTimeOut = INFINITE;
	}

	WaitForSingleObject(m_hThread, nTimeOut);
}

//------------------------------------------------------------------
// @Function:	 PlumThreadResume()
// @Purpose: PlumThread线程恢复
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadResume()
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	ResumeThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 PlumThreadSuspend()
// @Purpose: PlumThread线程挂起
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadSuspend()
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	SuspendThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 PlumThreadTerminate(DWORD dwExitCode)
// @Purpose: PlumThread线程退出
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool WINAPI CPlumThread::PlumThreadTerminate(DWORD dwExitCode)
{
	//线程未创建成功或线程未运行
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return true;
	}

	if (TerminateThread(m_hThread, dwExitCode))
	{
		CloseHandle(m_hThread);
		return true;
	}

	return false;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadExit()
// @Purpose: PlumThread线程退出
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadExit()
{
	if (m_hThread == NULL)
	{
		return;
	}

	CloseHandle(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 PlumThreadGetID()
// @Purpose: PlumThread线程ID获取
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DWORD WINAPI CPlumThread::PlumThreadGetID() const
{
	return m_dwThreadID;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadProc(LPVOID pThreadPara)
// @Purpose: PlumThread线程处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DWORD WINAPI CPlumThread::PlumThreadProc(LPVOID pThreadPara)
{
	CPlumThread* pThread = (CPlumThread*)(pThreadPara);

	pThread->PlumThreadRun();

	return 0;
}