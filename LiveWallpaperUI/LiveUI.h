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
#include "LiveBackGround.h"
#include "LiveBackPanel.h"
#include "LiveBackIcon.h"
#include "LiveTabConfig.h"

//Include PlumLibrary Header File
#include "PlumLog.h"
#include "PlumConsole.h"

//Include Lua Srcipt Class
#include "LiveLua.h"

//Class Definition
class CLiveUI
{
private:
	//<<<Window Alpha
	int m_nWindowAlpha;				//窗口Alpha值
	bool m_bWindowState;			//窗口Alpha状态
	bool m_bWindowClosed;			//窗口关闭状态
	bool m_bWindowClosing;			//窗口正在关闭状态

	//<<<Window Frame
	int m_nFrame;					//刷新帧数
	bool m_bFrame;					//帧数标志

	//<<<Mouse Point
	bool m_bMouseTrack;				//鼠标离开客户区标志
	POINT m_sMousePoint;			//鼠标坐标值

	//<<<Lua Script
	CLiveLua* m_pLiveLua;			//窗口Lua文件
	int m_nAnimationAlphaMin;		//窗口Alpha最小值
	int m_nAnimationAlphaMax;		//窗口Alpha最大值
	int m_nAnimationAlphaStep;		//窗口Alpha步长

private:
	void ShowWindowAlpha(bool& bState, int& nAlpha);
	void LButtonClickEvent();		//鼠标左键按下响应

public:
	CLiveUI();
	~CLiveUI();

	//<<<(构造/析构)
	void ConstructExtra();			//构造窗口资源
	void DestructExtra();			//析构窗口资源

	//<<<(访问/控制)
	POINT GetMosePoint() const;		//获取鼠标坐标

	//<<<(初始化/释放)
	BOOL InitWindowExtra();			//初始化窗口资源
	void ReleaseWindowExtra();		//释放回收窗口资源

	//<<<重绘窗口
	void UpdateWindow();			//刷新窗口
	void RePaintWindow();			//重绘窗口

protected:
	CLiveBackGround m_cLiveBackGround;		//窗口背景
	CLiveBackPanel m_cLiveBackPanel;		//容器背景

	CLiveBackIcon m_cLiveBackIconHome;		//图标--主页
	CLiveBackIcon m_cLiveBackIconPhone;		//图标--电话
	CLiveBackIcon m_cLiveBackIconConfig;	//图标--设置
	CLiveBackIcon m_cLiveBackIconCard;		//图标--卡片
	CLiveBackIcon m_cLiveBackIconWallpaper;	//图标--壁纸
	CLiveBackIcon m_cLiveBackIconColor;		//图标--彩色
	CLiveBackIcon m_cLiveBackIconChange;	//图标--改变

	CLiveTabConfig m_cLiveTabConfig;		//Tab--设置

public:
	LRESULT OnTimer(WPARAM wParam, LPARAM lParam);	//定时消息响应
	LRESULT OnClose(WPARAM wParam, LPARAM lParam);	//关闭消息响应
	LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);	//鼠标移动消息响应
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);	//鼠标离开消息响应
	LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);	//鼠标左键释放消息响应
	LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);//鼠标左键按下消息响应
	LRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);	//鼠标左键双击消息响应

};

//Variable Definition
extern CLiveUI g_cLiveUI;
extern CLiveUI* g_pLiveUI;

#endif // !__LIVEUI_H_


