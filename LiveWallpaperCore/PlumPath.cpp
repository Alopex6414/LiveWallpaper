/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumPath.cpp
* @brief	This Program is PlumPath DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-18	v1.00a	alopex	Create Project.
*/
#include "PlumPath.h"

//This Class is FilePath Correlation(~路径相关...)

//------------------------------------------------------------------
// @Function:	 CPlumPath()
// @Purpose: CPlumPath构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumPath::CPlumPath()
{
}

//------------------------------------------------------------------
// @Function:	 ~CPlumPath()
// @Purpose: CPlumPath析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumPath::~CPlumPath()
{
}

//------------------------------------------------------------------
// @Function:	 PlumPathGetPath()
// @Purpose: CPlumPath获取当前文件路径
// @Since: v1.00a
// @Para: char** pArr	//文件路径(需要释放!)
// @Return: None
//------------------------------------------------------------------
void CPlumPath::PlumPathGetPath(char** ppArr)
{
	char* pTemp = NULL;

	*ppArr = new char[MAX_PATH];
	memset(*ppArr, 0, MAX_PATH);

	GetModuleFileNameA(NULL, *ppArr, MAX_PATH);
	pTemp = strrchr(*ppArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}
}

//------------------------------------------------------------------
// @Function:	 PlumPathGetParentPath()
// @Purpose: CPlumPath获取当前文件路径
// @Since: v1.00a
// @Para: char** pArr	//文件路径(需要释放!)
// @Para: int nLevel	//查询前多少层级
// @Return: None
//------------------------------------------------------------------
void CPlumPath::PlumPathGetParentPath(char** ppArr, int nLevel)
{
	char* pTemp = NULL;

	*ppArr = new char[MAX_PATH];
	memset(*ppArr, 0, MAX_PATH);

	GetModuleFileNameA(NULL, *ppArr, MAX_PATH);

	for (int i = 0; i < nLevel; ++i)
	{
		pTemp = NULL;
		pTemp = strrchr(*ppArr, '\\');
		if (pTemp != NULL)
		{
			*pTemp = '\0';
		}
	}

}