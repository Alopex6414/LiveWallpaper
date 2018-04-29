/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveLua.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-27
*/
#include "LiveLua.h"

//LiveLua <Lua Script>

//------------------------------------------------------------------
// @Function:	 CLiveLua()
// @Purpose: CLiveLua构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveLua::CLiveLua(const char* szFile)
{
	int nSize = 0;

	nSize = strlen(szFile);

	L = luaL_newstate();
	memset(m_chFile, 0, MAX_PATH);
	memset(m_chPath, 0, MAX_PATH);
	memcpy_s(m_chFile, MAX_PATH, szFile, nSize);
}

//------------------------------------------------------------------
// @Function:	 ~CLiveLua()
// @Purpose: CLiveLua析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveLua::~CLiveLua()
{
	if (L)
	{
		lua_close(L);
	}
}

//------------------------------------------------------------------
// @Function:	 LiveLuaInit()
// @Purpose: CLiveLua初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveLua::LiveLuaInit()
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	pTemp = strrchr(chArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}

	strcat_s(chArr, "\\");
	strcat_s(chArr, m_chFile);
	memcpy_s(m_chPath, MAX_PATH, chArr, MAX_PATH);

	int nRet = -1;

	nRet = luaL_loadfile(L, chArr);
	if (nRet)
	{
		return FALSE;
	}

	nRet = lua_pcall(L, 0, 0, 0);
	if (nRet)
	{
		return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveLuaGetGlobalInt()
// @Purpose: CLiveLua获取全局整型
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveLua::LiveLuaGetGlobalInt(const char* szVar, int& nValue)
{
	lua_getglobal(L, szVar);
	nValue = (int)lua_tonumber(L, -1);
}

//------------------------------------------------------------------
// @Function:	 LiveLuaGetGlobalFloat()
// @Purpose: CLiveLua获取全局浮点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveLua::LiveLuaGetGlobalFloat(const char* szVar, float& fValue)
{
	lua_getglobal(L, szVar);
	fValue = (float)lua_tonumber(L, -1);
}

//------------------------------------------------------------------
// @Function:	 LiveLuaGetGlobalDouble()
// @Purpose: CLiveLua获取全局浮点
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveLua::LiveLuaGetGlobalDouble(const char* szVar, double& dValue)
{
	lua_getglobal(L, szVar);
	dValue = (double)lua_tonumber(L, -1);
}