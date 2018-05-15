/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTabConsole.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-15
*/
#pragma once

#ifndef __LIVETABCONSOLE_H_
#define __LIVETABCONSOLE_H_

//Include Common Header File
#include "Common.h"
#include "LiveTab.h"
#include "LiveButton.h"
#include "LiveRadio.h"
#include "LiveTip.h"

//Include Armeniaca Library
#include "ArmeniacaClass.h"

//Class Definition
class CLiveTabConsole :public CLiveTab
{
private:
	POINT * m_pMousePoint;

public:
	CLiveButton m_cLabelTitle;

	CLiveRadio m_cRadioConsoleStart;
	CLiveRadio m_cRadioConsoleStop;

public:
	VOID LiveTabConsoleStartButtonClick();
	VOID LiveTabConsoleStopButtonClick();

public:
	CLiveTabConsole();
	~CLiveTabConsole();

	VOID LiveTabConsoleSetMouse(POINT* ppt);

	VOID LiveTabConsoleInit(void);
	VOID LiveTabConsolePaint(HDC& hDC);

};

extern CArmeniacaExport g_cArmeniacaExport;

#endif // !__LIVETABCONSOLE_H_
