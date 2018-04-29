/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		LiveUI.h
* @brief	This Program is LiveWallpaperUI Project.
* @author	alopex
* @version	v1.00a
* @date		2018-04-27
*/
#pragma once

#ifndef __LIVEUI_H_
#define __LIVEUI_H_

//Include Common Header File
#include "Common.h"

//Include Lua Srcipt Class
#include "LiveLua.h"

//Class Definition
class CLiveUI
{
private:
	int m_nWindowAlpha;				//����Alphaֵ
	bool m_bWindowState;			//����Alpha״̬
	bool m_bWindowClosed;			//���ڹر�״̬
	bool m_bWindowClosing;			//�������ڹر�״̬

	//<<<Lua Script
	CLiveLua* m_pLiveLua;			//����Lua�ļ�
	int m_nAnimationAlphaMin;		//����Alpha��Сֵ
	int m_nAnimationAlphaMax;		//����Alpha���ֵ
	int m_nAnimationAlphaStep;		//����Alpha����

private:
	void ShowWindowAlpha(bool& bState, int& nAlpha);

public:
	CLiveUI();
	~CLiveUI();

	//<<<(����/����)
	void ConstructExtra();			//���촰����Դ
	void DestructExtra();			//����������Դ

	//<<<(��ʼ��/�ͷ�)
	BOOL InitWindowExtra();			//��ʼ��������Դ
	void ReleaseWindowExtra();		//�ͷŻ��մ�����Դ

	//<<<�ػ洰��
	void RePaintWindow();			//�ػ洰��

public:
	LRESULT OnTimer(WPARAM wParam, LPARAM lParam);	//��ʱ��Ϣ��Ӧ
	LRESULT OnClose(WPARAM wParam, LPARAM lParam);	//�ر���Ϣ��Ӧ

};

//Variable Definition
extern CLiveUI g_cLiveUI;
extern CLiveUI* g_pLiveUI;

#endif // !__LIVEUI_H_


