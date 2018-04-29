/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveLua.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-27
*/
#pragma once

#ifndef __LIVELUA_H_
#define __LIVELUA_H_

//Include Common Header File
#include "Common.h"

//Include Lua Header File
#include "lua.hpp"

//Class Definition
class CLiveLua
{
private:
	lua_State * L;

	char m_chFile[MAX_PATH];
	char m_chPath[MAX_PATH];

public:
	CLiveLua(const char* szFile);
	~CLiveLua();

	BOOL LiveLuaInit();
	void LiveLuaGetGlobalInt(const char* szVar, int& nValue);
	void LiveLuaGetGlobalFloat(const char* szVar, float& fValue);
	void LiveLuaGetGlobalDouble(const char* szVar, double& dValue);

};

#endif // !__LIVELUA_H_

