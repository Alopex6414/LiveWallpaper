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

//LiveUI LiveTabConfig->>Tab��

//------------------------------------------------------------------
// @Function:	 CLiveTabConfig()
// @Purpose: CLiveTabConfig���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConfig::CLiveTabConfig()
{
	m_nLiveCoreVideoMode = 0;
	m_nLiveCoreWallpaperMode = 0;
	m_nLiveCoreShowGraphics = 0;
	m_nLiveCoreLogProcess = 0;
	m_nLiveCoreWallpaperAudioMode = 0;

	memset(m_chLiveCoreVideoName, 0, MAX_PATH);
	memset(m_chLiveCoreVideoAddress, 0, MAX_PATH);
}

//------------------------------------------------------------------
// @Function:	 ~CLiveTabConfig()
// @Purpose: CLiveTabConfig��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveTabConfig::~CLiveTabConfig()
{
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigSetMouse()
// @Purpose: CLiveTabConfig�����������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigSetMouse(POINT* ppt)
{
	m_pMousePoint = ppt;
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigRepeatButtonClick()
// @Purpose: CLiveTabConfig�ָ�Ĭ������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigRepeatButtonClick()
{
	// LiveConfigTab����չʾ

	// Ĭ����Ƶģʽ
	m_cRadioLiveModeDefault.LiveRadioSetSelectState(true);
	m_cRadioLiveModeSelect.LiveRadioSetSelectState(false);

	// ������Ƶ��Ƶ
	m_cRadioLiveAudioUse.LiveRadioSetSelectState(true);
	m_cRadioLiveAudioNoUse.LiveRadioSetSelectState(false);

	// ��ֽ��������
	m_cRadioLiveFPS.LiveRadioSetSelectState(false);
	m_cRadioLiveLog.LiveRadioSetSelectState(false);

	// ��Ƶ����ģʽ
	m_cRadioLiveShowOne.LiveRadioSetSelectState(true);
	m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
	m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
	m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
	m_cRadioLiveShowFive.LiveRadioSetSelectState(false);

	// Ĭ����Ƶѡ��
	m_cRollCtrlDefault.LiveRollCtrl_SetMoveX(0);

	// �����ļ�д��
	char* pTemp = NULL;
	pTemp = (char*)"Wallpaper1.pak";

	m_nLiveCoreVideoMode = 0;
	m_nLiveCoreWallpaperAudioMode = 1;
	m_nLiveCoreShowGraphics = 0;
	m_nLiveCoreLogProcess = 0;
	m_nLiveCoreWallpaperMode = 0;
	
	memset(m_chLiveCoreVideoName, 0, MAX_PATH);
	memcpy_s(m_chLiveCoreVideoName, MAX_PATH, pTemp, strlen(pTemp));

	// д�������ļ�
	LiveTabConfigWriteConfig();

}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigSaveButtonClick()
// @Purpose: CLiveTabConfig���浱ǰ����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigSaveButtonClick()
{
	char chArray[MAX_PATH] = { 0 };
	int nValue = 0;

	// Ĭ����Ƶģʽ
	if (m_cRadioLiveModeDefault.LiveRadioGetSelectState())
	{
		nValue = 0;
	}
	else
	{
		nValue = 1;
	}

	m_nLiveCoreVideoMode = nValue;

	// ������Ƶ��Ƶ
	if (m_cRadioLiveAudioUse.LiveRadioGetSelectState())
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}

	m_nLiveCoreWallpaperAudioMode = nValue;

	// ��ֽ��������
	if (m_cRadioLiveFPS.LiveRadioGetSelectState())
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}

	m_nLiveCoreShowGraphics = nValue;

	if (m_cRadioLiveLog.LiveRadioGetSelectState())
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}

	m_nLiveCoreLogProcess = nValue;

	// ��Ƶ����ģʽ
	if (m_cRadioLiveShowOne.LiveRadioGetSelectState())
	{
		nValue = 0;
	}
	else if (m_cRadioLiveShowTwo.LiveRadioGetSelectState())
	{
		nValue = 1;
	}
	else if (m_cRadioLiveShowThree.LiveRadioGetSelectState())
	{
		nValue = 2;
	}
	else if (m_cRadioLiveShowFour.LiveRadioGetSelectState())
	{
		nValue = 3;
	}
	else
	{
		nValue = 4;
	}

	m_nLiveCoreWallpaperMode = nValue;

	char* pTemp = NULL;

	switch (m_cRollCtrlDefault.m_nWallpaperCount)
	{
	case 0:
		pTemp = (char*)"Wallpaper1.pak";
		memset(m_chLiveCoreVideoName, 0, MAX_PATH);
		memcpy_s(m_chLiveCoreVideoName, MAX_PATH, pTemp, strlen(pTemp));
		break;
	case 1:
		pTemp = (char*)"Wallpaper2.pak";
		memset(m_chLiveCoreVideoName, 0, MAX_PATH);
		memcpy_s(m_chLiveCoreVideoName, MAX_PATH, pTemp, strlen(pTemp));
		break;
	case 2:
		pTemp = (char*)"Wallpaper3.pak";
		memset(m_chLiveCoreVideoName, 0, MAX_PATH);
		memcpy_s(m_chLiveCoreVideoName, MAX_PATH, pTemp, strlen(pTemp));
		break;
	default:
		pTemp = (char*)"Wallpaper1.pak";
		memset(m_chLiveCoreVideoName, 0, MAX_PATH);
		memcpy_s(m_chLiveCoreVideoName, MAX_PATH, pTemp, strlen(pTemp));
		break;
	}

	// д�������ļ�
	LiveTabConfigWriteConfig();

}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigReadConfig()
// @Purpose: CLiveTabConfig��ȡ�����ļ�(LiveCore)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigReadConfig()
{
	char chFileArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chFileArr, MAX_PATH);
	pTemp = strrchr(chFileArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}

	strcat_s(chFileArr, "\\config\\LiveCore.cfg");

	char chArray[MAX_PATH] = { 0 };
	int nValue;

	// ����������Ϣ
	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Mode", 0, chArray, MAX_PATH, chFileArr);
	nValue = atoi(chArray);
	m_nLiveCoreVideoMode = nValue;	// LiveCore��̬��ֽ��Ƶģʽ: 0~����Ĭ����Ƶ 1~����ѡ����Ƶ

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", 0, chArray, MAX_PATH, chFileArr);
	nValue = atoi(chArray);
	m_nLiveCoreWallpaperAudioMode = nValue;	// LiveCore��Ƶ����ģʽ: 0~��������Ƶ 1~������Ƶ

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", 0, chArray, MAX_PATH, chFileArr);
	nValue = atoi(chArray);
	m_nLiveCoreShowGraphics = nValue;	// LiveCore��ʾ: 0~����ʾ�Կ��ͺ�(fps) 1~��ʾ�Կ��ͺ�(fps)

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", 0, chArray, MAX_PATH, chFileArr);
	nValue = atoi(chArray);
	m_nLiveCoreLogProcess = nValue;	// LiveCore��־��¼: 0~����¼���� 1~��¼����

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", 0, chArray, MAX_PATH, chFileArr);
	nValue = atoi(chArray);
	m_nLiveCoreWallpaperMode = nValue;	// LiveCore��Ļ�ֱ���ģʽ: 0~��� 1~��Ӧ 2~���� 3~ƽ�� 4~����


	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Name", 0, chArray, MAX_PATH, chFileArr);
	memcpy_s(m_chLiveCoreVideoName, MAX_PATH, chArray, MAX_PATH);	// LiveCore��̬��ֽĬ����Ƶ����

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", 0, chArray, MAX_PATH, chFileArr);
	memcpy_s(m_chLiveCoreVideoAddress, MAX_PATH, chArray, MAX_PATH);	// LiveCore��̬��ֽ��Ƶ��ַ


}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigWriteConfig()
// @Purpose: CLiveTabConfigд�������ļ�(LiveCore)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigWriteConfig()
{
	char chFileArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chFileArr, MAX_PATH);
	pTemp = strrchr(chFileArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}

	strcat_s(chFileArr, "\\config\\LiveCore.cfg");

	char chArray[MAX_PATH] = { 0 };

	// д��������Ϣ
	memset(chArray, 0, MAX_PATH);
	_itoa_s(m_nLiveCoreVideoMode, chArray, 10);
	WritePrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Mode", chArray, chFileArr);	// LiveCore��̬��ֽ��Ƶģʽ: 0~����Ĭ����Ƶ 1~����ѡ����Ƶ

	memset(chArray, 0, MAX_PATH);
	_itoa_s(m_nLiveCoreWallpaperAudioMode, chArray, 10);
	WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", chArray, chFileArr);	// LiveCore��Ƶ����ģʽ: 0~��������Ƶ 1~������Ƶ

	memset(chArray, 0, MAX_PATH);
	_itoa_s(m_nLiveCoreShowGraphics, chArray, 10);
	WritePrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", chArray, chFileArr);	// LiveCore��ʾ: 0~����ʾ�Կ��ͺ�(fps) 1~��ʾ�Կ��ͺ�(fps)

	memset(chArray, 0, MAX_PATH);
	_itoa_s(m_nLiveCoreLogProcess, chArray, 10);
	WritePrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", chArray, chFileArr);	// LiveCore��־��¼: 0~����¼���� 1~��¼����

	memset(chArray, 0, MAX_PATH);
	_itoa_s(m_nLiveCoreWallpaperMode, chArray, 10);
	WritePrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", chArray, chFileArr);		// LiveCore��Ļ�ֱ���ģʽ: 0~��� 1~��Ӧ 2~���� 3~ƽ�� 4~����

	memset(chArray, 0, MAX_PATH);
	memcpy_s(chArray, MAX_PATH, m_chLiveCoreVideoName, MAX_PATH);
	WritePrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Name", chArray, chFileArr);	// LiveCore��̬��ֽĬ����Ƶ����

	memset(chArray, 0, MAX_PATH);
	memcpy_s(chArray, MAX_PATH, m_chLiveCoreVideoAddress, MAX_PATH);
	WritePrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", chArray, chFileArr);	// LiveCore��̬��ֽ��Ƶ��ַ
	

}

//------------------------------------------------------------------
// @Function:	 LiveTabConfigInit()
// @Purpose: CLiveTabConfig��ʼ��Tabҳ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
VOID CLiveTabConfig::LiveTabConfigInit(void)
{
	LiveTabConfigReadConfig();

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
	// ��̬��ֽģʽ
	m_cRadioLiveModeDefault.LiveRadio_SetWindow(72, 88, 16, 16);
	m_cRadioLiveModeDefault.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");
	
	m_cRadioLiveModeSelect.LiveRadio_SetWindow(72, 120, 16, 16);
	m_cRadioLiveModeSelect.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");
	
	if (m_nLiveCoreVideoMode == 0)
	{
		m_cRadioLiveModeDefault.LiveRadioSetSelectState(true);
		m_cRadioLiveModeSelect.LiveRadioSetSelectState(false);
	}
	else
	{
		m_cRadioLiveModeDefault.LiveRadioSetSelectState(false);
		m_cRadioLiveModeSelect.LiveRadioSetSelectState(true);
	}

	// ��Ƶ��Ƶģʽ
	m_cRadioLiveAudioUse.LiveRadio_SetWindow(72, 198, 16, 16);
	m_cRadioLiveAudioUse.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");

	m_cRadioLiveAudioNoUse.LiveRadio_SetWindow(72, 230, 16, 16);
	m_cRadioLiveAudioNoUse.LiveRadioInit("frame\\Button\\RadioButtonUp.png", "frame\\Button\\RadioButtonDown.png");

	if (m_nLiveCoreWallpaperAudioMode == 0)
	{
		m_cRadioLiveAudioUse.LiveRadioSetSelectState(false);
		m_cRadioLiveAudioNoUse.LiveRadioSetSelectState(true);
	}
	else
	{
		m_cRadioLiveAudioUse.LiveRadioSetSelectState(true);
		m_cRadioLiveAudioNoUse.LiveRadioSetSelectState(false);
	}

	m_cRadioLiveFPS.LiveRadio_SetWindow(72, 308, 16, 16);
	m_cRadioLiveFPS.LiveRadioInit("frame\\Button\\StarButtonUp.png", "frame\\Button\\StarButtonDown.png");

	if (m_nLiveCoreShowGraphics == 0)
	{
		m_cRadioLiveFPS.LiveRadioSetSelectState(false);
	}
	else
	{
		m_cRadioLiveFPS.LiveRadioSetSelectState(true);
	}

	m_cRadioLiveLog.LiveRadio_SetWindow(72, 340, 16, 16);
	m_cRadioLiveLog.LiveRadioInit("frame\\Button\\StarButtonUp.png", "frame\\Button\\StarButtonDown.png");

	if (m_nLiveCoreLogProcess == 0)
	{
		m_cRadioLiveLog.LiveRadioSetSelectState(false);
	}
	else
	{
		m_cRadioLiveLog.LiveRadioSetSelectState(true);
	}

	m_cRadioLiveShowOne.LiveRadio_SetWindow(412, 88, 16, 16);
	m_cRadioLiveShowOne.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");

	m_cRadioLiveShowTwo.LiveRadio_SetWindow(412, 120, 16, 16);
	m_cRadioLiveShowTwo.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");

	m_cRadioLiveShowThree.LiveRadio_SetWindow(412, 152, 16, 16);
	m_cRadioLiveShowThree.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");

	m_cRadioLiveShowFour.LiveRadio_SetWindow(412, 184, 16, 16);
	m_cRadioLiveShowFour.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");

	m_cRadioLiveShowFive.LiveRadio_SetWindow(412, 216, 16, 16);
	m_cRadioLiveShowFive.LiveRadioInit("frame\\Button\\CheckBoxUp.png", "frame\\Button\\CheckBoxDown.png");

	m_cRadioLiveRepeat.LiveRadio_SetWindow(500, 400, 24, 24);
	m_cRadioLiveRepeat.LiveRadioInit("frame\\Button\\Repeat.png", "frame\\Button\\Repeat.png");
	m_cRadioLiveRepeat.LiveRadioSetSelectState(false);

	m_cRadioLiveSave.LiveRadio_SetWindow(550, 400, 24, 24);
	m_cRadioLiveSave.LiveRadioInit("frame\\Button\\Save.png", "frame\\Button\\Save.png");
	m_cRadioLiveSave.LiveRadioSetSelectState(false);

	switch (m_nLiveCoreWallpaperMode)
	{
	case 0:
		m_cRadioLiveShowOne.LiveRadioSetSelectState(true);
		m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
		m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		break;
	case 1:
		m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
		m_cRadioLiveShowTwo.LiveRadioSetSelectState(true);
		m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		break;
	case 2:
		m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
		m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
		m_cRadioLiveShowThree.LiveRadioSetSelectState(true);
		m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		break;
	case 3:
		m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
		m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
		m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFour.LiveRadioSetSelectState(true);
		m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		break;
	case 4:
		m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
		m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
		m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFive.LiveRadioSetSelectState(true);
		break;
	default:
		m_cRadioLiveShowOne.LiveRadioSetSelectState(true);
		m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
		m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
		m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		break;
	}

	//Roll Ctrl
	m_cRollCtrlDefault.LiveRollCtrl_SetWindow(240, 80, 135, 32);
	m_cRollCtrlDefault.LiveRollCtrlInit("frame\\Button\\ArrowLeft.png", "frame\\Button\\ArrowRight.png", "frame\\Label\\ModeDefaultText.png");

	if (!strcmp(m_chLiveCoreVideoName, "Wallpaper1.pak"))
	{
		m_cRollCtrlDefault.m_nWallpaperCount = 0;
		m_cRollCtrlDefault.LiveRollCtrl_SetMoveX(0);
	}
	else if (!strcmp(m_chLiveCoreVideoName, "Wallpaper2.pak"))
	{
		m_cRollCtrlDefault.m_nWallpaperCount = 1;
		m_cRollCtrlDefault.LiveRollCtrl_SetMoveX(108);
	}
	else if (!strcmp(m_chLiveCoreVideoName, "Wallpaper3.pak"))
	{
		m_cRollCtrlDefault.m_nWallpaperCount = 2;
		m_cRollCtrlDefault.LiveRollCtrl_SetMoveX(216);
	}
	else
	{
		m_cRollCtrlDefault.m_nWallpaperCount = 0;
		m_cRollCtrlDefault.LiveRollCtrl_SetMoveX(0);
	}

	LiveTabSetShowState(false);
}

//------------------------------------------------------------------
// @Function:	 LiveTabConfig()
// @Purpose: CLiveTabConfig�ػ�Tabҳ
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

	//Button
	m_cRadioLiveRepeat.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	m_cRadioLiveSave.LiveRadioPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);
	
	//RollCtrl
	m_cRollCtrlDefault.LiveRollCtrlPaint(hDC, *m_pMousePoint, m_bLoadWindow, m_nAlpha);

}