/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTab.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-07
*/
#include "LiveTab.h"

//LiveUI LiveTab->>Tab类

//------------------------------------------------------------------
// @Function:	 CLiveTab()
// @Purpose: CLiveTab构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTab::CLiveTab()
{
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
	m_bShowWindow = false;
	m_nAlpha = 0;
	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 ~CLiveTab()
// @Purpose: CLiveTab析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTab::~CLiveTab()
{
	m_iMage.Destroy();
}

//------------------------------------------------------------------
// @Function:	 LiveTab_SetWindow()
// @Purpose: CLiveTab设置窗口尺寸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveTab::LiveTab_SetWindow(int nWidth, int nHeight) 
{
	m_nScreenWidth = nWidth;
	m_nScreenHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveTab_Convert_A2W()
// @Purpose: CLiveTab转换小程式
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveTab::LiveTab_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
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
// @Function:	 LiveTabSetShowState()
// @Purpose: CLiveTab设置窗口页面是否可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveTab::LiveTabSetShowState(bool bShow)
{
	m_bShowWindow = bShow;
}

//------------------------------------------------------------------
// @Function:	 LiveTabSetShowState()
// @Purpose: CLiveTab获取窗口页面是否可见
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CLiveTab::LiveTabGetShowState(void)
{
	return m_bShowWindow;
}

//------------------------------------------------------------------
// @Function:	 LiveTabInit()
// @Purpose: CLiveTab初始化Tab页
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveTab::LiveTabInit(LPCSTR szFile)
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
	bRet = LiveTab_Convert_A2W(chArr, m_tcFilePath, MAX_PATH);
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
// @Function:	 LiveTabPaint()
// @Purpose: CLiveTab重绘Tab页
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTab::LiveTabPaint(HDC& hDC)
{
	BLENDFUNCTION bf;

	if (m_bShowWindow)
	{
		m_nAlpha += 16;
		if (m_nAlpha > 255)
		{
			m_nAlpha = 255;
		}
	}
	else
	{
		m_nAlpha -= 16;
		if (m_nAlpha < 0)
		{
			m_nAlpha = 0;
		}
	}

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = m_nAlpha;
	AlphaBlend(hDC, 0, 0, m_nScreenWidth, m_nScreenHeight, m_iMage.GetDC(), 0, 0, m_nScreenWidth, m_nScreenHeight, bf);
}
