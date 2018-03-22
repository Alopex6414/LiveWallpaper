/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumLog.h
* @brief	This Program is PlumLog DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2018-1-26	v1.00a	alopex	Create Project.
* @date		2018-3-20	v1.01a	alopex	Modify Code Bug.
*/
#pragma once

#ifndef __PLUMLOG_H_
#define __PLUMLOG_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>
#include <stdarg.h>

//Macro Definition
#ifdef	PLUMLOG_EXPORTS
#define PLUMLOG_API	__declspec(dllexport)
#else
#define PLUMLOG_API	__declspec(dllimport)
#endif

//Class Definition
class CPlumLog
{
private:
	CRITICAL_SECTION m_csThreadSafe;		//Critical Section(~线程安全)

public:
	bool m_bIsUseLog;		//Use PlumLog Flag(~是否使用)
	FILE* m_fp;				//File Pointer(~文件指针)

public:
	CPlumLog();				//Construction Function(~构造函数)
	~CPlumLog();			//Destruction Function(~析构函数)

	//构造
	CPlumLog(bool bIsUseLog);				//Construction Function(~构造函数)

	//访问
	virtual bool PlumLogGetUse() const;		//PlumLog Get UseLog(~获取使用日志)

	//控制
	virtual void PlumLogSetUse(bool IsUseLog);	//PlumLog Set UseLog(~设置使用日志)

	//初始化
	virtual void PlumLogInit();					//PlumLog Initialize(~初始化)(通用初始化<可重载>)

	//退出
	virtual void PlumLogExit();					//PlumLog Exit(~退出)
	virtual void PlumLogClose();				//PlumLog Close(~关闭文件系统)<需要调用Exit或Close>

	//写入
	virtual void PlumLogWrite(LPCSTR lpcstr);					//Plum Write(~写入)(ASCII)
	virtual void PlumLogWriteElongate(LPCSTR lpcstr, ...);		//Plum Write(~写入)(变参数长度)
	virtual void PlumLogWriteNormal(LPCSTR lpcstr, ...);		//Plum Write(~写入)(标准格式)<时间/线程>
	virtual void PlumLogWriteExtend(LPCSTR lpcstr, ...);		//Plum Write(~写入)(扩展格式)<时间/线程/文件/行号>
	virtual void PlumLogWriteLine(LPCSTR lpcstr);				//Plum Write Line(~写入)(ASCII)
	virtual void PlumLogWriteLineElongate(LPCSTR lpcstr, ...);	//Plum Write Line(~写入)(变参数长度)
	virtual void PlumLogWriteLineNormal(LPCSTR lpcstr, ...);	//Plum Write Line(~写入)(标准格式)<时间/线程>
	virtual void PlumLogWriteLineExtend(LPCSTR lpcstr, ...);	//Plum Write Line(~写入)(扩展格式)<时间/线程/文件/行号>

	virtual void PlumLogWriteExtend(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		//Plum Write(~写入)(扩展格式)<时间/线程/文件/行号>(传入__FILE__,__LINE__)
	virtual void PlumLogWriteLineExtend(LPCSTR file, LONG line, LPCSTR lpcstr, ...);	//Plum Write Line(~写入)(扩展格式)<时间/线程/文件/行号>(传入__FILE__,__LINE__)

protected:
	virtual void WriteLineComputerName();	//PlumLog Write Line Computer Name(~写入计算机名称)
	virtual void WriteLineUserName();		//PlumLog Write Line User Name(~写入用户名称)
	virtual void WriteLineWindowsVision();	//PlumLog Write Line Windows Vision(~写入Windows版本)
	virtual void WriteLineProcessID();		//PlumLog Write Line Process ID(~写入进程ID)
	virtual void WriteLineCurrentTime();	//PlumLog Write Line Current Time(~写入当前时间)

};

#endif // !__PLUMLOG_H_

