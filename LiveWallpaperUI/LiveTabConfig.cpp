/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTabConfig.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-07
*/
#include "LiveTabConfig.h"

//LiveUI LiveTabConfig->>Tab类

//------------------------------------------------------------------
// @Function:	 CLiveTabConfig()
// @Purpose: CLiveTabConfig构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConfig::CLiveTabConfig()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveTabConfig()
// @Purpose: CLiveTabConfig析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConfig::~CLiveTabConfig()
{
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigSetMouse()
// @Purpose: CLiveTabConfig设置鼠标坐标
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigSetMouse(POINT* ppt)
{
	m_pMousePoint = ppt;
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigInit()
// @Purpose: CLiveTabConfig初始化Tab页
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigInit(void)
{
	LiveTab_SetWindow(640, 480);
	LiveTabInit("frame\\Bk\\Config.png");

	m_cLabelTitle.LiveButton_SetWindow(0, 0, 120, 40);
	m_cLabelTitle.LiveButtonInit("frame\\Label\\Config.png");

	m_cLabelLiveMode.LiveButton_SetWindow(20, 40, 320, 40);
	m_cLabelLiveMode.LiveButtonInit("frame\\Label\\LiveModeLabel.png");

	m_cLabelLiveAudio.LiveButton_SetWindow(20, 150, 320, 40);
	m_cLabelLiveAudio.LiveButtonInit("frame\\Label\\LiveAudioLabel.png");

	m_cLabelLiveOther.LiveButton_SetWindow(20, 260, 320, 40);
	m_cLabelLiveOther.LiveButtonInit("frame\\Label\\LiveOtherLabel.png");

	m_cLabelLiveShow.LiveButton_SetWindow(360, 40, 320, 40);
	m_cLabelLiveShow.LiveButtonInit("frame\\Label\\LiveShowModeLabel.png");

	//Label
	m_cLabelLiveModeDefault.LiveButton_SetWindow(80, 80, 320, 32);
	m_cLabelLiveModeDefault.LiveButtonInit("frame\\Label\\LiveModeDefault.png");
	m_cLabelLiveModeSelect.LiveButton_SetWindow(80, 112, 320, 32);
	m_cLabelLiveModeSelect.LiveButtonInit("frame\\Label\\LiveModeSelect.png");

	m_cLabelLiveAudioUse.LiveButton_SetWindow(80, 190, 320, 32);
	m_cLabelLiveAudioUse.LiveButtonInit("frame\\Label\\LiveAudioUse.png");
	m_cLabelLiveAudioNoUse.LiveButton_SetWindow(80, 222, 320, 32);
	m_cLabelLiveAudioNoUse.LiveButtonInit("frame\\Label\\LiveAudioNoUse.png");

	m_cLabelLiveFPS.LiveButton_SetWindow(80, 300, 320, 32);
	m_cLabelLiveFPS.LiveButtonInit("frame\\Label\\LiveOtherShowFPSLabel.png");
	m_cLabelLiveLog.LiveButton_SetWindow(80, 332, 320, 32);
	m_cLabelLiveLog.LiveButtonInit("frame\\Label\\LiveOtherShowLogLabel.png");

	m_cLabelLiveShowOne.LiveButton_SetWindow(420, 80, 320, 32);
	m_cLabelLiveShowOne.LiveButtonInit("frame\\Label\\LiveShowModeOneLabel.png");
	m_cLabelLiveShowTwo.LiveButton_SetWindow(420, 112, 320, 32);
	m_cLabelLiveShowTwo.LiveButtonInit("frame\\Label\\LiveShowModeTwoLabel.png");
	m_cLabelLiveShowThree.LiveButton_SetWindow(420, 144, 320, 32);
	m_cLabelLiveShowThree.LiveButtonInit("frame\\Label\\LiveShowModeThreeLabel.png");
	m_cLabelLiveShowFour.LiveButton_SetWindow(420, 176, 320, 32);
	m_cLabelLiveShowFour.LiveButtonInit("frame\\Label\\LiveShowModeFourLabel.png");
	m_cLabelLiveShowFive.LiveButton_SetWindow(420, 208, 320, 32);
	m_cLabelLiveShowFive.LiveButtonInit("frame\\Label\\LiveShowModeFiveLabel.png");

	//Radio
	m_cRadioLiveModeDefault.LiveRadio_SetWindow(72, 88, 16, 16);
	m_cRadioLiveModeDefault.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");
	m_cRadioLiveModeDefault.LiveRadioSetSelectState(true);

	m_cRadioLiveModeSelect.LiveRadio_SetWindow(72, 120, 16, 16);
	m_cRadioLiveModeSelect.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");
	m_cRadioLiveModeSelect.LiveRadioSetSelectState(false);

	m_cRadioLiveAudioUse.LiveRadio_SetWindow(72, 198, 16, 16);
	m_cRadioLiveAudioUse.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");
	m_cRadioLiveAudioUse.LiveRadioSetSelectState(true);

	m_cRadioLiveAudioNoUse.LiveRadio_SetWindow(72, 230, 16, 16);
	m_cRadioLiveAudioNoUse.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");
	m_cRadioLiveAudioNoUse.LiveRadioSetSelectState(false);

	m_cRadioLiveFPS.LiveRadio_SetWindow(72, 308, 16, 16);
	m_cRadioLiveFPS.LiveRadioInit("frame\\Button\\StarButtonUp.png", "frame\\Button\\StarButtonDown.png");
	m_cRadioLiveFPS.LiveRadioSetSelectState(false);

	m_cRadioLiveLog.LiveRadio_SetWindow(72, 340, 16, 16);
	m_cRadioLiveLog.LiveRadioInit("frame\\Button\\StarButtonUp.png", "frame\\Button\\StarButtonDown.png");
	m_cRadioLiveLog.LiveRadioSetSelectState(false);

	m_cRadioLiveShowOne.LiveRadio_SetWindow(412, 88, 16, 16);
	m_cRadioLiveShowOne.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");
	m_cRadioLiveShowOne.LiveRadioSetSelectState(true);

	m_cRadioLiveShowTwo.LiveRadio_SetWindow(412, 120, 16, 16);
	m_cRadioLiveShowTwo.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");
	m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);

	m_cRadioLiveShowThree.LiveRadio_SetWindow(412, 152, 16, 16);
	m_cRadioLiveShowThree.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");
	m_cRadioLiveShowThree.LiveRadioSetSelectState(false);

	m_cRadioLiveShowFour.LiveRadio_SetWindow(412, 184, 16, 16);
	m_cRadioLiveShowFour.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");
	m_cRadioLiveShowFour.LiveRadioSetSelectState(false);

	m_cRadioLiveShowFive.LiveRadio_SetWindow(412, 216, 16, 16);
	m_cRadioLiveShowFive.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");
	m_cRadioLiveShowFive.LiveRadioSetSelectState(false);

	//Roll Ctrl
	m_cRollCtrlDefault.LiveRollCtrl_SetWindow(240, 80, 135, 32);
	m_cRollCtrlDefault.LiveRollCtrlInit("frame\\Button\\ArrowLeft.png", "frame\\Button\\ArrowRight.png", "frame\\Label\\ModeDefaultText.png");

	LiveTabSetShowState(false);
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfig()
// @Purpose: CLiveTabConfig重绘Tab页
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigPaint(HDC& hDC)
{
	LiveTabPaint(hDC);

	m_cLabelTitle.LiveButtonPaint(hDC, m_nAlpha);

	//Label
	m_cLabelLiveMode.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveModeDefault.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveModeSelect.LiveButtonPaint(hDC, m_nAlpha);

	m_cLabelLiveAudio.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveAudioUse.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveAudioNoUse.LiveButtonPaint(hDC, m_nAlpha);

	m_cLabelLiveOther.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveFPS.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveLog.LiveButtonPaint(hDC, m_nAlpha);

	m_cLabelLiveShow.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveShowOne.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveShowTwo.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveShowThree.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveShowFour.LiveButtonPaint(hDC, m_nAlpha);
	m_cLabelLiveShowFive.LiveButtonPaint(hDC, m_nAlpha);

	//Radio
	m_cRadioLiveModeDefault.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveModeSelect.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveAudioUse.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveAudioNoUse.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);

	m_cRadioLiveFPS.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveLog.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);

	m_cRadioLiveShowOne.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveShowTwo.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveShowThree.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveShowFour.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveShowFive.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	
	//RollCtrl
	m_cRollCtrlDefault.LiveRollCtrlPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);

}