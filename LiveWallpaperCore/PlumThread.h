/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumThread.h
* @brief	This Program is PlumThread DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-14	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __PLUMTHREAD_H_
#define __PLUMTHREAD_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <tchar.h>

//Macro Definition
#ifdef PLUMTHREAD_EXPORTS
#define PLUMTHREAD_API	__declspec(dllexport)
#else
#define PLUMTHREAD_API	__declspec(dllimport)
#endif

//Class Definition
//CPlumThreadBase����
class CPlumThreadBase
{
private:

public:
	CPlumThreadBase();													//����
	virtual ~CPlumThreadBase();											//����
	virtual void WINAPI PlumThreadRun() = 0;							//���麯��
};

//CPlumThread������
class CPlumThread :public CPlumThreadBase
{
private:
	HANDLE m_hThread;													//�߳̾��
	DWORD m_dwThreadID;													//�̺߳�
	volatile bool m_bThreadRun;											//�߳�����
	CPlumThreadBase* m_pThreadBase;										//�̻߳���ָ��

private:
	static DWORD WINAPI PlumThreadProc(LPVOID pThreadPara);				//�̴߳�����(��̬)

public:
	CPlumThread();														//����
	~CPlumThread();														//����
	CPlumThread(CPlumThreadBase* pThreadBase);							//����

	DWORD WINAPI PlumThreadGetID() const;								//�߳�ID��ȡ

	virtual bool WINAPI PlumThreadInit(bool bSuspend = false);			//�̳߳�ʼ��(����:true)
	virtual void WINAPI PlumThreadSetPriority(int nPriority);			//�߳��������ȼ�(THREAD_PRIORITY_ABOVE_NORMAL)
	virtual void WINAPI PlumThreadRun();								//�߳�����(��д)
	virtual void WINAPI PlumThreadJoin(int nTimeOut = -1);				//�̵߳ȴ�����
	virtual void WINAPI PlumThreadResume();								//�ָ̻߳�
	virtual void WINAPI PlumThreadSuspend();							//�̹߳���
	virtual bool WINAPI PlumThreadTerminate(DWORD dwExitCode);			//�߳���ֹ
	virtual void WINAPI PlumThreadExit();								//�߳��˳�
};

#endif