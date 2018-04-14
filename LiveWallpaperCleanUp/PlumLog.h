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
	CRITICAL_SECTION m_csThreadSafe;		//Critical Section(~�̰߳�ȫ)

public:
	bool m_bIsUseLog;		//Use PlumLog Flag(~�Ƿ�ʹ��)
	FILE* m_fp;				//File Pointer(~�ļ�ָ��)

public:
	CPlumLog();				//Construction Function(~���캯��)
	~CPlumLog();			//Destruction Function(~��������)

	//����
	CPlumLog(bool bIsUseLog);				//Construction Function(~���캯��)

	//����
	virtual bool PlumLogGetUse() const;		//PlumLog Get UseLog(~��ȡʹ����־)

	//����
	virtual void PlumLogSetUse(bool IsUseLog);	//PlumLog Set UseLog(~����ʹ����־)

	//��ʼ��
	virtual void PlumLogInit();					//PlumLog Initialize(~��ʼ��)(ͨ�ó�ʼ��<������>)

	//�˳�
	virtual void PlumLogExit();					//PlumLog Exit(~�˳�)
	virtual void PlumLogClose();				//PlumLog Close(~�ر��ļ�ϵͳ)<��Ҫ����Exit��Close>

	//д��
	virtual void PlumLogWrite(LPCSTR lpcstr);					//Plum Write(~д��)(ASCII)
	virtual void PlumLogWriteElongate(LPCSTR lpcstr, ...);		//Plum Write(~д��)(���������)
	virtual void PlumLogWriteNormal(LPCSTR lpcstr, ...);		//Plum Write(~д��)(��׼��ʽ)<ʱ��/�߳�>
	virtual void PlumLogWriteExtend(LPCSTR lpcstr, ...);		//Plum Write(~д��)(��չ��ʽ)<ʱ��/�߳�/�ļ�/�к�>
	virtual void PlumLogWriteLine(LPCSTR lpcstr);				//Plum Write Line(~д��)(ASCII)
	virtual void PlumLogWriteLineElongate(LPCSTR lpcstr, ...);	//Plum Write Line(~д��)(���������)
	virtual void PlumLogWriteLineNormal(LPCSTR lpcstr, ...);	//Plum Write Line(~д��)(��׼��ʽ)<ʱ��/�߳�>
	virtual void PlumLogWriteLineExtend(LPCSTR lpcstr, ...);	//Plum Write Line(~д��)(��չ��ʽ)<ʱ��/�߳�/�ļ�/�к�>

	virtual void PlumLogWriteExtend(LPCSTR file, LONG line, LPCSTR lpcstr, ...);		//Plum Write(~д��)(��չ��ʽ)<ʱ��/�߳�/�ļ�/�к�>(����__FILE__,__LINE__)
	virtual void PlumLogWriteLineExtend(LPCSTR file, LONG line, LPCSTR lpcstr, ...);	//Plum Write Line(~д��)(��չ��ʽ)<ʱ��/�߳�/�ļ�/�к�>(����__FILE__,__LINE__)

protected:
	virtual void WriteLineComputerName();	//PlumLog Write Line Computer Name(~д����������)
	virtual void WriteLineUserName();		//PlumLog Write Line User Name(~д���û�����)
	virtual void WriteLineWindowsVision();	//PlumLog Write Line Windows Vision(~д��Windows�汾)
	virtual void WriteLineProcessID();		//PlumLog Write Line Process ID(~д�����ID)
	virtual void WriteLineCurrentTime();	//PlumLog Write Line Current Time(~д�뵱ǰʱ��)

};

#endif // !__PLUMLOG_H_

