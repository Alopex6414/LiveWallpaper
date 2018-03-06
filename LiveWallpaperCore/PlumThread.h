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
//CPlumThreadBase基类
class CPlumThreadBase
{
private:

public:
	CPlumThreadBase();													//构造
	virtual ~CPlumThreadBase();											//析构
	virtual void WINAPI PlumThreadRun() = 0;							//纯虚函数
};

//CPlumThread派生类
class CPlumThread :public CPlumThreadBase
{
private:
	HANDLE m_hThread;													//线程句柄
	DWORD m_dwThreadID;													//线程号
	volatile bool m_bThreadRun;											//线程运行
	CPlumThreadBase* m_pThreadBase;										//线程基类指针

private:
	static DWORD WINAPI PlumThreadProc(LPVOID pThreadPara);				//线程处理函数(静态)

public:
	CPlumThread();														//构造
	~CPlumThread();														//析构
	CPlumThread(CPlumThreadBase* pThreadBase);							//构造

	DWORD WINAPI PlumThreadGetID() const;								//线程ID获取

	virtual bool WINAPI PlumThreadInit(bool bSuspend = false);			//线程初始化(挂起:true)
	virtual void WINAPI PlumThreadSetPriority(int nPriority);			//线程设置优先级(THREAD_PRIORITY_ABOVE_NORMAL)
	virtual void WINAPI PlumThreadRun();								//线程运行(重写)
	virtual void WINAPI PlumThreadJoin(int nTimeOut = -1);				//线程等待结束
	virtual void WINAPI PlumThreadResume();								//线程恢复
	virtual void WINAPI PlumThreadSuspend();							//线程挂起
	virtual bool WINAPI PlumThreadTerminate(DWORD dwExitCode);			//线程终止
	virtual void WINAPI PlumThreadExit();								//线程退出
};

#endif