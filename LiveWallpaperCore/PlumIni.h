/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumIni.h
* @brief	This Program is PlumIni DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-17	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __PLUMINI_H_
#define __PLUMINI_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>

//Macro Definition
#ifdef	PLUMINI_EXPORTS
#define PLUMINI_API	__declspec(dllexport)
#else
#define PLUMINI_API	__declspec(dllimport)
#endif

//Class Definition
class CPlumIni
{
private:


public:
	CPlumIni();
	~CPlumIni();

	static bool PlumIniReadStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrDefault, char** ppStrValue);
	static bool PlumIniReadIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nDefault, int* pValue);
	static bool PlumIniWriteStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrValue);
	static bool PlumIniWriteIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nValue);
};

#endif