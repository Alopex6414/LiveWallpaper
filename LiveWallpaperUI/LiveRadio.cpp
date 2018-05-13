/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveRadio.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-13
*/
#include "LiveRadio.h"

//LiveUI CLiveBackPanel->>Radio类

//------------------------------------------------------------------
// @Function:	 CLiveRadio()
// @Purpose: CLiveRadio构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveRadio::CLiveRadio()
{
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_bSelect = false;
	m_nAlpha = 128;
	memset(m_tcFilePathUp, 0, MAX_PATH * sizeof(TCHAR));
	memset(m_tcFilePathDown, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 ~CLiveRadio()
// @Purpose: CLiveRadio析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveRadio::~CLiveRadio()
{
	m_iMageUp.Destroy();
	m_iMageDown.Destroy();
}

//------------------------------------------------------------------
// @Function:	 LiveRadio_SetWindow()
// @Purpose: CLiveRadio设置窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveRadio::LiveRadio_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveRadio_Convert_A2W()
// @Purpose: CLiveRadio转化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveRadio::LiveRadio_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
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
// @Function:	 LiveRadioIsHover()
// @Purpose: CLiveRadio是否鼠标悬停
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CLiveRadio::LiveRadioIsHover(POINT pt)
{
	bool bRet = false;

	if ((pt.x > m_nPosX && pt.x < (m_nPosX + m_nWidth))
		&& (pt.y > m_nPosY && pt.y < (m_nPosY + m_nHeight)))
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

//------------------------------------------------------------------
// @Function:	 LiveRadioInit()
// @Purpose: CLiveRadio初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveRadio::LiveRadioInit(LPCSTR szFileUp, LPCSTR szFileDown)
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
	strcat_s(chArr, szFileUp);

	BOOL bRet = FALSE;

	memset(m_tcFilePathUp, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveRadio_Convert_A2W(chArr, m_tcFilePathUp, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	memset(chArr, 0, MAX_PATH);
	pTemp = NULL;

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	pTemp = strrchr(chArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}

	strcat_s(chArr, "\\");
	strcat_s(chArr, szFileDown);

	bRet = FALSE;

	memset(m_tcFilePathDown, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveRadio_Convert_A2W(chArr, m_tcFilePathDown, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	//Load...

	HRESULT hr;

	hr = m_iMageUp.Load(m_tcFilePathUp);
	if (FAILED(hr))
	{
		return FALSE;
	}

	if (m_iMageUp.GetBPP() == 32)//包含Alpha通道
	{
		for (int i = 0; i < m_iMageUp.GetWidth(); i++)
		{
			for (int j = 0; j < m_iMageUp.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_iMageUp.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	hr = m_iMageDown.Load(m_tcFilePathDown);
	if (FAILED(hr))
	{
		return FALSE;
	}

	if (m_iMageDown.GetBPP() == 32)//包含Alpha通道
	{
		for (int i = 0; i < m_iMageDown.GetWidth(); i++)
		{
			for (int j = 0; j < m_iMageDown.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_iMageDown.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveRadioPaint()
// @Purpose: CLiveRadio重绘
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveRadio::LiveRadioPaint(HDC& hDC, POINT pt, bool bLoad, int nAlpha)
{
	BLENDFUNCTION bf;
	bool bRet = false;

	if (!bLoad)
	{
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = nAlpha;
	}
	else
	{
		if (!m_bSelect)
		{
			bRet = LiveRadioIsHover(pt);
			if (bRet)
			{
				m_nAlpha += 8;
			}
			else
			{
				m_nAlpha -= 8;
			}
		}
		else
		{
			m_nAlpha = 255;
		}

		if (m_nAlpha < 128)
		{
			m_nAlpha = 128;
		}

		if (m_nAlpha > 255)
		{
			m_nAlpha = 255;
		}

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = m_nAlpha;
	}
	
	if (m_bSelect)
	{
		AlphaBlend(hDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight, m_iMageDown.GetDC(), 0, 0, m_nWidth, m_nHeight, bf);
	}
	else
	{
		AlphaBlend(hDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight, m_iMageUp.GetDC(), 0, 0, m_nWidth, m_nHeight, bf);
	}

}