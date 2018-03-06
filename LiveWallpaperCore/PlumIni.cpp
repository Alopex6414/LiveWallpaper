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

//This Class is Read & Write for INI File(.ini�ļ���д)

//------------------------------------------------------------------
// @Function:	 CPlumIni()
// @Purpose: CPlumIni���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumIni::CPlumIni()
{
}

//------------------------------------------------------------------
// @Function:	 ~CPlumIni()
// @Purpose: CPlumIni��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumIni::~CPlumIni()
{
}

//-----------------------------------------------------------------------------------------------------------------------------------
// @Function:	 PlumIniReadStringKeyValue(char* pStrFileName, char* pStrSection, char* pStrKey, char* pStrDefault, char** ppStrValue)
// @Purpose: CPlumIni��ȡIni�ļ��ַ���
// @Since: v1.00a
// @Para: char* pStrFileName	//�ļ�����(�ⲿ�����ڴ�)
// @Para: char* pStrSection		//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: char* pStrKey			//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: char* pStrDefault		//�ļ�Ĭ��ֵ(�ⲿ�����ڴ�)
// @Para: char** ppStrValue		//�ַ�������ֵ(��Ҫ�ͷ�!)(��ʼ������NULL)
// @Return: bool				//������ true:�ɹ� false:ʧ��
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
// @Purpose: CPlumIni��ȡIni�ļ�ֵ
// @Since: v1.00a
// @Para: char* pStrFileName	//�ļ�����(�ⲿ�����ڴ�)
// @Para: char* pStrSection		//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: char* pStrKey			//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: int nStrDefault		//�ļ�Ĭ��ֵ
// @Para: int* pValue			//���ͷ���ֵ
// @Return: bool				//������ true:�ɹ� false:ʧ��
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
// @Purpose: CPlumIniд��Ini�ļ��ַ���
// @Since: v1.00a
// @Para: char* pStrFileName	//�ļ�����(�ⲿ�����ڴ�)
// @Para: char* pStrSection		//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: char* pStrKey			//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: char* pStrValue		//д���ַ���(�ⲿ�����ڴ�)
// @Return: bool				//������ true:�ɹ� false:ʧ��
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
// @Purpose: CPlumIniд��Ini�ļ�����
// @Since: v1.00a
// @Para: char* pStrFileName	//�ļ�����(�ⲿ�����ڴ�)
// @Para: char* pStrSection		//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: char* pStrKey			//�ļ��ؼ���(�ⲿ�����ڴ�)
// @Para: int nValue			//д��������ֵ
// @Return: bool				//������ true:�ɹ� false:ʧ��
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