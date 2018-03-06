/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSurface.cpp
* @brief	This File is DirectSurface DLL Project.
* @author	Alopex/Helium
* @version	v1.11a
* @date		2017-12-9	v1.00a	alopex	Create This File.
* @date		2018-1-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
*/
#include "DirectCommon.h"
#include "DirectSurface.h"
#include "DirectThreadSafe.h"

//DriectSurface��Ҫ����2D��Ϸ��������

//------------------------------------------------------------------
// @Function:	 DirectSurface()
// @Purpose: DirectSurface���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSurface::DirectSurface()
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = NULL;			//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Surface = NULL;			//IDirect3DSurface9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9BackSurface = NULL;		//IDirect3DSurface9�ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 ~DirectSurface()
// @Purpose: DirectSurface��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSurface::~DirectSurface()
{
	SAFE_RELEASE(m_pD3D9Surface);		//IDirect3DSurface9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9BackSurface);	//IDirect3DSurface9�ӿ�ָ���ͷ�

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 DirectSurface(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectSurface���캯��
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//D3D9�豸
// @Return: None
//------------------------------------------------------------------
DirectSurface::DirectSurface(IDirect3DDevice9* pD3D9Device)
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = pD3D9Device;	//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Surface = NULL;			//IDirect3DSurface9�ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 DirectSurfaceGetDevice(void)
// @Purpose: DirectSurface��ȡD3D9�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DDevice9* WINAPI DirectSurface::DirectSurfaceGetDevice(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectSurfaceGetSurface(void)
// @Purpose: DirectSurface��ȡD3D9����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DSurface9* WINAPI DirectSurface::DirectSurfaceGetSurface(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Surface;
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceSetDevice(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectSurface����D3D9�豸
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//D3D9�豸
// @Return: None
//-----------------------------------------------------------------------
void WINAPI DirectSurface::DirectSurfaceSetDevice(IDirect3DDevice9* pD3D9Device)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device = pD3D9Device;
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceSetSurface(IDirect3DSurface9* pD3D9Surface)
// @Purpose: DirectSurface����D3D9����
// @Since: v1.00a
// @Para: IDirect3DSurface9* pD3D9Surface	//D3D9����
// @Return: None
//-----------------------------------------------------------------------
void WINAPI DirectSurface::DirectSurfaceSetSurface(IDirect3DSurface9* pD3D9Surface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Surface = pD3D9Surface;
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceInit(void)
// @Purpose: DirectSurface��ʼ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
HRESULT WINAPI DirectSurface::DirectSurfaceInit(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DSURFACE_DESC Desc;

	VERIFY(m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &m_pD3D9BackSurface));												//��ȡ��̨�������
	VERIFY(m_pD3D9BackSurface->GetDesc(&Desc));																									//��ȡDesc
	VERIFY(m_pD3D9Device->CreateOffscreenPlainSurface(Desc.Width, Desc.Height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pD3D9Surface, NULL));		//������������

	return S_OK;
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceLoadSurface(LPWSTR lpszSurface)
// @Purpose: DirectSurface��������
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//����·��
// @Return: None
//-----------------------------------------------------------------------
HRESULT WINAPI DirectSurface::DirectSurfaceLoadSurface(LPWSTR lpszSurface, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromFile(m_pD3D9Surface, NULL, pDestRect, lpszSurface, pSrcRect, D3DX_FILTER_NONE, NULL, NULL));

	return S_OK;
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceLoadSurface(LPWSTR lpszSurface)
// @Purpose: DirectSurface��������
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//����·��
// @Return: None
//-----------------------------------------------------------------------
HRESULT WINAPI DirectSurface::DirectSurfaceLoadSurface(IDirect3DSurface9* pSurface, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromSurface(m_pD3D9Surface, NULL, pDestRect, pSurface, NULL, pSrcRect, D3DX_FILTER_NONE, NULL));

	return S_OK;
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceLoadSurface(LPWSTR lpszSurface)
// @Purpose: DirectSurface��������
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//����·��
// @Return: None
//-----------------------------------------------------------------------
HRESULT WINAPI DirectSurface::DirectSurfaceLoadSurface(LPCVOID lpcszArray, UINT nArraySize, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromFileInMemory(m_pD3D9Surface, NULL, pDestRect, lpcszArray, nArraySize, pSrcRect, D3DX_FILTER_NONE, NULL, NULL));

	return S_OK;
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceLoadSurface(LPWSTR lpszSurface)
// @Purpose: DirectSurface��������
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//����·��
// @Return: None
//-----------------------------------------------------------------------
HRESULT WINAPI DirectSurface::DirectSurfaceLoadSurface(LPCVOID lpcszArray, D3DFORMAT Format, UINT nPitch, const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	if (!m_pD3D9Surface) return E_FAIL;

	VERIFY(D3DXLoadSurfaceFromMemory(m_pD3D9Surface, NULL, pDestRect, lpcszArray, Format, nPitch, NULL, pSrcRect, D3DX_FILTER_NONE, NULL));

	return S_OK;
}

//-------------------------------------------------------------------------------
// @Function:	 DirectSurfaceRender(const RECT* pDestRect, const RECT* pSrcRect)
// @Purpose: DirectSurface��Ⱦ
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//����·��
// @Return: None
//-------------------------------------------------------------------------------
void WINAPI DirectSurface::DirectSurfaceRender(const RECT* pDestRect, const RECT* pSrcRect)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->StretchRect(m_pD3D9Surface, pDestRect, m_pD3D9BackSurface, pSrcRect, D3DTEXF_NONE);
}

//-----------------------------------------------------------------------
// @Function:	 DirectSurfaceRender(DWORD dwColor)
// @Purpose: DirectSurface��Ⱦ
// @Since: v1.00a
// @Para: LPWSTR lpszSurface	//����·��
// @Return: None
//-----------------------------------------------------------------------
void WINAPI DirectSurface::DirectSurfaceRender(DWORD dwColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DSURFACE_DESC Desc;
	D3DLOCKED_RECT Rect;

	m_pD3D9Surface->GetDesc(&Desc);
	m_pD3D9Surface->LockRect(&Rect, 0, 0);

	DWORD* Data = (DWORD*)Rect.pBits;

	for (UINT i = 0; i < Desc.Height; ++i)
	{
		for (UINT j = 0; j < Desc.Width; ++j)
		{
			int index = i * Rect.Pitch / 4 + j;
			Data[index] = dwColor;
		}
	}

	m_pD3D9Surface->UnlockRect();
	m_pD3D9Device->StretchRect(m_pD3D9Surface, NULL, m_pD3D9BackSurface, NULL, D3DTEXF_NONE);
}