/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectFont.h
* @brief	This File is DirectFont DLL Project.
* @author	Alopex/Helium
* @version	v1.11a
* @date		2017-12-16	v1.00a	alopex	Create This File.
* @date		2018-1-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.10a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-2-12	v1.11a	alopex	Add Reset Device & Definion of DirectFont Colors.
*/
#pragma once

#ifndef __DIRECTFONT_H_
#define __DIRECTFONT_H_

//Include DirectX Common Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	DIRECTFONT_EXPORTS
#define DIRECTFONT_API	__declspec(dllexport)
#else
#define DIRECTFONT_API	__declspec(dllimport)
#endif

#define DIRECTFONT_FORMAT_CENTER		(DT_CENTER)
#define DIRECTFONT_FORMAT_TOPLEFT		(DT_TOP | DT_LEFT)
#define DIRECTFONT_FORMAT_TOPRIGHT		(DT_TOP | DT_RIGHT)
#define DIRECTFONT_FORMAT_BOTTOMLEFT	(DT_BOTTOM | DT_LEFT)
#define DIRECTFONT_FORMAT_BOTTOMRIGHT	(DT_BOTTOM | DT_RIGHT)

#define DIRECTFONT_D3DXCOLOR_WHITE		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define DIRECTFONT_D3DXCOLOR_RED		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
#define DIRECTFONT_D3DXCOLOR_GREEN		(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))
#define DIRECTFONT_D3DXCOLOR_BLUE		(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))
#define DIRECTFONT_D3DXCOLOR_YELLOW		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))

//Class Definition
class DirectFont
{
private:
	IDirect3DDevice9* m_pD3D9Device;			//The Direct3D 9 Device(D3D9�����豸)
	ID3DXFont* m_pD3D9Font;						//The Direct3D 9 Font(D3D9��������)

	CRITICAL_SECTION m_cs;						//Thread Safe(CriticalSection)
	bool m_bThreadSafe;							//Thread Safe Status

public:
	DirectFont();								//DirectFont Constructor Function(���캯��)
	~DirectFont();								//DirectFont Destructor  Function(��������)

	//����
	DirectFont(IDirect3DDevice9* pD3D9Device);	//DirectFont Constructor Function(���캯��)

	//����
	IDirect3DDevice9* WINAPI DirectFontGetDevice(void) const;			//DirectFont Get D3D9 Device(��ȡD3D9�豸)
	ID3DXFont* WINAPI DirectFontGetFont(void) const;					//DirectFont Get D3D9 Font(��ȡD3D9����)

	//����
	void WINAPI DirectFontSetDevice(IDirect3DDevice9* pD3D9Device);		//DirectFont Set D3D9 Device(����D3D9�豸)
	void WINAPI DirectFontSetFont(ID3DXFont* pD3DXFont);				//DirectFont Set D3DX Font(����D3D9����)

	//����
	virtual HRESULT WINAPI DirectFontReset(void);						//DirectFont Reset D3DX Font(����D3DX����)(��ʧ�豸����)

	//��ʼ��
	virtual HRESULT WINAPI DirectFontInit(void);										//DirectFont Create Font(DirectFont��ʼ��)
	virtual HRESULT WINAPI DirectFontInit(int nFontSize);								//DirectFont Create Font(DirectFont��ʼ��)
	virtual HRESULT WINAPI DirectFontInit(int nFontSize, LPWSTR lpszFontType);			//DirectFont Create Font(DirectFont��ʼ��)

	//����
	virtual void WINAPI DirectFontDrawText(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color);			//DirectFont Draw Text(DirectFont����)
	virtual void WINAPI DirectFontDrawTextA(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color);			//DirectFont Draw Text(DirectFont����)
	virtual void WINAPI DirectFontDrawTextW(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color);			//DirectFont Draw Text(DirectFont����)
};

#endif