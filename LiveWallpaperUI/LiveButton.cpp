/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveButton.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-04
*/
#include "LiveButton.h"

//LiveUI CLiveBackPanel->>Button类

//------------------------------------------------------------------
// @Function:	 CLiveButton()
// @Purpose: CLiveButton构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveButton::CLiveButton()
{
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 ~CLiveButton()
// @Purpose: CLiveButton析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveButton::~CLiveButton()
{
	m_iMage.Destroy();
}

//------------------------------------------------------------------
// @Function:	 CLiveButton()
// @Purpose: CLiveButton构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveButton::CLiveButton(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 LiveButtonGetPosX()
// @Purpose: CLiveButton获取X坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CLiveButton::LiveButtonGetPosX()
{
	return m_nPosX;
}

//------------------------------------------------------------------
// @Function:	 LiveButtonGetPosY()
// @Purpose: CLiveButton获取Y坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CLiveButton::LiveButtonGetPosY()
{
	return m_nPosY;
}

//------------------------------------------------------------------
// @Function:	 LiveButtonGetWidth()
// @Purpose: CLiveButton获取宽度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CLiveButton::LiveButtonGetWidth()
{
	return m_nWidth;
}

//------------------------------------------------------------------
// @Function:	 LiveButtonGetHeight()
// @Purpose: CLiveButton获取高度
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
int CLiveButton::LiveButtonGetHeight()
{
	return m_nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveButton_SetWindow()
// @Purpose: CLiveButton设置窗口坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveButton::LiveButton_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveButton_Convert_A2W()
// @Purpose: CLiveButton字符转换小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveButton::LiveButton_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
{
	int nSrcSize = 0;
	wchar_t* pwszArr = NULL;

	nSrcSize = ::MultiByteToWideChar(CP_ACP, 0, szArr, -1, NULL, NULL);
	if (nSize < nSrcSize + 1)
	{
		return FALSE;
	}

	pwszArr = new wchar_t[nSrcSize + 1];
	memset(pwszArr, 0, (nSrcSize + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, szArr, -1, (LPWSTR)pwszArr, nSrcSize);

	memset((void*)wszArr, 0, nSize * sizeof(wchar_t));
	memcpy_s((void*)wszArr, nSize * sizeof(wchar_t), pwszArr, (nSrcSize + 1) * sizeof(wchar_t));

	delete[] pwszArr;
	pwszArr = NULL;

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveButtonInit()
// @Purpose: CLiveButton初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveButton::LiveButtonInit(LPCSTR szFile)
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
	strcat_s(chArr, szFile);

	BOOL bRet = FALSE;

	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveButton_Convert_A2W(chArr, m_tcFilePath, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	HRESULT hr;

	hr = m_iMage.Load(m_tcFilePath);
	if (FAILED(hr))
	{
		return FALSE;
	}

	if (m_iMage.GetBPP() == 32)//包含Alpha通道
	{
		for (int i = 0; i < m_iMage.GetWidth(); i++)
		{
			for (int j = 0; j < m_iMage.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_iMage.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveButtonPaint()
// @Purpose: CLiveButton重绘
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveButton::LiveButtonPaint(HDC& hDC)
{
	m_iMage.Draw(hDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight);
}