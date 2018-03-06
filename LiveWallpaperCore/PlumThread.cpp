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
// @Purpose: PlumThreadBase���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumThreadBase::CPlumThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 ~CPlumThreadBase()
// @Purpose: PlumThreadBase��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumThreadBase::~CPlumThreadBase()
{
}

//------------------------------------------------------------------
// @Function:	 CPlumThread()
// @Purpose: PlumThread���캯��
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
// @Purpose: PlumThread��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumThread::~CPlumThread()
{
}

//------------------------------------------------------------------
// @Function:	 CPlumThread(CWinThreadBase* pThreadBase)
// @Purpose: PlumThread���캯��
// @Since: v1.00a
// @Para: CPlumThreadBase* pThreadBase	//�̻߳���ָ��
// @Return: None
//------------------------------------------------------------------
CPlumThread::CPlumThread(CPlumThreadBase* pThreadBase)
{
	m_pThreadBase = pThreadBase;
	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadInit(bool bSuspend)
// @Purpose: PlumThread�̳߳�ʼ��
// @Since: v1.00a
// @Para: bool bSuspend	//�����Ƿ����
// @Return: None
//------------------------------------------------------------------
bool WINAPI CPlumThread::PlumThreadInit(bool bSuspend)
{
	//�߳���������״̬
	if (m_bThreadRun) return true;

	//�̳߳�ʼ������
	if (bSuspend)
	{
		m_hThread = CreateThread(NULL, 0, PlumThreadProc, this, CREATE_SUSPENDED, &m_dwThreadID);
	}
	else
	{
		m_hThread = CreateThread(NULL, 0, PlumThreadProc, this, 0, &m_dwThreadID);
	}

	//�߳�״̬
	m_bThreadRun = (m_hThread != NULL);

	return m_bThreadRun;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadSetPriority(int nPriority)
// @Purpose: PlumThread�߳��������ȼ�
// @Since: v1.00a
// @Para: int nPriority		//�߳����ȼ�
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadSetPriority(int nPriority)
{
	SetThreadPriority(m_hThread, nPriority);	//�߳����ȼ�
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThread�߳�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadRun()
{
	//�߳�δ����
	if (!m_bThreadRun) return;

	//�߳�����
	if (m_pThreadBase != NULL)
	{
		m_pThreadBase->PlumThreadRun();
	}

	m_bThreadRun = false;
}

//------------------------------------------------------------------
// @Function:	 PlumThreadJoin()
// @Purpose: PlumThread�̵߳ȴ�
// @Since: v1.00a
// @Para: int nTimeOut	//�ȴ�ʱ��
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadJoin(int nTimeOut)
{
	//�߳�δ�����ɹ����߳�δ����
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	//�̵߳ȴ�ʱ��
	if (nTimeOut < 0)
	{
		nTimeOut = INFINITE;
	}

	WaitForSingleObject(m_hThread, nTimeOut);
}

//------------------------------------------------------------------
// @Function:	 PlumThreadResume()
// @Purpose: PlumThread�ָ̻߳�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadResume()
{
	//�߳�δ�����ɹ����߳�δ����
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	ResumeThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 PlumThreadSuspend()
// @Purpose: PlumThread�̹߳���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CPlumThread::PlumThreadSuspend()
{
	//�߳�δ�����ɹ����߳�δ����
	if (m_hThread == NULL || !m_bThreadRun)
	{
		return;
	}

	SuspendThread(m_hThread);
}

//------------------------------------------------------------------
// @Function:	 PlumThreadTerminate(DWORD dwExitCode)
// @Purpose: PlumThread�߳��˳�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool WINAPI CPlumThread::PlumThreadTerminate(DWORD dwExitCode)
{
	//�߳�δ�����ɹ����߳�δ����
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
// @Purpose: PlumThread�߳��˳�
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
// @Purpose: PlumThread�߳�ID��ȡ
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
// @Purpose: PlumThread�̴߳�����
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