/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		Cherryfps.h
* @brief	This File is Cherryfps DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-1-1	v1.00a	alopex	Create This File
*/
#pragma once

#ifndef __CHERRYFPS_H_
#define __CHERRYFPS_H_

//Include DirectX Common Header File
#include "DirectCommon.h"
#include "DirectFont.h"

//Macro Definition
#ifdef	CHERRYFPS_EXPORTS
#define CHERRYFPS_API	__declspec(dllexport)
#else
#define CHERRYFPS_API	__declspec(dllimport)
#endif

//Class Definition
class CCherryfps
{
private:
	DirectFont* m_pFont;			//Cherryfps Font
	float m_fps;					//Cherryfps Value

public:
	CCherryfps();					//Cherryfps (~构造函数)
	~CCherryfps();					//Cherryfps (~析构函数)

	CCherryfps(IDirect3DDevice9* pD3D9Device);						//Cherryfps (~构造函数)

	//初始化
	void CherryfpsInit(int nFontSize, LPWSTR lpszFontType);			//Cherryfps (~初始化)

	//计算
	void CherryfpsGetfps(void);										//Cherryfps Get fps    (获取fps)
	void CherryfpsGetfpsEx(float fTimeDelta, float* pfps);			//Cherryfps Get fps Ex (获取fps)
	void CherryfpsGetfpsEx(float* pfps);							//Cherryfps Get fps Ex (获取fps)
	float CherryfpsGetfpsEx(float fTimeDelta);						//Cherryfps Get fps Ex (获取fps)
	float CherryfpsGetfpsEx(void);									//Cherryfps Get fps Ex (获取fps)

	//绘制
	void CherryfpsDrawfps(HWND hWnd);								//Cherryfps Draw fps (~绘制fps)
	void CherryfpsDrawfps(HWND hWnd, DWORD Format);					//Cherryfps Draw fps (~绘制fps)
	void CherryfpsDrawfps(HWND hWnd, DWORD Format, D3DCOLOR Color);	//Cherryfps Draw fps (~绘制fps)
};

#endif