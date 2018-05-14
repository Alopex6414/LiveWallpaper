/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTip.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-14
*/
#include "LiveTip.h"

//LiveUI CLiveTip->>Tip类

//------------------------------------------------------------------
// @Function:	 CLiveTip()
// @Purpose: CLiveTip构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTip::CLiveTip()
{
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;

	m_bShow = false;
	m_nAlpha = 0;

	m_nDeltaX = 0;
	m_nDeltaY = 0;

	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 ~CLiveTip()
// @Purpose: CLiveTip析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTip::~CLiveTip()
{
	m_iMage.Destroy();
}

//------------------------------------------------------------------
// @Function:	 LiveTip_SetWindow()
// @Purpose: CLiveTip设置窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveTip::LiveTip_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveTip_Convert_A2W()
// @Purpose: CLiveTip转换小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveTip::LiveTip_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
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
// @Function:	 LiveTipInit()
// @Purpose: CLiveTip初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveTip::LiveTipInit(LPCSTR szFile)
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
	bRet = LiveTip_Convert_A2W(chArr, m_tcFilePath, MAX_PATH);
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
// @Function:	 LiveTipPaint()
// @Purpose: CLiveTip初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTip::LiveTipPaint(HDC& hDC)
{
	BLENDFUNCTION bf;

	if (m_bShow)
	{
		static int nSymbol = 0;
		static int nCount = 0;

		if (nSymbol == 0)
		{
			m_nAlpha += 17;
			if (m_nAlpha > 204)
			{
				m_nAlpha = 204;
				nSymbol = 1;
			}
		}
		else if (nSymbol == 1)
		{
			nCount++;
			if (nCount > 100)
			{
				nCount = 0;
				nSymbol = 2;
			}
		}
		else
		{
			m_nAlpha -= 12;
			m_nDeltaY++;
			if (m_nAlpha < 0)
			{
				m_nAlpha = 0;
				m_nDeltaY = 0;
				nSymbol = 0;
				m_bShow = false;
			}
		}

	}

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = m_nAlpha;
	AlphaBlend(hDC, m_nPosX, m_nPosY - m_nDeltaY, m_nWidth, m_nHeight, m_iMage.GetDC(), 0, 0, m_nWidth, m_nHeight, bf);
}