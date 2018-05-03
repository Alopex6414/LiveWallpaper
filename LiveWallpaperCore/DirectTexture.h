/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectTexture.h
* @brief	This File is DirectTexture DLL Project.
* @author	Alopex/Helium
* @version	v1.12a
* @date		2017-12-10	v1.00a	alopex	Create This File.
* @date		2018-1-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-4-12	v1.12a	alopex	Add Macro Call Mode.
*/
#pragma once

#ifndef __DIRECTTEXTURE_H_
#define __DIRECTTEXTURE_H_

//Include DirectX Common Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	DIRECTTEXTURE_EXPORTS
#define DIRECTTEXTURE_API	__declspec(dllexport)
#else
#define DIRECTTEXTURE_API	__declspec(dllimport)
#endif

#define DIRECTTEXTURE_CALLMODE	__stdcall

//Class Definition
class DirectTexture
{
private:
	IDirect3DDevice9* m_pD3D9Device;			//The Direct3D 9 Device(D3D9�����豸)
	IDirect3DTexture9* m_pD3D9Texture;			//The Direct3D 9 Texture(D3D9��������)

	CRITICAL_SECTION m_cs;						//Thread Safe(CriticalSection)
	bool m_bThreadSafe;							//Thread Safe Status

public:
	DirectTexture();							//DirectTexture Constructor Function(���캯��)
	~DirectTexture();							//DirectTexture Destructor  Function(��������)

	//����
	DirectTexture(IDirect3DDevice9* pD3D9Device);							//DirectTexture Constructor Function(���캯��)(D3D9�����豸)

	//����
	IDirect3DDevice9* DIRECTTEXTURE_CALLMODE DirectTextureGetDevice(void) const;			//DirectTexture Get D3D9 Device(��ȡD3D9�豸)
	IDirect3DTexture9* DIRECTTEXTURE_CALLMODE DirectTextureGetTexture(void) const;			//DirectTexture Get D3D9 Texture(��ȡD3D9����)

	//����
	void DIRECTTEXTURE_CALLMODE DirectTextureSetDevice(IDirect3DDevice9* pD3D9Device);		//DirectTexture Set D3D9 Device(����D3D9�豸)
	void DIRECTTEXTURE_CALLMODE DirectTextureSetTexture(IDirect3DTexture9* pD3D9Texture);	//DirectTexture Set D3D9 Device(����D3D9����)

	//����
	virtual void DIRECTTEXTURE_CALLMODE DirectTextureReset(void);							//DirectTexture Reset(����D3D9����)

	//��������
	virtual HRESULT DIRECTTEXTURE_CALLMODE DirectTextureLoadTexture(LPWSTR lpszTexture);														//DirectTexture Load Texture(��������)(�ļ�)
	virtual HRESULT DIRECTTEXTURE_CALLMODE DirectTextureLoadTexture(LPCVOID lpSrcData, UINT nSrcDataSize);										//DirectTexture Load Texture(��������)(�ڴ�)
	virtual HRESULT DIRECTTEXTURE_CALLMODE DirectTextureLoadTextureEx(LPWSTR lpszTexture, UINT nWidth, UINT nHeight);							//DirectTexture Load Texture Ex(��������)(�ļ�)
	virtual HRESULT DIRECTTEXTURE_CALLMODE DirectTextureLoadTextureEx(LPCVOID lpSrcData, UINT nSrcDataSize, UINT nWidth, UINT nHeight);			//DirectTexture Load Texture Ex(��������)(�ڴ�)

	//��Ⱦ����
	virtual void DIRECTTEXTURE_CALLMODE DirectTextureSelectTexture(void);					//DirectTexture Select Texture(D3D9�豸ѡ������)

};


#endif