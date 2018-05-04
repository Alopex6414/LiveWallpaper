/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveBackPanel.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-04
*/
#include "LiveBackPanel.h"

//LiveUI CLiveBackPanel->>Panel类

//------------------------------------------------------------------
// @Function:	 CLiveBackPanel()
// @Purpose: CLiveBackPanel构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackPanel::CLiveBackPanel()
{
	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;

	m_nMoveX = 0;
	m_nMoveY = 0;

	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	~CLiveBackPanel()
// @Purpose: CLiveBackPanel析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackPanel::~CLiveBackPanel()
{
	m_iMage.Destroy();
}

//------------------------------------------------------------------
// @Function:	 CLiveBackPanel()
// @Purpose: CLiveBackPanel构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackPanel::CLiveBackPanel(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	m_nMoveX = 0;
	m_nMoveY = 0;

	memset(m_tcFilePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 LiveBackPanel_SetWindow()
// @Purpose: CLiveBackPanel设置窗口位置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveBackPanel::LiveBackPanel_SetWindow(int nPosX, int nPosY, int nWidth, int nHeight)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveBackPanel_SetMove()
// @Purpose: CLiveBackPanel设置窗口移动位置
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveBackPanel::LiveBackPanel_SetMove(int nMoveX, int nMoveY)
{
	m_nMoveX = nMoveX;
	m_nMoveY = nMoveY;
}

//------------------------------------------------------------------
// @Function:	 LiveBackPanel_Convert_A2W()
// @Purpose: CLiveBackPanel字符转换小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveBackPanel::LiveBackPanel_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
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
// @Function:	 LiveBackPanelInit()
// @Purpose: CLiveBackPanel初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveBackPanel::LiveBackPanelInit(LPCSTR szFile)
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
	bRet = LiveBackPanel_Convert_A2W(chArr, m_tcFilePath, MAX_PATH);
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
// @Function:	 LiveBackPanelPaint()
// @Purpose: CLiveBackPanel重绘
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveBackPanel::LiveBackPanelPaint(HDC& hDC)
{
	m_iMage.Draw(hDC, m_nMoveX, m_nMoveY, m_nWidth, m_nHeight);
}