/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics.h
* @brief	This Program is DirectGraphics DLL Project.
* @author	Alopex/Helium
* @version	v1.21a
* @date		2017-11-2	v1.00a	alopex	Create Project.
* @date		2017-12-2	v1.01a	alopex	Add D3DXFont.
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-2-11	v1.22a	alopex	Add D3D9 Lost Device Function.
*/
#pragma once

#ifndef __DIRECTGRAPHICS_H_
#define __DIRECTGRAPHICS_H_

//Macro Definition
#ifdef	DIRECTGRAPHICS_EXPORTS
#define DIRECTGRAPHICS_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS_API	__declspec(dllimport)
#endif

#ifndef USER_SCREENWIDTH
#define USER_SCREENWIDTH	640		//UserScreenWidth(~窗口区域宽度)
#endif

#ifndef USER_SCREENHEIGHT
#define USER_SCREENHEIGHT	480		//UserScreenHeight(~窗口区域高度)
#endif

#define ADAPTERTYPESIZE		50		//AdapterType Size(~存储显卡型号数组)

//Struct Definition

//CallBack Definition

//Class Definition
class DirectGraphics
{
private:
	IDirect3D9* m_pD3D9;				//The Direct3D 9 Main Object(~D3D9对象)
	IDirect3DDevice9* m_pD3D9Device;	//The Direct3D 9 Render Device(~D3D9设备对象)
	D3DCAPS9 m_D3D9Caps;				//The Direct3D 9 Caps(~D3D9设备状态)
	D3DPRESENT_PARAMETERS m_D3D9pp;		//The Direct3D 9 Parameters(~D3D9设备参数)
	ID3DXFont* m_pD3DXFont;				//The Direct3D 9 Font(~D3D9字体:显卡型号显示)
	wchar_t m_wcD3D9AdapterType[ADAPTERTYPESIZE];	//The Direct3D 9 AdapterType(eg:NVIDIA GeForce GT750M)

	CRITICAL_SECTION m_cs;				//Thread Safe(CriticalSection)(~D3D9临界区变量)
	bool m_bThreadSafe;					//Thread Safe Status(~D3D9线程安全状态)

public:
	DirectGraphics();					//DirectGraphics Constructor Function(~DirectGraphics构造函数)
	~DirectGraphics();					//DirectGraphics Destructor	Function(~DirectGraphics析构函数)

	virtual IDirect3D9* WINAPI DirectGraphicsGetObject(void) const;			//DirectGraphics Get Object(~DirectGraphics获取D3D9对象)
	virtual IDirect3DDevice9* WINAPI DirectGraphicsGetDevice(void) const;	//DirectGraphics Get Device(~DirectGraphics获取D3D9设备对象)
	virtual const D3DCAPS9* WINAPI DirectGraphicsGetCaps(void) const;		//DirectGraphics Get Caps(~DirectGraphics获取D3D9设备状态)
	virtual const D3DPRESENT_PARAMETERS* WINAPI DirectGraphicsGetPresentParameters(void) const;	//DirectGraphics Get Present Parameters(~DirectGraphics获取D3D9显卡参数)
	virtual const wchar_t* WINAPI DirectGraphicsAdapterType(void) const;	//DirectGraphics Get Adapter Type(~DirectGraphics获取D3D9显卡型号)
	virtual const ID3DXFont* WINAPI DirectGraphicsGetFont(void) const;		//DirectGraphics Get Font(~DirectGraphics获取D3D9字体)

	virtual HRESULT WINAPI DirectGraphicsTestCooperativeLevel(void) const;	//DirectGraphics Get TestCooperativeLevel获取D3D9当前状态
	virtual HRESULT WINAPI DirectGraphicsResetDevice(void);					//DirectGraphics Reset Direct3D 9 Device重置D3D9设备
	virtual HRESULT WINAPI DirectGraphicsGetBackBuffer(IDirect3DSurface9**& ppD3D9BackBuffer);	//DirectGraphics Get BackBuffer获取D3D9表面
	virtual HRESULT WINAPI DirectGraphicsReset(void);						//DirectGraphics Reset & Init重置DirectGraphics并重新初始化

	virtual HRESULT WINAPI DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9**& ppD3D9Surface);//DirectGraphics Create Off-Screen Plain Surface创建离屏表面

	virtual HRESULT WINAPI DirectGraphicsInit(HWND hWnd);					//DirectGraphics Initialization(W:640 H:480 Windowed)(~DirectGraphics初始化:窗口宽度:640,窗口高度:480)
	virtual HRESULT WINAPI DirectGraphicsInit(HWND hWnd, bool bIsWindowed);	//DirectGraphics Initialization(~DirectGraphics初始化 <窗口模式>bIsWindowed = true, <全屏模式>bIsWindowed = false)
	virtual HRESULT WINAPI DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight);	//DirectGraphics Initialization(~DirectGraphics初始化 <窗口模式>bIsWindowed = true, <全屏模式>bIsWindowed = false)
	virtual HRESULT WINAPI DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp);//DirectGraphics Initialization(~DirectGraphics初始化 D3DPRESENT_PARAMETERS结构体参数传入)
	virtual HRESULT WINAPI DirectGraphicsBeginScene(void);					//DirectGraphics Begin Render(~DirectGraphics开始渲染:不进行清除屏幕)
	virtual HRESULT WINAPI DirectGraphicsEndScene(void);					//DirectGraphics End Render(~DirectGraphics结束渲染:不进行翻转显示)
	virtual HRESULT WINAPI DirectGraphicsBegin(void);						//DirectGraphics Begin Render(~DirectGraphics开始渲染:清除屏幕->开始渲染)
	virtual HRESULT WINAPI DirectGraphicsEnd(void);							//DirectGraphics End Render(~DirectGraphics结束渲染:结束渲染->翻转屏幕)
	virtual HRESULT WINAPI DirectGraphicsPresent(void);						//DirectGraphics Present Render(~DirectGraphics翻转屏幕)
	virtual HRESULT WINAPI DirectGraphicsClear(void);						//DirectGraphics Clear Screen(~DirectGraphics清除屏幕:黑色填充)
	virtual HRESULT WINAPI DirectGraphicsClear(DWORD dwColor);				//DirectGraphics Clear Screen(~DirectGraphics清除屏幕:选定颜色填充)
	
	virtual HRESULT WINAPI DirectGraphicsFontInit();						//DirectGraphicsFont Initialization(~DirectGraphics显卡型号字体初始化)
	virtual HRESULT WINAPI DirectGraphicsFontInit(int nFontSize);			//DirectGraphicsFont Initialization(~DirectGraphics显卡型号字体初始化:nFontSize:字体大小)
	virtual HRESULT WINAPI DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType);	//DirectGraphicsFont Initialization(~DirectGraphics显卡型号字体初始化:<nFontSize>:字体大小 <lpszFontType>:字体样式)
	virtual void WINAPI DirectGraphicsFontDrawText(HWND hWnd);							//DirectGraphicsFont Draw Text(~DirectGraphics绘制显卡型号)
	virtual void WINAPI DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor);		//DirectGraphicsFont Draw Text(~DirectGraphics绘制显卡型号:<dwColor>:字体颜色)
};

//Variable Definition

//Function Definition

#endif