/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveTabConfig.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-05-07
*/
#pragma once

#ifndef __LIVETABCONFIG_H_
#define __LIVETABCONFIG_H_

//Include Common Header File
#include "Common.h"
#include "LiveTab.h"
#include "LiveButton.h"
#include "LiveRadio.h"
#include "LiveRollCtrl.h"

//Class Definition
class CLiveTabConfig :public CLiveTab
{
private:
	POINT* m_pMousePoint;

public:
	CLiveButton m_cLabelTitle;
	CLiveButton m_cLabelLiveMode;
	CLiveButton m_cLabelLiveModeDefault;
	CLiveButton m_cLabelLiveModeSelect;
	CLiveButton m_cLabelLiveAudio;
	CLiveButton m_cLabelLiveAudioUse;
	CLiveButton m_cLabelLiveAudioNoUse;
	CLiveButton m_cLabelLiveShow;
	CLiveButton m_cLabelLiveShowOne;
	CLiveButton m_cLabelLiveShowTwo;
	CLiveButton m_cLabelLiveShowThree;
	CLiveButton m_cLabelLiveShowFour;
	CLiveButton m_cLabelLiveShowFive;
	CLiveButton m_cLabelLiveOther;
	CLiveButton m_cLabelLiveFPS;
	CLiveButton m_cLabelLiveLog;
	
	CLiveRadio m_cRadioLiveModeDefault;
	CLiveRadio m_cRadioLiveModeSelect;
	CLiveRollCtrl m_cRollCtrlDefault;

	CLiveRadio m_cRadioLiveAudioUse;
	CLiveRadio m_cRadioLiveAudioNoUse;

	CLiveRadio m_cRadioLiveShowOne;
	CLiveRadio m_cRadioLiveShowTwo;
	CLiveRadio m_cRadioLiveShowThree;
	CLiveRadio m_cRadioLiveShowFour;
	CLiveRadio m_cRadioLiveShowFive;

	CLiveRadio m_cRadioLiveFPS;
	CLiveRadio m_cRadioLiveLog;

public:
	CLiveTabConfig();
	~CLiveTabConfig();

	VOID LiveTabConfigSetMouse(POINT* ppt);

	VOID LiveTabConfigInit(void);
	VOID LiveTabConfigPaint(HDC& hDC);

};

#endif // !__LIVETABCONFIG_H_
