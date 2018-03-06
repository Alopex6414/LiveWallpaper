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

//DirectThreadSafe���캯��
DirectThreadSafe::DirectThreadSafe(const CRITICAL_SECTION* pCriticalSection, const bool bThreadSafe)
{
	m_pCriticalSection = (CRITICAL_SECTION*)pCriticalSection;
	m_bThreadSafe = bThreadSafe;

	if (m_bThreadSafe) EnterCriticalSection(m_pCriticalSection);
}

//DirectThreadSafe��������
DirectThreadSafe::~DirectThreadSafe()
{
	if (m_bThreadSafe) LeaveCriticalSection(m_pCriticalSection);
}