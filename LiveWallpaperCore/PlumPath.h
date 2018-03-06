/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumPath.h
* @brief	This Program is PlumPath DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-18	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __PLUMPATH_H_
#define __PLUMPATH_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>
#include <stdlib.h>

//Macro Definition
#ifdef	PLUMPATH_EXPORTS
#define PLUMPATH_API	__declspec(dllexport)
#else
#define PLUMPATH_API	__declspec(dllimport)
#endif

//Class Definition
class CPlumPath
{
private:


public:
	CPlumPath();
	~CPlumPath();

	virtual void PlumPathGetPath(char** ppArr);
	virtual void PlumPathGetParentPath(char** ppArr, int nLevel);
};

#endif