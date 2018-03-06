/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectThreadSafe.h
* @brief	This Program is DirectThreadSafe Header File.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-10	v1.00a	alopex	Create This File.
*/
#pragma once

#ifndef __DIRECTTHREADSAFE_H_
#define __DIRECTTHREADSAFE_H_

//Include DirectCommon Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef  DIRECTGRAPHICS_EXPORTS
#define DIRECTTHREADSAFE_API	__declspec(dllexport)
#else
#define DIRECTTHREADSAFE_API	__declspec(dllimport)
#endif

//Class
class DirectThreadSafe
{
private:
	CRITICAL_SECTION* m_pCriticalSection;	//CriticalSection Variable
	bool m_bThreadSafe;						//CriticalSection ThreadSafe Use Variable

public:
	DirectThreadSafe(const CRITICAL_SECTION* pCriticalSection, const bool bThreadSafe);
	~DirectThreadSafe();
};

#endif