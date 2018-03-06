/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSurface.h
* @brief	This File is DirectSurface DLL Project.
* @author	Alopex/Helium
* @version	v1.11a
* @date		2017-12-9	v1.00a	alopex	Create This File.
* @date		2018-1-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
*/
#ifndef __DIRECTSURFACE_H_
#define __DIRECTSURFACE_H_

//Include Windows Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	DIRECTSURFACE_EXPORTS
#define DIRECTSURFACE_API	__declspec(dllexport)
#else
#define DIRECTSURFACE_API	__declspec(dllimport)
#endif

//Class Definition
class DirectSurface
{
private:
	IDirect3DDevice9*	m_pD3D9Device;										//The Direct3D 9 Device(D3D9绘制设备)
	IDirect3DSurface9*	m_pD3D9Surface;										//The Direct3D 9 Surface(D3D9绘制表面)
	IDirect3DSurface9*	m_pD3D9BackSurface;									//The Direct3D 9 Surface(D3D9后台表面)

	CRITICAL_SECTION m_cs;													//Thread Safe(CriticalSection)
	bool m_bThreadSafe;														//Thread Safe Status

public:
	DirectSurface();														//DirectSurface Constructor Function(构造函数)
	~DirectSurface();														//DirectSurface Destructor  Function(析构函数)

	//构造
	DirectSurface(IDirect3DDevice9* pD3D9Device);							//DirectSurface Constructor Function(构造函数)

	//访问
	IDirect3DDevice9* WINAPI DirectSurfaceGetDevice(void) const;			//DirectSurface Get D3D9Device(获取D3D9设备)
	IDirect3DSurface9* WINAPI DirectSurfaceGetSurface(void) const;			//DirectSurface Get D3D9Surface(获取D3D9表面)

	//控制
	void WINAPI DirectSurfaceSetDevice(IDirect3DDevice9* pD3D9Device);		//DirectSurface Set D3D9Device(设置D3D9设备)
	void WINAPI DirectSurfaceSetSurface(IDirect3DSurface9* pD3D9Surface);	//DirectSurface Set D3D9Surface(获取D3D9表面)

	//初始化
	virtual HRESULT WINAPI DirectSurfaceInit(void);							//DirectSurface Initialize(DirectSurface初始化)

	//加载表面
	virtual HRESULT WINAPI DirectSurfaceLoadSurface(LPWSTR lpszSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);										//DirectSurface Load Surface From File(DirectSurface导入纹理)(文件加载)
	virtual HRESULT WINAPI DirectSurfaceLoadSurface(IDirect3DSurface9* pSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);							//DirectSurface Load Surface From File(DirectSurface导入纹理)(表面加载)
	virtual HRESULT WINAPI DirectSurfaceLoadSurface(LPCVOID lpcszArray, UINT nArraySize, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);					//DirectSurface Load Surface From File(DirectSurface导入纹理)(内存文件加载)
	virtual HRESULT WINAPI DirectSurfaceLoadSurface(LPCVOID lpcszArray, D3DFORMAT Format, UINT nPitch, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);		//DirectSurface Load Surface From File(DirectSurface导入纹理)(内存加载)

	//渲染表面
	virtual void WINAPI DirectSurfaceRender(const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);																	//DirectSurface Render Surface(纹理)
	virtual void WINAPI DirectSurfaceRender(DWORD dwColor);																												//DirectSurface Render Surface(纯色)				

};


#endif