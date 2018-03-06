/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectFont.cpp
* @brief	This File is DirectFont DLL Project.
* @author	Alopex/Helium
* @version	v1.11a
* @date		2017-12-16	v1.00a	alopex	Create This File.
* @date		2018-1-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.10a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-2-12	v1.11a	alopex	Add Reset Device & Definion of DirectFont Colors.
*/
#include "DirectCommon.h"
#include "DirectFont.h"
#include "DirectThreadSafe.h"

//DirectFont��Ҫ����2D/3D���ֻ���

//------------------------------------------------------------------
// @Function:	 DirectFont()
// @Purpose: DirectFont���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont::DirectFont()
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = NULL;			//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Font = NULL;				//IDirect3DFont9�ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 ~DirectFont()
// @Purpose: DirectFont��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectFont::~DirectFont()
{
	SAFE_RELEASE(m_pD3D9Font);		//IDirect3DFont9�ӿ�ָ���ͷ�

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 DirectFont(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectFont���캯��
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device	//D3D9�����豸
// @Return: None
//------------------------------------------------------------------
DirectFont::DirectFont(IDirect3DDevice9* pD3D9Device)
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = pD3D9Device;	//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Font = NULL;				//IDirect3DFont9�ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 DirectFontGetDevice(void) const
// @Purpose: DirectFont��ȡD3D9�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
IDirect3DDevice9* WINAPI DirectFont::DirectFontGetDevice(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectFontGetFont(void) const
// @Purpose: DirectFont��ȡD3D9����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
ID3DXFont* WINAPI DirectFont::DirectFontGetFont(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Font;
}

//------------------------------------------------------------------
// @Function:	 DirectFontSetDevice(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectFont����D3D9�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectFont::DirectFontSetDevice(IDirect3DDevice9* pD3D9Device)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device = pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectFontSetFont(ID3DXFont* pD3DXFont)
// @Purpose: DirectFont����D3D9����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI DirectFont::DirectFontSetFont(ID3DXFont* pD3DXFont)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Font = pD3DXFont;
}

//------------------------------------------------------------------
// @Function:	 DirectFontReset(void)
// @Purpose: DirectFont����D3D9����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectFont::DirectFontReset(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Font->OnLostDevice();
}

//------------------------------------------------------------------
// @Function:	 DirectFontInit(void)
// @Purpose: DirectFont��ʼ��D3D9����
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectFont::DirectFontInit(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateFont(m_pD3D9Device, 12, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3D9Font));

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectFontInit(int nFontSize)
// @Purpose: DirectFont��ʼ��D3D9����
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectFont::DirectFontInit(int nFontSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3D9Font));

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectFontInit(int nFontSize, LPWSTR lpszFontType)
// @Purpose: DirectFont��ʼ��D3D9����
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//------------------------------------------------------------------
HRESULT WINAPI DirectFont::DirectFontInit(int nFontSize, LPWSTR lpszFontType)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, lpszFontType, &m_pD3D9Font));
	
	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectFontDrawText(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectFont��������
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectFont::DirectFontDrawText(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3D9Font->DrawText(NULL, lpcszStr, -1, &Rect, Format, Color);
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectFontDrawTextA(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectFont��������
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPSTR lpszFontType
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectFont::DirectFontDrawTextA(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3D9Font->DrawTextA(NULL, lpcszStr, -1, &Rect, Format, Color);
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectFontDrawTextW(HWND hWnd, LPCSTR lpcszStr, DWORD Format, D3DCOLOR Color)
// @Purpose: DirectFont��������
// @Since: v1.00a
// @Para: int nFontSize
// @Para: LPWSTR lpszFontType
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectFont::DirectFontDrawTextW(HWND hWnd, LPCWSTR lpcszStr, DWORD Format, D3DCOLOR Color)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3D9Font->DrawTextW(NULL, lpcszStr, -1, &Rect, Format, Color);
}