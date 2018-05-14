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
	int m_nLiveCoreVideoMode;			// LiveCore��̬��ֽ��Ƶģʽ: 0~����Ĭ����Ƶ 1~����ѡ����Ƶ
	int m_nLiveCoreWallpaperMode;		// LiveCore��Ļ�ֱ���ģʽ: 0~��� 1~��Ӧ 2~���� 3~ƽ�� 4~����
	int m_nLiveCoreShowGraphics;		// LiveCore��ʾ: 0~����ʾ�Կ��ͺ�(fps) 1~��ʾ�Կ��ͺ�(fps)
	int m_nLiveCoreLogProcess;			// LiveCore��־��¼: 0~����¼���� 1~��¼����
	int m_nLiveCoreWallpaperAudioMode;	// LiveCore��Ƶ����ģʽ: 0~��������Ƶ 1~������Ƶ

	char m_chLiveCoreVideoName[MAX_PATH];		// LiveCore��̬��ֽĬ����Ƶ����
	char m_chLiveCoreVideoAddress[MAX_PATH];	// LiveCore��̬��ֽ��Ƶ��ַ

	char m_chVideoAddressName[MAX_PATH];		// ѡ����Ƶ��ַ����

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
	VOID LiveTabConfigRepeatButtonClick();	// �����ָ�Ĭ�����ð�ť�¼�
	VOID LiveTabConfigSaveButtonClick();	// �������浱ǰ���ð�ť�¼�

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
