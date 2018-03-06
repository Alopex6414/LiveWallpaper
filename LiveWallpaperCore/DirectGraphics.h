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
#define USER_SCREENWIDTH	640		//UserScreenWidth(~����������)
#endif

#ifndef USER_SCREENHEIGHT
#define USER_SCREENHEIGHT	480		//UserScreenHeight(~��������߶�)
#endif

#define ADAPTERTYPESIZE		50		//AdapterType Size(~�洢�Կ��ͺ�����)

//Struct Definition

//CallBack Definition

//Class Definition
class DirectGraphics
{
private:
	IDirect3D9* m_pD3D9;				//The Direct3D 9 Main Object(~D3D9����)
	IDirect3DDevice9* m_pD3D9Device;	//The Direct3D 9 Render Device(~D3D9�豸����)
	D3DCAPS9 m_D3D9Caps;				//The Direct3D 9 Caps(~D3D9�豸״̬)
	D3DPRESENT_PARAMETERS m_D3D9pp;		//The Direct3D 9 Parameters(~D3D9�豸����)
	ID3DXFont* m_pD3DXFont;				//The Direct3D 9 Font(~D3D9����:�Կ��ͺ���ʾ)
	wchar_t m_wcD3D9AdapterType[ADAPTERTYPESIZE];	//The Direct3D 9 AdapterType(eg:NVIDIA GeForce GT750M)

	CRITICAL_SECTION m_cs;				//Thread Safe(CriticalSection)(~D3D9�ٽ�������)
	bool m_bThreadSafe;					//Thread Safe Status(~D3D9�̰߳�ȫ״̬)

public:
	DirectGraphics();					//DirectGraphics Constructor Function(~DirectGraphics���캯��)
	~DirectGraphics();					//DirectGraphics Destructor	Function(~DirectGraphics��������)

	virtual IDirect3D9* WINAPI DirectGraphicsGetObject(void) const;			//DirectGraphics Get Object(~DirectGraphics��ȡD3D9����)
	virtual IDirect3DDevice9* WINAPI DirectGraphicsGetDevice(void) const;	//DirectGraphics Get Device(~DirectGraphics��ȡD3D9�豸����)
	virtual const D3DCAPS9* WINAPI DirectGraphicsGetCaps(void) const;		//DirectGraphics Get Caps(~DirectGraphics��ȡD3D9�豸״̬)
	virtual const D3DPRESENT_PARAMETERS* WINAPI DirectGraphicsGetPresentParameters(void) const;	//DirectGraphics Get Present Parameters(~DirectGraphics��ȡD3D9�Կ�����)
	virtual const wchar_t* WINAPI DirectGraphicsAdapterType(void) const;	//DirectGraphics Get Adapter Type(~DirectGraphics��ȡD3D9�Կ��ͺ�)
	virtual const ID3DXFont* WINAPI DirectGraphicsGetFont(void) const;		//DirectGraphics Get Font(~DirectGraphics��ȡD3D9����)

	virtual HRESULT WINAPI DirectGraphicsTestCooperativeLevel(void) const;	//DirectGraphics Get TestCooperativeLevel��ȡD3D9��ǰ״̬
	virtual HRESULT WINAPI DirectGraphicsResetDevice(void);					//DirectGraphics Reset Direct3D 9 Device����D3D9�豸
	virtual HRESULT WINAPI DirectGraphicsGetBackBuffer(IDirect3DSurface9**& ppD3D9BackBuffer);	//DirectGraphics Get BackBuffer��ȡD3D9����
	virtual HRESULT WINAPI DirectGraphicsReset(void);						//DirectGraphics Reset & Init����DirectGraphics�����³�ʼ��

	virtual HRESULT WINAPI DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9**& ppD3D9Surface);//DirectGraphics Create Off-Screen Plain Surface������������

	virtual HRESULT WINAPI DirectGraphicsInit(HWND hWnd);					//DirectGraphics Initialization(W:640 H:480 Windowed)(~DirectGraphics��ʼ��:���ڿ��:640,���ڸ߶�:480)
	virtual HRESULT WINAPI DirectGraphicsInit(HWND hWnd, bool bIsWindowed);	//DirectGraphics Initialization(~DirectGraphics��ʼ�� <����ģʽ>bIsWindowed = true, <ȫ��ģʽ>bIsWindowed = false)
	virtual HRESULT WINAPI DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight);	//DirectGraphics Initialization(~DirectGraphics��ʼ�� <����ģʽ>bIsWindowed = true, <ȫ��ģʽ>bIsWindowed = false)
	virtual HRESULT WINAPI DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp);//DirectGraphics Initialization(~DirectGraphics��ʼ�� D3DPRESENT_PARAMETERS�ṹ���������)
	virtual HRESULT WINAPI DirectGraphicsBeginScene(void);					//DirectGraphics Begin Render(~DirectGraphics��ʼ��Ⱦ:�����������Ļ)
	virtual HRESULT WINAPI DirectGraphicsEndScene(void);					//DirectGraphics End Render(~DirectGraphics������Ⱦ:�����з�ת��ʾ)
	virtual HRESULT WINAPI DirectGraphicsBegin(void);						//DirectGraphics Begin Render(~DirectGraphics��ʼ��Ⱦ:�����Ļ->��ʼ��Ⱦ)
	virtual HRESULT WINAPI DirectGraphicsEnd(void);							//DirectGraphics End Render(~DirectGraphics������Ⱦ:������Ⱦ->��ת��Ļ)
	virtual HRESULT WINAPI DirectGraphicsPresent(void);						//DirectGraphics Present Render(~DirectGraphics��ת��Ļ)
	virtual HRESULT WINAPI DirectGraphicsClear(void);						//DirectGraphics Clear Screen(~DirectGraphics�����Ļ:��ɫ���)
	virtual HRESULT WINAPI DirectGraphicsClear(DWORD dwColor);				//DirectGraphics Clear Screen(~DirectGraphics�����Ļ:ѡ����ɫ���)
	
	virtual HRESULT WINAPI DirectGraphicsFontInit();						//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��)
	virtual HRESULT WINAPI DirectGraphicsFontInit(int nFontSize);			//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��:nFontSize:�����С)
	virtual HRESULT WINAPI DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType);	//DirectGraphicsFont Initialization(~DirectGraphics�Կ��ͺ������ʼ��:<nFontSize>:�����С <lpszFontType>:������ʽ)
	virtual void WINAPI DirectGraphicsFontDrawText(HWND hWnd);							//DirectGraphicsFont Draw Text(~DirectGraphics�����Կ��ͺ�)
	virtual void WINAPI DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor);		//DirectGraphicsFont Draw Text(~DirectGraphics�����Կ��ͺ�:<dwColor>:������ɫ)
};

//Variable Definition

//Function Definition

#endif