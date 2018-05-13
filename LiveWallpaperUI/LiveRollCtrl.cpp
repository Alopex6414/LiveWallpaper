/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveRollCtrl.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-13
*/
#include "LiveRollCtrl.h"

//LiveUI CLiveRollCtrl->>滚动控件类

//------------------------------------------------------------------
// @Function:	 CLiveRollCtrl()
// @Purpose: CLiveRollCtrl构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveRollCtrl::CLiveRollCtrl()
{
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;

	m_nMoveX = 0;
	m_nMoveY = 0;

	m_bSelectLeft = false;
	m_nLeftAlpha = 128;
	m_bSelectRight = false;
	m_nRightAlpha = 128;
	
	memset(m_tcFilePathLeft, 0, MAX_PATH * sizeof(TCHAR));
	memset(m_tcFilePathRight, 0, MAX_PATH * sizeof(TCHAR));
	memset(m_tcFilePathText, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 ~CLiveRollCtrl()
// @Purpose: CLiveRollCtrl析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveRollCtrl::~CLiveRollCtrl()
{
	m_iMageLeft.Destroy();
	m_iMageRight.Destroy();
	m_iMageText.Destroy();
}

//------------------------------------------------------------------
// @Function:	 LiveRollCtrl_SetWindow()
// @Purpose: CLiveRollCtrl设置窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveRollCtrl::LiveRollCtrl_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveRollCtrl_Convert_A2W()
// @Purpose: CLiveRollCtrl转换小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveRollCtrl::LiveRollCtrl_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
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
// @Function:	 LiveRollCtrlIsLeftHover()
// @Purpose: CLiveRollCtrl左键鼠标悬停
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CLiveRollCtrl::LiveRollCtrlIsLeftHover(POINT pt)
{
	bool bRet = false;

	if ((pt.x > m_nPosX && pt.x < (m_nPosX + 16))
		&& (pt.y > (m_nPosY + 8) && pt.y < (m_nPosY + 8 + 16)))
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
// @Function:	 LiveRollCtrlIsRightHover()
// @Purpose: CLiveRollCtrl右键鼠标悬停
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CLiveRollCtrl::LiveRollCtrlIsRightHover(POINT pt)
{
	bool bRet = false;

	if ((pt.x > (m_nPosX + m_nWidth - 16) && pt.x < (m_nPosX + m_nWidth))
		&& (pt.y > (m_nPosY + 8) && pt.y < (m_nPosY + 8 + 16)))
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
// @Function:	 LiveRollCtrlInit()
// @Purpose: CLiveRollCtrl初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveRollCtrl::LiveRollCtrlInit(LPCSTR szFileLeft, LPCSTR szFileRight, LPCSTR szFileText)
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
	strcat_s(chArr, szFileLeft);

	BOOL bRet = FALSE;

	memset(m_tcFilePathLeft, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveRollCtrl_Convert_A2W(chArr, m_tcFilePathLeft, MAX_PATH);
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
	strcat_s(chArr, szFileRight);

	bRet = FALSE;

	memset(m_tcFilePathRight, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveRollCtrl_Convert_A2W(chArr, m_tcFilePathRight, MAX_PATH);
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
	strcat_s(chArr, szFileText);

	bRet = FALSE;

	memset(m_tcFilePathText, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveRollCtrl_Convert_A2W(chArr, m_tcFilePathText, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	//Load...

	HRESULT hr;

	hr = m_iMageLeft.Load(m_tcFilePathLeft);
	if (FAILED(hr))
	{
		return FALSE;
	}

	if (m_iMageLeft.GetBPP() == 32)//包含Alpha通道
	{
		for (int i = 0; i < m_iMageLeft.GetWidth(); i++)
		{
			for (int j = 0; j < m_iMageLeft.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_iMageLeft.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	hr = m_iMageRight.Load(m_tcFilePathRight);
	if (FAILED(hr))
	{
		return FALSE;
	}

	if (m_iMageRight.GetBPP() == 32)//包含Alpha通道
	{
		for (int i = 0; i < m_iMageRight.GetWidth(); i++)
		{
			for (int j = 0; j < m_iMageRight.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_iMageRight.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	hr = m_iMageText.Load(m_tcFilePathText);
	if (FAILED(hr))
	{
		return FALSE;
	}

	if (m_iMageText.GetBPP() == 32)//包含Alpha通道
	{
		for (int i = 0; i < m_iMageText.GetWidth(); i++)
		{
			for (int j = 0; j < m_iMageText.GetHeight(); j++)
			{
				byte *pByte = (byte *)m_iMageText.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveRollCtrlPaint()
// @Purpose: CLiveRollCtrl重绘
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveRollCtrl::LiveRollCtrlPaint(HDC& hDC, POINT pt, bool bLoad, int nAlpha)
{
	bool bRet = false;

	if (!bLoad)
	{
		BLENDFUNCTION bf;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = nAlpha;

		AlphaBlend(hDC, m_nPosX, m_nPosY + 8, 16, 16, m_iMageLeft.GetDC(), 0, 0, 16, 16, bf);
		AlphaBlend(hDC, m_nPosX + m_nWidth - 16, m_nPosY + 8, 16, 16, m_iMageRight.GetDC(), 0, 0, 16, 16, bf);
		AlphaBlend(hDC, m_nPosX + 16, m_nPosY, m_nWidth - 32, m_nHeight, m_iMageText.GetDC(), 0, 0, m_nWidth - 32, m_nHeight, bf);
	}
	else
	{
		BLENDFUNCTION bfLeft;
		BLENDFUNCTION bfRight;
		BLENDFUNCTION bfText;

		//Left...
		if (!m_bSelectLeft)
		{
			bRet = LiveRollCtrlIsLeftHover(pt);
			if (bRet)
			{
				m_nLeftAlpha += 8;
			}
			else
			{
				m_nLeftAlpha -= 8;
			}
		}
		else
		{
			m_nLeftAlpha = 255;
		}

		if (m_nLeftAlpha < 128)
		{
			m_nLeftAlpha = 128;
		}

		if (m_nLeftAlpha > 255)
		{
			m_nLeftAlpha = 255;
		}

		bfLeft.BlendOp = AC_SRC_OVER;
		bfLeft.BlendFlags = 0;
		bfLeft.AlphaFormat = AC_SRC_ALPHA;
		bfLeft.SourceConstantAlpha = m_nLeftAlpha;

		//Right...
		if (!m_bSelectRight)
		{
			bRet = LiveRollCtrlIsRightHover(pt);
			if (bRet)
			{
				m_nRightAlpha += 8;
			}
			else
			{
				m_nRightAlpha -= 8;
			}
		}
		else
		{
			m_nRightAlpha = 255;
		}

		if (m_nRightAlpha < 128)
		{
			m_nRightAlpha = 128;
		}

		if (m_nRightAlpha > 255)
		{
			m_nRightAlpha = 255;
		}

		bfRight.BlendOp = AC_SRC_OVER;
		bfRight.BlendFlags = 0;
		bfRight.AlphaFormat = AC_SRC_ALPHA;
		bfRight.SourceConstantAlpha = m_nRightAlpha;

		//Text...
		static int nDeltaL = 0;
		static int nDeltaR = 0;

		if (m_bSelectLeft)
		{
			nDeltaL += 5;
			m_nMoveX -= 5;

			if (m_nMoveX <= 0)
			{
				nDeltaL = 0;
				nDeltaR = 0;
				m_nMoveX = 0;
				m_bSelectLeft = false;
			}

			if (nDeltaL >= 108 + nDeltaR)
			{
				nDeltaL = 0;
				nDeltaR = 0;
				m_bSelectLeft = false;
			}

		}

		if (m_bSelectRight)
		{
			nDeltaR += 5;
			m_nMoveX += 5;
			
			if (m_nMoveX >= 216)
			{
				nDeltaL = 0;
				nDeltaR = 0;
				m_nMoveX = 216;
				m_bSelectRight = false;
			}

			if (nDeltaR >= 108 + nDeltaL)
			{
				nDeltaL = 0;
				nDeltaR = 0;
				m_bSelectRight = false;
			}

		}

		bfText.BlendOp = AC_SRC_OVER;
		bfText.BlendFlags = 0;
		bfText.AlphaFormat = AC_SRC_ALPHA;
		bfText.SourceConstantAlpha = 255;

		AlphaBlend(hDC, m_nPosX, m_nPosY + 8, 16, 16, m_iMageLeft.GetDC(), 0, 0, 16, 16, bfLeft);
		AlphaBlend(hDC, m_nPosX + m_nWidth - 16, m_nPosY + 8, 16, 16, m_iMageRight.GetDC(), 0, 0, 16, 16, bfRight);
		AlphaBlend(hDC, m_nPosX + 16, m_nPosY, m_nWidth - 32, m_nHeight, m_iMageText.GetDC(), m_nMoveX, 0, m_nWidth - 32, m_nHeight, bfText);
	}

}