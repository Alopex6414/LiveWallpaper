/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumIni.cpp
* @brief	This Program is PlumIni DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-17	v1.00a	alopex	Create Project.
*/
#include "PlumIni.h"

//This Class is Read & Write for INI File(.ini文件读写)

//------------------------------------------------------------------
// @Function:	 CPlumIni()
// @Purpose: CPlumIni构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumIni::CPlumIni()
{
}

//------------------------------------------------------------------
// @Function:	 ~CPlumIni()
// @Purpose: CPlumIni析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumIni::~CPlumIni()
{
}

//-----------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PlumIniReadStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrDefault, char** ppStrValue)
// @Purpose: CPlumIni读取Ini文件字符串
// @Since: v1.00a
// @Para: char* pStrFileName	//文件名称(外部管理内存)
// @Para: char* pStrSection		//文件关键段(外部管理内存)
// @Para: char* pStrKey			//文件关键字(外部管理内存)
// @Para: char* pStrDefault		//文件默认值(外部管理内存)
// @Para: char** ppStrValue		//字符串返回值(需要释放!)(初始化传入NULL)
// @Return: bool				//布尔型 true:成功 false:失败
//-----------------------------------------------------------------------------------------------------------------------------------
bool CPlumIni::PlumIniReadStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrDefault, char** ppStrValue)
{
	bool bResult = false;
	char strData[MAX_PATH];
	int nCount = 0;
	DWORD dwCount = 0;

	memset(strData, 0, MAX_PATH);

	dwCount = GetPrivateProfileStringA(pStrSection, pStrKey, pStrDefault, strData, MAX_PATH - 1, pStrFileName);
	if (dwCount > 0)
	{
		nCount = strlen(strData);
		*ppStrValue = new char[nCount + 1];
		memset(*ppStrValue, 0, nCount + 1);
		strcpy_s(*ppStrValue, nCount + 1, strData);
		bResult = true;
	}
	else
	{
		nCount = strlen(pStrDefault);
		*ppStrValue = new char[nCount + 1];
		memset(*ppStrValue, 0, nCount + 1);
		strcpy_s(*ppStrValue, nCount + 1, pStrDefault);
		bResult = false;
	}

	return bResult;
}

//----------------------------------------------------------------------------------------------------------------------
// @Function:	 PlumIniReadIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nDefault, int* pValue)
// @Purpose: CPlumIni读取Ini文件值
// @Since: v1.00a
// @Para: char* pStrFileName	//文件名称(外部管理内存)
// @Para: char* pStrSection		//文件关键段(外部管理内存)
// @Para: char* pStrKey			//文件关键字(外部管理内存)
// @Para: int nStrDefault		//文件默认值
// @Para: int* pValue			//整型返回值
// @Return: bool				//布尔型 true:成功 false:失败
//----------------------------------------------------------------------------------------------------------------------
bool CPlumIni::PlumIniReadIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nDefault, int* pValue)
{
	bool bResult = false;
	char** ppArray = NULL;

	bResult = PlumIniReadStringKeyValue(pStrFileName, pStrSection, pStrKey, (char*)"", ppArray);
	if (bResult == true)
	{
		*pValue = atoi(*ppArray);
		if (*ppArray)
		{
			delete[](*ppArray);
			*ppArray = NULL;
		}
	}
	else
	{
		*pValue = nDefault;
		if (*ppArray)
		{
			delete[](*ppArray);
			*ppArray = NULL;
		}
	}

	return bResult;
}

//-----------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PlumIniWriteStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char** ppStrValue)
// @Purpose: CPlumIni写入Ini文件字符串
// @Since: v1.00a
// @Para: char* pStrFileName	//文件名称(外部管理内存)
// @Para: char* pStrSection		//文件关键段(外部管理内存)
// @Para: char* pStrKey			//文件关键字(外部管理内存)
// @Para: char* pStrValue		//写入字符串(外部管理内存)
// @Return: bool				//布尔型 true:成功 false:失败
//-----------------------------------------------------------------------------------------------------------------------------------
bool CPlumIni::PlumIniWriteStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrValue)
{
	bool bResult = false;
	DWORD dwCount = 0;

	dwCount = WritePrivateProfileStringA(pStrSection, pStrKey, pStrValue, pStrFileName);
	if (dwCount != 0)
	{
		bResult = true;
	}
	else
	{
		bResult = false;
	}

	return bResult;
}

//-----------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PlumIniWriteIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nValue)
// @Purpose: CPlumIni写入Ini文件整型
// @Since: v1.00a
// @Para: char* pStrFileName	//文件名称(外部管理内存)
// @Para: char* pStrSection		//文件关键段(外部管理内存)
// @Para: char* pStrKey			//文件关键字(外部管理内存)
// @Para: int nValue			//写入整型数值
// @Return: bool				//布尔型 true:成功 false:失败
//-----------------------------------------------------------------------------------------------------------------------------------
bool CPlumIni::PlumIniWriteIntKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, int nValue)
{
	bool bResult = false;
	char strValue[32];

	memset(strValue, 0, 32);
	_snprintf_s(strValue, sizeof(strValue), _TRUNCATE, "%d", nValue);
	bResult = PlumIniWriteStringKeyValue(pStrFileName, pStrSection, pStrKey, strValue);

	return bResult;
}