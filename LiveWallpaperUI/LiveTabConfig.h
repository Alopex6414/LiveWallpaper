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
#include "LiveRollText.h"
#include "LiveTip.h"

//Class Definition
class CLiveTabConfig :public CLiveTab
{
private:
	POINT* m_pMousePoint;

private:
	int m_nLiveCoreVideoMode;			// LiveCore动态壁纸视频模式: 0~启用默认视频 1~启用选择视频
	int m_nLiveCoreWallpaperMode;		// LiveCore屏幕分辨率模式: 0~填充 1~适应 2~拉伸 3~平铺 4~居中
	int m_nLiveCoreShowGraphics;		// LiveCore显示: 0~不显示显卡型号(fps) 1~显示显卡型号(fps)
	int m_nLiveCoreLogProcess;			// LiveCore日志记录: 0~不记录过程 1~记录过程
	int m_nLiveCoreWallpaperAudioMode;	// LiveCore音频播放模式: 0~不播放音频 1~播放音频

	char m_chLiveCoreVideoName[MAX_PATH];		// LiveCore动态壁纸默认视频名称
	char m_chLiveCoreVideoAddress[MAX_PATH];	// LiveCore动态壁纸视频地址

	char m_chVideoAddressName[MAX_PATH];		// 选中视频地址名称

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
	CLiveRadio m_cRadioLiveAddressOpen;
	CLiveRollText m_cRollTextAddress;

	CLiveRadio m_cRadioLiveAudioUse;
	CLiveRadio m_cRadioLiveAudioNoUse;

	CLiveRadio m_cRadioLiveShowOne;
	CLiveRadio m_cRadioLiveShowTwo;
	CLiveRadio m_cRadioLiveShowThree;
	CLiveRadio m_cRadioLiveShowFour;
	CLiveRadio m_cRadioLiveShowFive;

	CLiveRadio m_cRadioLiveFPS;
	CLiveRadio m_cRadioLiveLog;

	CLiveRadio m_cRadioLiveRepeat;
	CLiveRadio m_cRadioLiveSave;

	CLiveTip m_cTipLiveRepeat;
	CLiveTip m_cTipLiveSave;

public:
	VOID LiveTabConfigRepeatButtonClick();	// 单击恢复默认设置按钮事件
	VOID LiveTabConfigSaveButtonClick();	// 单击保存当前设置按钮事件

public:
	CLiveTabConfig();
	~CLiveTabConfig();

	VOID LiveTabConfigSetMouse(POINT* ppt);
	VOID LiveTabConfigAnalizeVideoAddress(const char* szAddress);

	VOID LiveTabConfigReadConfig();
	VOID LiveTabConfigWriteConfig();

	VOID LiveTabConfigInit(void);
	VOID LiveTabConfigPaint(HDC& hDC);

};

#endif // !__LIVETABCONFIG_H_
