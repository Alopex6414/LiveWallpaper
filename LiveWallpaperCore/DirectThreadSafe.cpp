/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectThreadSafe.cpp
* @brief	This Program is DirectThreadSafe Header File.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-10	v1.00a	alopex	Create This File.
*/
#include "DirectThreadSafe.h"

//DirectThreadSafe构造函数
DirectThreadSafe::DirectThreadSafe(const CRITICAL_SECTION* pCriticalSection, const bool bThreadSafe)
{
	m_pCriticalSection = (CRITICAL_SECTION*)pCriticalSection;
	m_bThreadSafe = bThreadSafe;

	if (m_bThreadSafe) EnterCriticalSection(m_pCriticalSection);
}

//DirectThreadSafe析构函数
DirectThreadSafe::~DirectThreadSafe()
{
	if (m_bThreadSafe) LeaveCriticalSection(m_pCriticalSection);
}