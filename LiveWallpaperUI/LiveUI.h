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
	int m_nWindowAlpha;				//窗口Alpha值
	bool m_bWindowState;			//窗口Alpha状态
	bool m_bWindowClosed;			//窗口关闭状态
	bool m_bWindowClosing;			//窗口正在关闭状态

	//<<<Lua Script
	CLiveLua* m_pLiveLua;			//窗口Lua文件
	int m_nAnimationAlphaMin;		//窗口Alpha最小值
	int m_nAnimationAlphaMax;		//窗口Alpha最大值
	int m_nAnimationAlphaStep;		//窗口Alpha步长

private:
	void ShowWindowAlpha(bool& bState, int& nAlpha);

public:
	CLiveUI();
	~CLiveUI();

	//<<<(构造/析构)
	void ConstructExtra();			//构造窗口资源
	void DestructExtra();			//析构窗口资源

	//<<<(初始化/释放)
	BOOL InitWindowExtra();			//初始化窗口资源
	void ReleaseWindowExtra();		//释放回收窗口资源

	//<<<重绘窗口
	void RePaintWindow();			//重绘窗口

public:
	LRESULT OnTimer(WPARAM wParam, LPARAM lParam);	//定时消息响应
	LRESULT OnClose(WPARAM wParam, LPARAM lParam);	//关闭消息响应

};

//Variable Definition
extern CLiveUI g_cLiveUI;
extern CLiveUI* g_pLiveUI;

#endif // !__LIVEUI_H_


