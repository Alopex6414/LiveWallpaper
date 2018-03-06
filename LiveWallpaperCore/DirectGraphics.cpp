/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics.cpp
* @brief	This Program is DirectGraphics DLL Project.
* @author	Alopex/Helium
* @version	v1.21a
* @date		2017-11-2	v1.00a	alopex	Create Project.
* @date		2017-12-2	v1.01a	alopex	Add D3DXFont.
* @date		2017-12-8	v1.11a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-2	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-2-11	v1.22a	alopex	Add D3D9 Lost Device Function.
*/
#include "DirectCommon.h"
#include "DirectGraphics.h"
#include "DirectThreadSafe.h"

//------------------------------------------------------------------
// @Function:	 DirectGraphics()
// @Purpose: DirectGraphics���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics::DirectGraphics()
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9 = NULL;			//IDirect3D9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Device = NULL;	//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3DXFont = NULL;		//ID3DXFont�ӿ�ָ���ʼ��(NULL)
	ZeroMemory(&m_D3D9Caps, sizeof(m_D3D9Caps));	//���m_D3D9Caps�ڴ�����
	ZeroMemory(&m_D3D9pp, sizeof(m_D3D9pp));		//���m_D3D9pp�ڴ�����
	ZeroMemory(m_wcD3D9AdapterType, sizeof(wchar_t)*ADAPTERTYPESIZE);	//���m_wcD3D9AdapterType�ڴ�����
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics()
// @Purpose: DirectGraphics��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics::~DirectGraphics()
{
	SAFE_RELEASE(m_pD3DXFont);		//ID3DXFont�ӿ��ͷ�
	SAFE_RELEASE(m_pD3D9Device);	//IDirect3D9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9);			//IDirect3DDevice9�ӿ�ָ���ͷ�

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetObject(void) const
// @Purpose: DirectGraphics��ȡD3D9����
// @Since: v1.00a
// @Para: None
// @Return: IDirect3D9*(D3D9����ָ��)
//------------------------------------------------------------------
IDirect3D9* WINAPI DirectGraphics::DirectGraphicsGetObject(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetDevice(void) const
// @Purpose: DirectGraphics��ȡD3D9�豸����
// @Since: v1.00a
// @Para: None
// @Return: IDirect3DDevice9*(D3D9�豸����ָ��)
//------------------------------------------------------------------
IDirect3DDevice9* WINAPI DirectGraphics::DirectGraphicsGetDevice(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetCaps(void) const
// @Purpose: DirectGraphics��ȡD3D9�豸�ͺ�
// @Since: v1.00a
// @Para: None
// @Return: D3DCAPS9*(D3D9�豸�ͺ�ָ��)
//------------------------------------------------------------------
const D3DCAPS9* WINAPI DirectGraphics::DirectGraphicsGetCaps(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (&m_D3D9Caps);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetPresentParameters(void) const
// @Purpose: DirectGraphics��ȡD3D9�豸����
// @Since: v1.00a
// @Para: None
// @Return: D3DPRESENT_PARAMETERS*(D3D9�豸����ָ��)
//------------------------------------------------------------------
const D3DPRESENT_PARAMETERS* WINAPI DirectGraphics::DirectGraphicsGetPresentParameters(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (&m_D3D9pp);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsAdapterType(void) const
// @Purpose: DirectGraphics��ȡD3D9 GPU�ͺ�
// @Since: v1.00a
// @Para: None
// @Return: wchar_t*(���ַ������ַ)
//------------------------------------------------------------------
const wchar_t* WINAPI DirectGraphics::DirectGraphicsAdapterType(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_wcD3D9AdapterType;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetFont(void) const
// @Purpose: DirectGraphics��ȡD3D9 GPU����
// @Since: v1.00a
// @Para: None
// @Return: ID3DXFont*(ID3DXFont����ָ��)
//------------------------------------------------------------------
const ID3DXFont* WINAPI DirectGraphics::DirectGraphicsGetFont(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXFont;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsTestCooperativeLevel(void) const
// @Purpose: DirectGraphics��ȡD3D9 ��ǰ״̬
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ǰ״̬:����:S_OK,����:E_FAIL)
//			D3DERR_DEVICELOST:�豸��ʧ(�޷�Reset)
//			D3DERR_DEVICENOTRESET:�豸δReset(����Reset)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsTestCooperativeLevel(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->TestCooperativeLevel());
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsResetDevice(void) const
// @Purpose: DirectGraphics����D3D9 ��ʼ����
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ǰ״̬:����:S_OK,����:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsResetDevice(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->Reset(&m_D3D9pp));
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetBackBuffer(IDirect3DSurface9* pD3D9BackBuffer)
// @Purpose: DirectGraphics��ȡD3D9 ����
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ǰ״̬:����:S_OK,����:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsGetBackBuffer(IDirect3DSurface9**& ppD3D9BackBuffer)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, ppD3D9BackBuffer));
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsReset(void)
// @Purpose: DirectGraphics ����
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(����״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsReset(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3DXFont ? m_pD3DXFont->OnLostDevice() : S_OK);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9**& ppD3D9Surface)
// @Purpose: DirectGraphics ����
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9**& ppD3D9Surface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->CreateOffscreenPlainSurface(nWidth, nHeight, D3DFormat, D3DPool, ppD3D9Surface, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = USER_SCREENWIDTH;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = USER_SCREENHEIGHT;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = 1;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = 0;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = hWnd;//�豸��ش��ھ��
	m_D3D9pp.Windowed = true;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = 0;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd, bool bIsWindowed)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: bool bIsWindowed(�Ƿ��Դ���ģʽ����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(HWND hWnd, bool bIsWindowed)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = USER_SCREENWIDTH;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = USER_SCREENHEIGHT;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = 1;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = 0;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = hWnd;//�豸��ش��ھ��
	m_D3D9pp.Windowed = bIsWindowed;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = 0;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: HWND hWnd(���ھ��)
// @Para: bool bIsWindowed(�Ƿ��Դ���ģʽ����)
// @Para: int nScreenWidth(��Ļ���)
// @Para: int nScreenHeight(��Ļ�߶�)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = nScreenWidth;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = nScreenHeight;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = 1;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = 0;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = hWnd;//�豸��ش��ھ��
	m_D3D9pp.Windowed = bIsWindowed;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = 0;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp)
// @Purpose: DirectGraphics ��ʼ��
// @Since: v1.00a
// @Para: D3DPRESENT_PARAMETERS D3D9pp(D3D9����)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//��ȡDirect3D9�ӿڶ���ָ��
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//����Direct3D9�ӿڶ���

	//��ȡD3DCAPS9У��Ӳ����������
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//У��Ӳ��������������

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//֧��Ӳ����������(Ӳ����������)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//��֧��Ӳ����������(�����������)
	}

	//���D3DPRESENT_PARAMETERS�ṹ
	m_D3D9pp.BackBufferWidth = D3D9pp.BackBufferWidth;//��̨���������(Pixel)
	m_D3D9pp.BackBufferHeight = D3D9pp.BackBufferHeight;//��̨�������߶�(Pixel)
	m_D3D9pp.BackBufferFormat = D3D9pp.BackBufferFormat;//��̨�������ظ�ʽ
	m_D3D9pp.BackBufferCount = D3D9pp.BackBufferCount;//��̨��������(1)
	m_D3D9pp.MultiSampleType = D3D9pp.MultiSampleType;//��̨������ز�������
	m_D3D9pp.MultiSampleQuality = D3D9pp.MultiSampleQuality;//��̨������ز�������
	m_D3D9pp.SwapEffect = D3D9pp.SwapEffect;//������ҳ���û���ʽ
	m_D3D9pp.hDeviceWindow = D3D9pp.hDeviceWindow;//�豸��ش��ھ��
	m_D3D9pp.Windowed = D3D9pp.Windowed;//����ģʽ:true/ȫ��ģʽ:false
	m_D3D9pp.EnableAutoDepthStencil = D3D9pp.EnableAutoDepthStencil;//Direct3D�Զ�����ά����Ȼ����ģ�建��
	m_D3D9pp.AutoDepthStencilFormat = D3D9pp.AutoDepthStencilFormat;//��Ȼ����ģ�建�����ظ�ʽ
	m_D3D9pp.Flags = D3D9pp.Flags;//�ޱ�Ǹ�ʽ
	m_D3D9pp.FullScreen_RefreshRateInHz = D3D9pp.FullScreen_RefreshRateInHz;//Direct3DĬ��ˢ��Ƶ��
	m_D3D9pp.PresentationInterval = D3D9pp.PresentationInterval;//Direct3D�ύƵ��(Ĭ���ύ)

	//����IDirect3DDevice9�ӿڶ���ָ��
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3D9pp.hDeviceWindow, Vp, &m_D3D9pp, &m_pD3D9Device));//����IDirect3DDevice9�ӿڶ���ָ��

	//��ȡGPU�ͺ�
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//��ȡGPU��Ϣ
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}
//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsBeginScene(void)
// @Purpose: DirectGraphics ��ʼ��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsBeginScene(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->BeginScene());	//��ʼ��Ⱦ
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsEndScene(void)
// @Purpose: DirectGraphics ������Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsEndScene(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->EndScene());		//������Ⱦ
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsBegin(void)
// @Purpose: DirectGraphics ��ʼ��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsBegin(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));		//���ͼ��
	VERIFY(m_pD3D9Device->BeginScene());	//��ʼ��Ⱦ
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsEnd(void)
// @Purpose: DirectGraphics ������Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsEnd(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->EndScene());		//������Ⱦ
	VERIFY(m_pD3D9Device->Present(NULL, NULL, NULL, NULL));		//�ύ��Ⱦ(��ʾ)
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsPresent(void)
// @Purpose: DirectGraphics �ύ��Ⱦ(��ʾ)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsPresent(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Present(NULL,NULL,NULL,NULL));		//�ύ��Ⱦ(��ʾ)
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsClear(void)
// @Purpose: DirectGraphics ���ͼ��
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsClear(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));		//���ͼ��
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsClear(DWORD dwColor)
// @Purpose: DirectGraphics ���ͼ��
// @Since: v1.00a
// @Para: DWORD dwColor(������ɫ)
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsClear(DWORD dwColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, dwColor, 1.0f, 0));		//���ͼ��
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit()
// @Purpose: DirectGraphics �����ʼ��
// @Since: v1.01a
// @Para: None
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsFontInit()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, 20, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(int nFontSize)
// @Purpose: DirectGraphics �����ʼ��
// @Since: v1.01a
// @Para: int nFontSize		//�����С
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsFontInit(int nFontSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType)
// @Purpose: DirectGraphics �����ʼ��
// @Since: v1.01a
// @Para: int nFontSize			//�����С
// @Para: LPWSTR lpszFontType	//��������
// @Return: HRESULT(��ʼ��״̬:�ɹ�:S_OK,ʧ��:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, lpszFontType, &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontDrawText(HWND hWnd)
// @Purpose: DirectGraphics ����HAL��Ϣ
// @Since: v1.01a
// @Para: HWND hWnd		//���ھ��
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics::DirectGraphicsFontDrawText(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3DXFont->DrawText(NULL, m_wcD3D9AdapterType, -1, &Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontDrawText(D3DXCOLOR dwColor)
// @Purpose: DirectGraphics ����HAL��Ϣ
// @Since: v1.01a
// @Para: HWND hWnd				//���ھ��
// @Para: D3DXCOLOR dwColor		//������ɫ
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics::DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3DXFont->DrawText(NULL, m_wcD3D9AdapterType, -1, &Rect, DT_TOP | DT_LEFT, dwColor);
}