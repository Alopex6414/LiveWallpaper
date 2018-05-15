/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTabConsole.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-15
*/
#include "LiveTabConsole.h"

//LiveUI CLiveTabConsole->>Tab��

//------------------------------------------------------------------
// @Function:	 CLiveTabConsole()
// @Purpose: CLiveTabConsole���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConsole::CLiveTabConsole()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveTabConsole()
// @Purpose: CLiveTabConsole��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConsole::~CLiveTabConsole()
{
}

//------------------------------------------------------------------
// @Function:	 LiveTabConsoleSetMouse()
// @Purpose: CLiveTabConsole�����������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConsole::LiveTabConsoleSetMouse(POINT* ppt)
{
	m_pMousePoint = ppt;
}

//------------------------------------------------------------------
// @Function:	 LiveTabConsoleStartButtonClick()
// @Purpose: CLiveTabConsole������ʼ���Ű�ť
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConsole::LiveTabConsoleStartButtonClick()
{
	g_cArmeniacaExport.Armeniaca_StartProcessA("LiveWallpaperCore.exe");
}

//------------------------------------------------------------------
// @Function:	 LiveTabConsoleStopButtonClick()
// @Purpose: CLiveTabConsole����ֹͣ���Ű�ť
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConsole::LiveTabConsoleStopButtonClick()
{

}

//------------------------------------------------------------------
// @Function:	 LiveTabConsoleInit()
// @Purpose: CLiveTabConsole��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConsole::LiveTabConsoleInit(void)
{
	LiveTab_SetWindow(640, 480);
	LiveTabInit("frame\\Bk\\Console.png");

	m_cLabelTitle.LiveButton_SetWindow(0, 0, 120, 40);
	m_cLabelTitle.LiveButtonInit("frame\\Label\\Console.png");
	
	//Radio
	m_cRadioConsoleStart.LiveRadio_SetWindow(500, 400, 24, 24);
	m_cRadioConsoleStart.LiveRadioInit("frame\\Button\\Start.png", "frame\\Button\\Start.png");
	m_cRadioConsoleStart.LiveRadioSetSelectState(false);

	m_cRadioConsoleStop.LiveRadio_SetWindow(550, 400, 24, 24);
	m_cRadioConsoleStop.LiveRadioInit("frame\\Button\\Stop.png", "frame\\Button\\Stop.png");
	m_cRadioConsoleStop.LiveRadioSetSelectState(false);

}

//------------------------------------------------------------------
// @Function:	 LiveTabConsolePaint()
// @Purpose: CLiveTabConsole�ػ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConsole::LiveTabConsolePaint(HDC& hDC)
{
	LiveTabPaint(hDC);

	m_cLabelTitle.LiveButtonPaint(hDC, m_nAlpha);

	//Radio
	m_cRadioConsoleStart.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioConsoleStop.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);

}