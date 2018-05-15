/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveRollText.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-14
*/
#include "LiveRollText.h"
#include "WinProcess.h"
#include "WinUtilities.h"

//LiveUI CLiveRollText->>RollText类

//------------------------------------------------------------------
// @Function:	 CLiveRollText()
// @Purpose: CLiveRollText构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveRollText::CLiveRollText()
{
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;

	m_nTextX = 0;
	m_nTextY = 0;

	m_nFontSize = 100;
	memset(m_chFontType, 0, MAX_PATH);
	memset(m_tcFilePath, 0, MAX_PATH);
}

//------------------------------------------------------------------
// @Function:	 ~CLiveRollText()
// @Purpose: CLiveRollText析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveRollText::~CLiveRollText()
{
	m_iMage.Destroy();
}

//------------------------------------------------------------------
// @Function:	 LiveRollText_SetWindow()
// @Purpose: CLiveRollText设置窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveRollText::LiveRollText_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveRollText_SetFont()
// @Purpose: CLiveRollText设置字体
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveRollText::LiveRollText_SetFont(const char* szFontType, int nFontSize)
{
	m_nFontSize = nFontSize;
	memcpy_s(m_chFontType, MAX_PATH, szFontType, strlen(szFontType));
}

//------------------------------------------------------------------
// @Function:	 LiveRollText_Convert_A2W()
// @Purpose: CLiveRollText转换小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveRollText::LiveRollText_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
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
// @Function:	 LiveRollTextPaint()
// @Purpose: CLiveRollText重绘窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveRollText::LiveRollTextInit(LPCSTR szFile)
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
	bRet = LiveRollText_Convert_A2W(chArr, m_tcFilePath, MAX_PATH);
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
// @Function:	 LiveRollTextPaint()
// @Purpose: CLiveRollText重绘窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveRollText::LiveRollTextPaint(HDC& hDC, const char* szText, bool bLoad, int nAlpha)
{
	HDC hMemDC;
	HBITMAP hBitmap;
	HFONT hFont;
	SIZE Size;
	RECT Rect;
	int nWidth;
	int nHeight;

	//用户区域大小
	GetClientRect(g_hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	//绘制准备
	hMemDC = CreateCompatibleDC(hDC);
	hBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);

	SetBkMode(hMemDC, TRANSPARENT);
	SetTextColor(hMemDC, RGB(0, 0, 0));

	hFont = CreateFontA(m_nFontSize, 0, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, m_chFontType);

	SelectObject(hMemDC, hFont);
	SelectObject(hMemDC, hBitmap);

	//绘制背景图片
	m_iMage.Draw(hMemDC, 0, 0);

	GetTextExtentPoint32A(hMemDC, szText, strlen(szText), &Size);

	static bool bMove = false;
	static int nMoveX = 0;
	static int nMoveWidth = 0;

	if (Size.cx <= m_nWidth)
	{
		bMove = false;
		nMoveX = 0;
		nMoveWidth = 0;

		m_nTextX = m_nPosX + ((m_nWidth - Size.cx) >> 1);
		m_nTextY = m_nPosY + ((m_nHeight - Size.cy) >> 1);
	}
	else
	{
		nMoveWidth = (Size.cx - m_nWidth);

		if (!bMove)
		{
			nMoveX++;
			if (nMoveX > nMoveWidth + 10)
			{
				nMoveX = nMoveWidth + 10;
				bMove = true;
			}
		}
		else
		{
			nMoveX--;
			if (nMoveX < -10)
			{
				nMoveX = -10;
				bMove = false;
			}
		}

		m_nTextX = m_nPosX - nMoveX;
		m_nTextY = m_nPosY + ((m_nHeight - Size.cy) >> 1);
	}

	TextOutA(hMemDC, m_nTextX, m_nTextY, szText, strlen(szText));

	if (!bLoad)
	{
		BLENDFUNCTION bf;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.SourceConstantAlpha = nAlpha;

		AlphaBlend(hDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight, hMemDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight, bf);
	}
	else
	{
		BitBlt(hDC, m_nPosX, m_nPosY, m_nWidth, m_nHeight, hMemDC, m_nPosX, m_nPosY, SRCCOPY);
	}

	DeleteObject(hFont);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);

}