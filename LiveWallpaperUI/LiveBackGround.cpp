/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveBackGround.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-03
*/
#include "LiveBackGround.h"

//LiveUI CLiveBackGround->>背景类

//------------------------------------------------------------------
// @Function:	 CLiveBackGround()
// @Purpose: CLiveBackGround构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackGround::CLiveBackGround()
{
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	~CLiveBackGround()
// @Purpose: CLiveBackGround析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackGround::~CLiveBackGround()
{
	m_iMage.Destroy();
}

//------------------------------------------------------------------
// @Function:	 CLiveBackGround()
// @Purpose: CLiveBackGround构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackGround::CLiveBackGround(int nWidth, int nHeight)
{
	m_nScreenWidth = nWidth;
	m_nScreenHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveBackGround_SetWindow()
// @Purpose: CLiveBackGround设置窗口尺寸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveBackGround::LiveBackGround_SetWindow(int nWidth, int nHeight)
{
	m_nScreenWidth = nWidth;
	m_nScreenHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveBackGround_Convert_A2W()
// @Purpose: CLiveBackGround转换小程式
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveBackGround::LiveBackGround_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
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
// @Function:	 LiveBackGroundInit()
// @Purpose: CLiveBackGround初始化函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveBackGround::LiveBackGroundInit(LPCSTR szFile)
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
	bRet = LiveBackGround_Convert_A2W(chArr, m_tcFilePath, MAX_PATH);
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
// @Function:	 LiveBackGroundPaint()
// @Purpose: CLiveBackGround重绘函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveBackGround::LiveBackGroundPaint(HDC& hDC)
{
	m_iMage.Draw(hDC, 0, 0);
}