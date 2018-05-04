/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveBackIcon.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-04
*/
#include "LiveBackIcon.h"

//LiveUI LiveBackIcon->>Icon类

//------------------------------------------------------------------
// @Function:	 CLiveBackIcon()
// @Purpose: CLiveBackIcon构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackIcon::CLiveBackIcon()
{
	m_nAlpha = 128;
	m_bClick = false;

	m_nMoveX = 0;
	m_nMoveY = 0;
}

//------------------------------------------------------------------
// @Function:	 ~CLiveBackIcon()
// @Purpose: CLiveBackIcon析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveBackIcon::~CLiveBackIcon()
{
}

//------------------------------------------------------------------
// @Function:	 LiveBackIconSetMove()
// @Purpose: CLiveBackIcon设置移动坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveBackIcon::LiveBackIconSetMove(int nMoveX, int nMoveY)
{
	m_nMoveX = nMoveX;
	m_nMoveY = nMoveY;
}

//------------------------------------------------------------------
// @Function:	 LiveBackIconIsHover()
// @Purpose: CLiveBackIcon鼠标在控件上
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
bool CLiveBackIcon::LiveBackIconIsHover(POINT pt)
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
// @Function:	 LiveBackIconSetClick()
// @Purpose: CLiveBackIcon控件单击状态
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveBackIcon::LiveBackIconSetClick(bool bClick)
{
	m_bClick = bClick;
}

//------------------------------------------------------------------
// @Function:	 LiveBackIconPaint()
// @Purpose: CLiveBackIcon绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveBackIcon::LiveBackIconPaint(HDC& hDC, POINT pt)
{
	BLENDFUNCTION bf;
	bool bRet = false;

	if (!m_bClick)
	{
		bRet = LiveBackIconIsHover(pt);
		if (bRet)
		{
			m_nAlpha += 20;
		}
		else
		{
			m_nAlpha -= 20;
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
	AlphaBlend(hDC, m_nMoveX, m_nMoveY, m_nWidth, m_nHeight, m_iMage.GetDC(), 0, 0, m_nWidth, m_nHeight, bf);
}

//------------------------------------------------------------------
// @Function:	 LiveBackIconPaint()
// @Purpose: CLiveBackIcon绘制
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveBackIcon::LiveBackIconPaint(HDC& hDC, UCHAR ucAlpha)
{
	BLENDFUNCTION bf;

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = ucAlpha;
	AlphaBlend(hDC, m_nMoveX, m_nMoveY, m_nWidth, m_nHeight, m_iMage.GetDC(), 0, 0, m_nWidth, m_nHeight, bf);
}