/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveUI.cpp
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-27
*/
#include "LiveUI.h"
#include "WinProcess.h"
#include "WinUtilities.h"

// LiveWallpaperUI ������
#define LIVEUI_TIMER_ALPHA		0
#define LIVEUI_TIMER_REPAINT	1

CLiveUI g_cLiveUI;
CLiveUI* g_pLiveUI;

//------------------------------------------------------------------
// @Function:	 CLiveUI()
// @Purpose: CLiveUI���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveUI::CLiveUI()
{
	ConstructExtra();
}

//------------------------------------------------------------------
// @Function:	 ~CLiveUI()
// @Purpose: CLiveUI��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveUI::~CLiveUI()
{
	DestructExtra();
}

//------------------------------------------------------------------
// @Function:	 ConstructExtra()
// @Purpose: CLiveUI���촰����Դ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::ConstructExtra()
{
	g_pLiveUI = this;
	m_nWindowAlpha = 0;
	m_bWindowState = false;
	m_bWindowClosed = false;
	m_bWindowClosing = false;

	m_nFrame = 0;
	m_bFrame = false;

	m_pLiveLua = NULL;
	m_nAnimationAlphaMin = 0;
	m_nAnimationAlphaMax = 255;
	m_nAnimationAlphaStep = 1;

	m_bMouseTrack = true;
}

//------------------------------------------------------------------
// @Function:	 DestructExtra()
// @Purpose: CLiveUI����������Դ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::DestructExtra()
{
	if (m_pLiveLua)
	{
		delete m_pLiveLua;
		m_pLiveLua = NULL;
	}
}

//------------------------------------------------------------------
// @Function:	 GetMosePoint()
// @Purpose: CLiveUI��ȡ�������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
POINT CLiveUI::GetMosePoint() const 
{
	return m_sMousePoint;
}

//------------------------------------------------------------------
// @Function:	 InitWindowExtra()
// @Purpose: CLiveUI��ʼ��������Դ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL CLiveUI::InitWindowExtra()
{
	BOOL bRet = FALSE;

	//���ô��ڳߴ�
	m_cLiveBackGround.LiveBackGround_SetWindow(USER_SCREENWIDTH, USER_SCREENHEIGHT);
	m_cLiveBackGround.LiveBackGroundInit("frame\\Bk\\Azure.png");

	//���������ߴ�
	m_cLiveBackPanel.LiveBackPanel_SetMove(0, 475);
	m_cLiveBackPanel.LiveBackPanel_SetWindow(0, 440, 640, 40);
	m_cLiveBackPanel.LiveBackPanelInit("frame\\Panel\\Panel.png");

	//����ͼ�괰�ڳߴ�
	m_cLiveBackIconHome.LiveBackIconSetMove(42, 479);
	m_cLiveBackIconHome.LiveButton_SetWindow(42, 444, 32, 32);
	m_cLiveBackIconHome.LiveButtonInit("frame\\Button\\Home.png");

	m_cLiveBackIconPhone.LiveBackIconSetMove(84, 479);
	m_cLiveBackIconPhone.LiveButton_SetWindow(84, 444, 32, 32);//+20
	m_cLiveBackIconPhone.LiveButtonInit("frame\\Button\\Phone.png");

	m_cLiveBackIconConfig.LiveBackIconSetMove(126, 479);
	m_cLiveBackIconConfig.LiveButton_SetWindow(126, 444, 32, 32);//+20
	m_cLiveBackIconConfig.LiveButtonInit("frame\\Button\\Config.png");

	m_cLiveBackIconCard.LiveBackIconSetMove(178, 479);
	m_cLiveBackIconCard.LiveButton_SetWindow(178, 444, 32, 32);//+20
	m_cLiveBackIconCard.LiveButtonInit("frame\\Button\\Card.png");

	m_cLiveBackIconWallpaper.LiveBackIconSetMove(220, 479);
	m_cLiveBackIconWallpaper.LiveButton_SetWindow(220, 444, 32, 32);//+20
	m_cLiveBackIconWallpaper.LiveButtonInit("frame\\Button\\Wallpaper.png");
	
	m_cLiveBackIconColor.LiveBackIconSetMove(262, 479);
	m_cLiveBackIconColor.LiveButton_SetWindow(262, 444, 32, 32);//+20
	m_cLiveBackIconColor.LiveButtonInit("frame\\Button\\Color.png");

	m_cLiveBackIconChange.LiveBackIconSetMove(304, 479);
	m_cLiveBackIconChange.LiveButton_SetWindow(304, 444, 32, 32);//+20
	m_cLiveBackIconChange.LiveButtonInit("frame\\Button\\Change.png");

	m_cLiveBackIconHome.LiveBackIconSetClick(true);

	//���ø���Tab
	m_cLiveTabConfig.LiveTabConfigSetMouse(&m_sMousePoint);
	m_cLiveTabConfig.LiveTabConfigInit();

	//��ʼ��Lua
	m_pLiveLua = new CLiveLua("script\\LiveUI.lua");
	bRet = m_pLiveLua->LiveLuaInit();
	if (!bRet)
	{
		return FALSE;
	}

	//��ȡLua����
	m_pLiveLua->LiveLuaGetGlobalInt("Animation_Alpha_Min", m_nAnimationAlphaMin);
	m_pLiveLua->LiveLuaGetGlobalInt("Animation_Alpha_Max", m_nAnimationAlphaMax);
	m_pLiveLua->LiveLuaGetGlobalInt("Animation_Alpha_Step", m_nAnimationAlphaStep);

	//�޸Ĵ�����ʽ
	::SetWindowLong(g_hWnd, GWL_EXSTYLE, ::GetWindowLong(g_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetTimer(g_hWnd, LIVEUI_TIMER_ALPHA, 10, NULL);

	//�ػ洰�ڶ�ʱ��
	SetTimer(g_hWnd, LIVEUI_TIMER_REPAINT, 10, NULL);

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 ReleaseWindowExtra()
// @Purpose: CLiveUI�ͷŴ�����Դ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::ReleaseWindowExtra()
{

}

//------------------------------------------------------------------
// @Function:	 UpdateWindow()
// @Purpose: CLiveUI����ˢ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::UpdateWindow()
{
	static bool bStart = false;
	static bool bClose = false;
	static double dVPanel = 5.0;

	//<<<֡����
	m_nFrame++;
	if (m_nFrame > 16 && (!bStart))
	{
		m_nFrame = 16;
		m_bFrame = true;
	}

	//<<<��ʽ��ʼPanel�仯
	if (m_bFrame)
	{
		m_cLiveBackPanel.m_nMoveY -= (int)dVPanel;
		m_cLiveBackIconHome.m_nMoveY -= (int)dVPanel;
		m_cLiveBackIconPhone.m_nMoveY -= (int)dVPanel;
		m_cLiveBackIconConfig.m_nMoveY -= (int)dVPanel;
		m_cLiveBackIconCard.m_nMoveY -= (int)dVPanel;
		m_cLiveBackIconWallpaper.m_nMoveY -= (int)dVPanel;
		m_cLiveBackIconColor.m_nMoveY -= (int)dVPanel;
		m_cLiveBackIconChange.m_nMoveY -= (int)dVPanel;

		dVPanel -= 0.3125;
		if (dVPanel <= 0.0)
		{
			dVPanel = 0.0;
			bStart = true;
			m_bFrame = false;
		}

	}

	//<<<��ʽ����Panel�仯
	if (m_bWindowClosing && (!bClose))
	{
		m_cLiveBackPanel.m_nMoveY += (int)dVPanel;
		m_cLiveBackIconHome.m_nMoveY += (int)dVPanel;
		m_cLiveBackIconPhone.m_nMoveY += (int)dVPanel;
		m_cLiveBackIconConfig.m_nMoveY += (int)dVPanel;
		m_cLiveBackIconCard.m_nMoveY += (int)dVPanel;
		m_cLiveBackIconWallpaper.m_nMoveY += (int)dVPanel;
		m_cLiveBackIconColor.m_nMoveY += (int)dVPanel;
		m_cLiveBackIconChange.m_nMoveY += (int)dVPanel;

		dVPanel += 0.3125;
		if (dVPanel > 5.0)
		{
			dVPanel = 5.0;
			bClose = true;
		}
	}

}

//------------------------------------------------------------------
// @Function:	 RePaintWindow()
// @Purpose: CLiveUI�����ػ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::RePaintWindow()
{
	HDC hDC;
	HDC hMemDC;
	HBITMAP hBitmap;
	HBRUSH hBrush;
	HFONT hFont;
	RECT Rect;
	int nWidth;
	int nHeight;

	//�û������С
	GetClientRect(g_hWnd, &Rect);
	nWidth = Rect.right - Rect.left;
	nHeight = Rect.bottom - Rect.top;

	//����׼��
	hDC = GetDC(g_hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	hBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	hFont = CreateFontW(-14, -7, 0, 0, 400, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Consola"));

	SelectObject(hMemDC, hFont);
	SelectObject(hMemDC, hBrush);
	SelectObject(hMemDC, hBitmap);

	//���ƴ��ڱ���
	FillRect(hMemDC, &Rect, hBrush);

	//���ƴ��ڱ���
	m_cLiveBackGround.LiveBackGroundPaint(hMemDC);

	//����ҳ�汳��
	m_cLiveTabConfig.LiveTabConfigPaint(hMemDC);

	//������������
	m_cLiveBackPanel.LiveBackPanelPaint(hMemDC);

	//����ͼ��
	m_cLiveBackIconHome.LiveBackIconPaint(hMemDC, m_sMousePoint);
	m_cLiveBackIconPhone.LiveBackIconPaint(hMemDC, m_sMousePoint);
	m_cLiveBackIconConfig.LiveBackIconPaint(hMemDC, m_sMousePoint);
	m_cLiveBackIconCard.LiveBackIconPaint(hMemDC, m_sMousePoint);
	m_cLiveBackIconWallpaper.LiveBackIconPaint(hMemDC, m_sMousePoint);
	m_cLiveBackIconColor.LiveBackIconPaint(hMemDC, m_sMousePoint);
	m_cLiveBackIconChange.LiveBackIconPaint(hMemDC, m_sMousePoint);
	
	//���Ƶ�����Ϣ
	char chArr[MAX_PATH] = { 0 };
	
	SetBkMode(hMemDC, TRANSPARENT);

	memset(chArr, 0, MAX_PATH);
	sprintf_s(chArr, "X:%d", m_sMousePoint.x);
	//TextOutA(hMemDC, 0, 0, chArr, strlen(chArr));

	memset(chArr, 0, MAX_PATH);
	sprintf_s(chArr, "Y:%d", m_sMousePoint.y);
	//TextOutA(hMemDC, 0, 14, chArr, strlen(chArr));

	//�ڴ�DC����������DC
	BitBlt(hDC, 0, 0, USER_SCREENWIDTH, USER_SCREENHEIGHT, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(hFont);
	DeleteObject(hBrush);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(g_hWnd, hDC);
}

//==================================================================
// ~�㷨����
//==================================================================

//------------------------------------------------------------------
// @Function:	 ShowWindowAlpha()
// @Purpose: CLiveUI����Alpha�仯
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::ShowWindowAlpha(bool& bState, int& nAlpha)
{
	if (!bState)
	{
		nAlpha += m_nAnimationAlphaStep;
		if (nAlpha > 255)
		{
			nAlpha = 255;
			KillTimer(g_hWnd, LIVEUI_TIMER_ALPHA);
		}
	}
	else
	{
		nAlpha -= m_nAnimationAlphaStep;
		if (nAlpha < 0)
		{
			nAlpha = 0;
			KillTimer(g_hWnd, LIVEUI_TIMER_ALPHA);
			m_bWindowClosed = true;
			::PostMessage(g_hWnd, WM_CLOSE, 0, 0);
		}
	}

	SetLayeredWindowAttributes(g_hWnd, 0, nAlpha, LWA_ALPHA);
}

//------------------------------------------------------------------
// @Function:	 LButtonClickEvent()
// @Purpose: CLiveUI���������������¼�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveUI::LButtonClickEvent()
{
	//<<<���--��ҳ����
	if (m_cLiveBackIconHome.LiveBackIconIsHover(m_sMousePoint))
	{
		m_cLiveBackIconHome.LiveBackIconSetClick(true);
		m_cLiveBackIconPhone.LiveBackIconSetClick(false);
		m_cLiveBackIconConfig.LiveBackIconSetClick(false);
		m_cLiveBackIconCard.LiveBackIconSetClick(false);
		m_cLiveBackIconWallpaper.LiveBackIconSetClick(false);
		m_cLiveBackIconColor.LiveBackIconSetClick(false);
		m_cLiveBackIconChange.LiveBackIconSetClick(false);

		m_cLiveTabConfig.LiveTabSetShowState(false);
	}

	//<<<���--�绰����
	if (m_cLiveBackIconPhone.LiveBackIconIsHover(m_sMousePoint))
	{
		m_cLiveBackIconHome.LiveBackIconSetClick(false);
		m_cLiveBackIconPhone.LiveBackIconSetClick(true);
		m_cLiveBackIconConfig.LiveBackIconSetClick(false);
		m_cLiveBackIconCard.LiveBackIconSetClick(false);
		m_cLiveBackIconWallpaper.LiveBackIconSetClick(false);
		m_cLiveBackIconColor.LiveBackIconSetClick(false);
		m_cLiveBackIconChange.LiveBackIconSetClick(false);

		m_cLiveTabConfig.LiveTabSetShowState(false);
	}

	//<<<���--���ð���
	if (m_cLiveBackIconConfig.LiveBackIconIsHover(m_sMousePoint))
	{
		m_cLiveBackIconHome.LiveBackIconSetClick(false);
		m_cLiveBackIconPhone.LiveBackIconSetClick(false);
		m_cLiveBackIconConfig.LiveBackIconSetClick(true);
		m_cLiveBackIconCard.LiveBackIconSetClick(false);
		m_cLiveBackIconWallpaper.LiveBackIconSetClick(false);
		m_cLiveBackIconColor.LiveBackIconSetClick(false);
		m_cLiveBackIconChange.LiveBackIconSetClick(false);

		m_cLiveTabConfig.LiveTabSetShowState(true);
	}

	//<<<���--��Ƭ����
	if (m_cLiveBackIconCard.LiveBackIconIsHover(m_sMousePoint))
	{
		m_cLiveBackIconHome.LiveBackIconSetClick(false);
		m_cLiveBackIconPhone.LiveBackIconSetClick(false);
		m_cLiveBackIconConfig.LiveBackIconSetClick(false);
		m_cLiveBackIconCard.LiveBackIconSetClick(true);
		m_cLiveBackIconWallpaper.LiveBackIconSetClick(false);
		m_cLiveBackIconColor.LiveBackIconSetClick(false);
		m_cLiveBackIconChange.LiveBackIconSetClick(false);

		m_cLiveTabConfig.LiveTabSetShowState(false);
	}

	//<<<���--��ֽ����
	if (m_cLiveBackIconWallpaper.LiveBackIconIsHover(m_sMousePoint))
	{
		m_cLiveBackIconHome.LiveBackIconSetClick(false);
		m_cLiveBackIconPhone.LiveBackIconSetClick(false);
		m_cLiveBackIconConfig.LiveBackIconSetClick(false);
		m_cLiveBackIconCard.LiveBackIconSetClick(false);
		m_cLiveBackIconWallpaper.LiveBackIconSetClick(true);
		m_cLiveBackIconColor.LiveBackIconSetClick(false);
		m_cLiveBackIconChange.LiveBackIconSetClick(false);

		m_cLiveTabConfig.LiveTabSetShowState(false);
	}

	//<<<���--��ɫ����
	if (m_cLiveBackIconColor.LiveBackIconIsHover(m_sMousePoint))
	{
		m_cLiveBackIconHome.LiveBackIconSetClick(false);
		m_cLiveBackIconPhone.LiveBackIconSetClick(false);
		m_cLiveBackIconConfig.LiveBackIconSetClick(false);
		m_cLiveBackIconCard.LiveBackIconSetClick(false);
		m_cLiveBackIconWallpaper.LiveBackIconSetClick(false);
		m_cLiveBackIconColor.LiveBackIconSetClick(true);
		m_cLiveBackIconChange.LiveBackIconSetClick(false);

		m_cLiveTabConfig.LiveTabSetShowState(false);
	}

	//<<<���--�任����
	if (m_cLiveBackIconChange.LiveBackIconIsHover(m_sMousePoint))
	{
		m_cLiveBackIconHome.LiveBackIconSetClick(false);
		m_cLiveBackIconPhone.LiveBackIconSetClick(false);
		m_cLiveBackIconConfig.LiveBackIconSetClick(false);
		m_cLiveBackIconCard.LiveBackIconSetClick(false);
		m_cLiveBackIconWallpaper.LiveBackIconSetClick(false);
		m_cLiveBackIconColor.LiveBackIconSetClick(false);
		m_cLiveBackIconChange.LiveBackIconSetClick(true);

		m_cLiveTabConfig.LiveTabSetShowState(false);
	}

	//<<<...
	
	//===============================
	// ����ҳ��
	//===============================
	if (m_cLiveTabConfig.LiveTabGetShowState())
	{
		//---------------��Ƶģʽ------------------
		// ѡ��Ĭ��ģʽ
		if (m_cLiveTabConfig.m_cRadioLiveModeDefault.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveModeDefault.LiveRadioSetSelectState(true);
			m_cLiveTabConfig.m_cRadioLiveModeSelect.LiveRadioSetSelectState(false);
		}
		
		// ѡ��ѡ��ģʽ
		if (m_cLiveTabConfig.m_cRadioLiveModeSelect.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveModeDefault.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveModeSelect.LiveRadioSetSelectState(true);
		}

		//---------------��Ƶģʽ------------------
		// ѡ��������Ƶ
		if (m_cLiveTabConfig.m_cRadioLiveAudioUse.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveAudioUse.LiveRadioSetSelectState(true);
			m_cLiveTabConfig.m_cRadioLiveAudioNoUse.LiveRadioSetSelectState(false);
		}

		// ѡ�н�����Ƶ
		if (m_cLiveTabConfig.m_cRadioLiveAudioNoUse.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveAudioUse.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveAudioNoUse.LiveRadioSetSelectState(true);
		}

		//--------------��������------------------
		// ѡ��������ʾ�Կ�FPS
		if (m_cLiveTabConfig.m_cRadioLiveFPS.LiveRadioIsHover(m_sMousePoint))
		{
			if (m_cLiveTabConfig.m_cRadioLiveFPS.LiveRadioGetSelectState())
			{
				m_cLiveTabConfig.m_cRadioLiveFPS.LiveRadioSetSelectState(false);
			}
			else
			{
				m_cLiveTabConfig.m_cRadioLiveFPS.LiveRadioSetSelectState(true);
			}
		}

		// ѡ��������ϸ��־
		if (m_cLiveTabConfig.m_cRadioLiveLog.LiveRadioIsHover(m_sMousePoint))
		{
			if (m_cLiveTabConfig.m_cRadioLiveLog.LiveRadioGetSelectState())
			{
				m_cLiveTabConfig.m_cRadioLiveLog.LiveRadioSetSelectState(false);
			}
			else
			{
				m_cLiveTabConfig.m_cRadioLiveLog.LiveRadioSetSelectState(true);
			}
		}

		//--------------��ʾģʽ-----------------
		// ѡ�����ģʽ
		if (m_cLiveTabConfig.m_cRadioLiveShowOne.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveShowOne.LiveRadioSetSelectState(true);
			m_cLiveTabConfig.m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		}

		// ѡ����Ӧģʽ
		if (m_cLiveTabConfig.m_cRadioLiveShowTwo.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowTwo.LiveRadioSetSelectState(true);
			m_cLiveTabConfig.m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		}

		// ѡ������ģʽ
		if (m_cLiveTabConfig.m_cRadioLiveShowThree.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowThree.LiveRadioSetSelectState(true);
			m_cLiveTabConfig.m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		}

		// ѡ��ƽ��ģʽ
		if (m_cLiveTabConfig.m_cRadioLiveShowFour.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFour.LiveRadioSetSelectState(true);
			m_cLiveTabConfig.m_cRadioLiveShowFive.LiveRadioSetSelectState(false);
		}

		// ѡ�о���ģʽ
		if (m_cLiveTabConfig.m_cRadioLiveShowFive.LiveRadioIsHover(m_sMousePoint))
		{
			m_cLiveTabConfig.m_cRadioLiveShowOne.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowTwo.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowThree.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFour.LiveRadioSetSelectState(false);
			m_cLiveTabConfig.m_cRadioLiveShowFive.LiveRadioSetSelectState(true);
		}

		// Ĭ����Ƶѡ��
		if (m_cLiveTabConfig.m_cRollCtrlDefault.LiveRollCtrlIsLeftHover(m_sMousePoint))		// ���
		{
			m_cLiveTabConfig.m_cRollCtrlDefault.LiveRollCtrl_SetLeftClick(true);
			m_cLiveTabConfig.m_cRollCtrlDefault.LiveRollCtrl_SetRightClick(false);
		}

		if (m_cLiveTabConfig.m_cRollCtrlDefault.LiveRollCtrlIsRightHover(m_sMousePoint))	// �Ҽ�
		{
			m_cLiveTabConfig.m_cRollCtrlDefault.LiveRollCtrl_SetLeftClick(false);
			m_cLiveTabConfig.m_cRollCtrlDefault.LiveRollCtrl_SetRightClick(true);
		}

	}

}

//==================================================================
// ~��Ϣ��Ӧ
//==================================================================

//------------------------------------------------------------------
// @Function:	 OnTimer()
// @Purpose: CLiveUI��ʱ����Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnTimer(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case LIVEUI_TIMER_ALPHA:
		ShowWindowAlpha(m_bWindowState, m_nWindowAlpha);
		break;
	case LIVEUI_TIMER_REPAINT:
		UpdateWindow();
		RePaintWindow();
		break;
	default:
		break;
	}

	return DefWindowProc(g_hWnd, WM_TIMER, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnClose()
// @Purpose: CLiveUI���ڹر���Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnClose(WPARAM wParam, LPARAM lParam)
{
	LRESULT lr = 0;

	if (!m_bWindowClosed)
	{
		if (!m_bWindowClosing)
		{
			m_bWindowState = true;
			m_bWindowClosing = true;
			SetTimer(g_hWnd, LIVEUI_TIMER_ALPHA, 10, NULL);
		}
	}
	else
	{
		lr = DefWindowProc(g_hWnd, WM_CLOSE, wParam, lParam);
	}

	return lr;
}

//------------------------------------------------------------------
// @Function:	 OnMouseMove()
// @Purpose: CLiveUI����ƶ���Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	m_sMousePoint.x = (LONG)LOWORD(lParam);
	m_sMousePoint.y = (LONG)HIWORD(lParam);

	if (m_bMouseTrack)
	{
		TRACKMOUSEEVENT csTME = { 0 };
		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE;
		csTME.hwndTrack = g_hWnd;
		::_TrackMouseEvent(&csTME);

		m_bMouseTrack = false;
	}



	return DefWindowProc(g_hWnd, WM_MOUSEMOVE, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnMouseLeave()
// @Purpose: CLiveUI����뿪��Ӧ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_sMousePoint.x = 0;
	m_sMousePoint.y = 0;

	m_bMouseTrack = true;

	return DefWindowProc(g_hWnd, WM_MOUSELEAVE, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnLButtonUp()
// @Purpose: CLiveUI�������ͷ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(g_hWnd, WM_LBUTTONUP, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnLButtonDown()
// @Purpose: CLiveUI����������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	LButtonClickEvent();
	return DefWindowProc(g_hWnd, WM_LBUTTONDOWN, wParam, lParam);
}

//------------------------------------------------------------------
// @Function:	 OnLButtonDblClk()
// @Purpose: CLiveUI������˫��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveUI::OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	LButtonClickEvent();
	return DefWindowProc(g_hWnd, WM_NCLBUTTONDBLCLK, wParam, lParam);
}