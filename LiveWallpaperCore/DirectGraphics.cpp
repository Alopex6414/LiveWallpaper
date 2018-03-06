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
// @Purpose: DirectGraphics构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics::DirectGraphics()
{
	m_bThreadSafe = true;									//线程安全
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//初始化临界区

	m_pD3D9 = NULL;			//IDirect3D9接口指针初始化(NULL)
	m_pD3D9Device = NULL;	//IDirect3DDevice9接口指针初始化(NULL)
	m_pD3DXFont = NULL;		//ID3DXFont接口指针初始化(NULL)
	ZeroMemory(&m_D3D9Caps, sizeof(m_D3D9Caps));	//清空m_D3D9Caps内存区域
	ZeroMemory(&m_D3D9pp, sizeof(m_D3D9pp));		//清空m_D3D9pp内存区域
	ZeroMemory(m_wcD3D9AdapterType, sizeof(wchar_t)*ADAPTERTYPESIZE);	//清空m_wcD3D9AdapterType内存区域
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics()
// @Purpose: DirectGraphics析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics::~DirectGraphics()
{
	SAFE_RELEASE(m_pD3DXFont);		//ID3DXFont接口释放
	SAFE_RELEASE(m_pD3D9Device);	//IDirect3D9接口指针释放
	SAFE_RELEASE(m_pD3D9);			//IDirect3DDevice9接口指针释放

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//删除临界区
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetObject(void) const
// @Purpose: DirectGraphics读取D3D9对象
// @Since: v1.00a
// @Para: None
// @Return: IDirect3D9*(D3D9对象指针)
//------------------------------------------------------------------
IDirect3D9* WINAPI DirectGraphics::DirectGraphicsGetObject(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetDevice(void) const
// @Purpose: DirectGraphics读取D3D9设备对象
// @Since: v1.00a
// @Para: None
// @Return: IDirect3DDevice9*(D3D9设备对象指针)
//------------------------------------------------------------------
IDirect3DDevice9* WINAPI DirectGraphics::DirectGraphicsGetDevice(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetCaps(void) const
// @Purpose: DirectGraphics读取D3D9设备型号
// @Since: v1.00a
// @Para: None
// @Return: D3DCAPS9*(D3D9设备型号指针)
//------------------------------------------------------------------
const D3DCAPS9* WINAPI DirectGraphics::DirectGraphicsGetCaps(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (&m_D3D9Caps);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetPresentParameters(void) const
// @Purpose: DirectGraphics读取D3D9设备参数
// @Since: v1.00a
// @Para: None
// @Return: D3DPRESENT_PARAMETERS*(D3D9设备参数指针)
//------------------------------------------------------------------
const D3DPRESENT_PARAMETERS* WINAPI DirectGraphics::DirectGraphicsGetPresentParameters(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (&m_D3D9pp);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsAdapterType(void) const
// @Purpose: DirectGraphics读取D3D9 GPU型号
// @Since: v1.00a
// @Para: None
// @Return: wchar_t*(宽字符数组地址)
//------------------------------------------------------------------
const wchar_t* WINAPI DirectGraphics::DirectGraphicsAdapterType(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_wcD3D9AdapterType;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetFont(void) const
// @Purpose: DirectGraphics读取D3D9 GPU字体
// @Since: v1.00a
// @Para: None
// @Return: ID3DXFont*(ID3DXFont类型指针)
//------------------------------------------------------------------
const ID3DXFont* WINAPI DirectGraphics::DirectGraphicsGetFont(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3DXFont;
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsTestCooperativeLevel(void) const
// @Purpose: DirectGraphics读取D3D9 当前状态
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(当前状态:正常:S_OK,错误:E_FAIL)
//			D3DERR_DEVICELOST:设备丢失(无法Reset)
//			D3DERR_DEVICENOTRESET:设备未Reset(可以Reset)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsTestCooperativeLevel(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->TestCooperativeLevel());
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsResetDevice(void) const
// @Purpose: DirectGraphics重置D3D9 初始设置
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(当前状态:正常:S_OK,错误:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsResetDevice(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->Reset(&m_D3D9pp));
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsGetBackBuffer(IDirect3DSurface9* pD3D9BackBuffer)
// @Purpose: DirectGraphics获取D3D9 表面
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(当前状态:正常:S_OK,错误:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsGetBackBuffer(IDirect3DSurface9**& ppD3D9BackBuffer)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, ppD3D9BackBuffer));
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsReset(void)
// @Purpose: DirectGraphics 重置
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(重置状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsReset(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return (m_pD3DXFont ? m_pD3DXFont->OnLostDevice() : S_OK);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9**& ppD3D9Surface)
// @Purpose: DirectGraphics 重置
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(状态:成功:S_OK,失败:E_FAIL)
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsCreateOffscreenPlainSurface(UINT nWidth, UINT nHeight, D3DFORMAT D3DFormat, D3DPOOL D3DPool, IDirect3DSurface9**& ppD3D9Surface)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device->CreateOffscreenPlainSurface(nWidth, nHeight, D3DFormat, D3DPool, ppD3D9Surface, NULL);
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd)
// @Purpose: DirectGraphics 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(HWND hWnd)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//读取Direct3D9接口对象指针
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//创建Direct3D9接口对象

	//读取D3DCAPS9校验硬件顶点运算
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//校验硬件顶点运算能力

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//支持硬件顶点运算(硬件顶点运算)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//不支持硬件顶点运算(软件顶点运算)
	}

	//填充D3DPRESENT_PARAMETERS结构
	m_D3D9pp.BackBufferWidth = USER_SCREENWIDTH;//后台缓冲表面宽度(Pixel)
	m_D3D9pp.BackBufferHeight = USER_SCREENHEIGHT;//后台缓冲表面高度(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//后台缓冲像素格式
	m_D3D9pp.BackBufferCount = 1;//后台缓冲数量(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//后台缓冲多重采样类型
	m_D3D9pp.MultiSampleQuality = 0;//后台缓冲多重采样质量
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//交换链页面置换方式
	m_D3D9pp.hDeviceWindow = hWnd;//设备相关窗口句柄
	m_D3D9pp.Windowed = true;//窗口模式:true/全屏模式:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D自动创建维护深度缓冲和模板缓冲
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//深度缓冲和模板缓冲像素格式
	m_D3D9pp.Flags = 0;//无标记格式
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3D默认刷新频率
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D提交频率(默认提交)

	//创建IDirect3DDevice9接口对象指针
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//创建IDirect3DDevice9接口对象指针

	//读取GPU型号
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//读取GPU信息
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}

//------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd, bool bIsWindowed)
// @Purpose: DirectGraphics 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: bool bIsWindowed(是否以窗口模式运行)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(HWND hWnd, bool bIsWindowed)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//读取Direct3D9接口对象指针
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//创建Direct3D9接口对象

	//读取D3DCAPS9校验硬件顶点运算
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//校验硬件顶点运算能力

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//支持硬件顶点运算(硬件顶点运算)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//不支持硬件顶点运算(软件顶点运算)
	}

	//填充D3DPRESENT_PARAMETERS结构
	m_D3D9pp.BackBufferWidth = USER_SCREENWIDTH;//后台缓冲表面宽度(Pixel)
	m_D3D9pp.BackBufferHeight = USER_SCREENHEIGHT;//后台缓冲表面高度(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//后台缓冲像素格式
	m_D3D9pp.BackBufferCount = 1;//后台缓冲数量(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//后台缓冲多重采样类型
	m_D3D9pp.MultiSampleQuality = 0;//后台缓冲多重采样质量
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//交换链页面置换方式
	m_D3D9pp.hDeviceWindow = hWnd;//设备相关窗口句柄
	m_D3D9pp.Windowed = bIsWindowed;//窗口模式:true/全屏模式:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D自动创建维护深度缓冲和模板缓冲
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//深度缓冲和模板缓冲像素格式
	m_D3D9pp.Flags = 0;//无标记格式
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3D默认刷新频率
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D提交频率(默认提交)

	//创建IDirect3DDevice9接口对象指针
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//创建IDirect3DDevice9接口对象指针

	//读取GPU型号
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//读取GPU信息
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight)
// @Purpose: DirectGraphics 初始化
// @Since: v1.00a
// @Para: HWND hWnd(窗口句柄)
// @Para: bool bIsWindowed(是否以窗口模式运行)
// @Para: int nScreenWidth(屏幕宽度)
// @Para: int nScreenHeight(屏幕高度)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(HWND hWnd, bool bIsWindowed, int nScreenWidth, int nScreenHeight)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//读取Direct3D9接口对象指针
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//创建Direct3D9接口对象

	//读取D3DCAPS9校验硬件顶点运算
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//校验硬件顶点运算能力

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//支持硬件顶点运算(硬件顶点运算)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//不支持硬件顶点运算(软件顶点运算)
	}

	//填充D3DPRESENT_PARAMETERS结构
	m_D3D9pp.BackBufferWidth = nScreenWidth;//后台缓冲表面宽度(Pixel)
	m_D3D9pp.BackBufferHeight = nScreenHeight;//后台缓冲表面高度(Pixel)
	m_D3D9pp.BackBufferFormat = D3DFMT_A8R8G8B8;//后台缓冲像素格式
	m_D3D9pp.BackBufferCount = 1;//后台缓冲数量(1)
	m_D3D9pp.MultiSampleType = D3DMULTISAMPLE_NONE;//后台缓冲多重采样类型
	m_D3D9pp.MultiSampleQuality = 0;//后台缓冲多重采样质量
	m_D3D9pp.SwapEffect = D3DSWAPEFFECT_DISCARD;//交换链页面置换方式
	m_D3D9pp.hDeviceWindow = hWnd;//设备相关窗口句柄
	m_D3D9pp.Windowed = bIsWindowed;//窗口模式:true/全屏模式:false
	m_D3D9pp.EnableAutoDepthStencil = true;//Direct3D自动创建维护深度缓冲和模板缓冲
	m_D3D9pp.AutoDepthStencilFormat = D3DFMT_D24S8;//深度缓冲和模板缓冲像素格式
	m_D3D9pp.Flags = 0;//无标记格式
	m_D3D9pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//Direct3D默认刷新频率
	m_D3D9pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//Direct3D提交频率(默认提交)

	//创建IDirect3DDevice9接口对象指针
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, Vp, &m_D3D9pp, &m_pD3D9Device));//创建IDirect3DDevice9接口对象指针

	//读取GPU型号
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//读取GPU信息
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp)
// @Purpose: DirectGraphics 初始化
// @Since: v1.00a
// @Para: D3DPRESENT_PARAMETERS D3D9pp(D3D9参数)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsInit(D3DPRESENT_PARAMETERS D3D9pp)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	int nSize;
	int Vp;
	D3DADAPTER_IDENTIFIER9 D3D9Adapter;

	//读取Direct3D9接口对象指针
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);//创建Direct3D9接口对象

	//读取D3DCAPS9校验硬件顶点运算
	VERIFY(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3D9Caps));//校验硬件顶点运算能力

	if (m_D3D9Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		Vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;//支持硬件顶点运算(硬件顶点运算)
	}
	else
	{
		Vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;//不支持硬件顶点运算(软件顶点运算)
	}

	//填充D3DPRESENT_PARAMETERS结构
	m_D3D9pp.BackBufferWidth = D3D9pp.BackBufferWidth;//后台缓冲表面宽度(Pixel)
	m_D3D9pp.BackBufferHeight = D3D9pp.BackBufferHeight;//后台缓冲表面高度(Pixel)
	m_D3D9pp.BackBufferFormat = D3D9pp.BackBufferFormat;//后台缓冲像素格式
	m_D3D9pp.BackBufferCount = D3D9pp.BackBufferCount;//后台缓冲数量(1)
	m_D3D9pp.MultiSampleType = D3D9pp.MultiSampleType;//后台缓冲多重采样类型
	m_D3D9pp.MultiSampleQuality = D3D9pp.MultiSampleQuality;//后台缓冲多重采样质量
	m_D3D9pp.SwapEffect = D3D9pp.SwapEffect;//交换链页面置换方式
	m_D3D9pp.hDeviceWindow = D3D9pp.hDeviceWindow;//设备相关窗口句柄
	m_D3D9pp.Windowed = D3D9pp.Windowed;//窗口模式:true/全屏模式:false
	m_D3D9pp.EnableAutoDepthStencil = D3D9pp.EnableAutoDepthStencil;//Direct3D自动创建维护深度缓冲和模板缓冲
	m_D3D9pp.AutoDepthStencilFormat = D3D9pp.AutoDepthStencilFormat;//深度缓冲和模板缓冲像素格式
	m_D3D9pp.Flags = D3D9pp.Flags;//无标记格式
	m_D3D9pp.FullScreen_RefreshRateInHz = D3D9pp.FullScreen_RefreshRateInHz;//Direct3D默认刷新频率
	m_D3D9pp.PresentationInterval = D3D9pp.PresentationInterval;//Direct3D提交频率(默认提交)

	//创建IDirect3DDevice9接口对象指针
	VERIFY(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3D9pp.hDeviceWindow, Vp, &m_D3D9pp, &m_pD3D9Device));//创建IDirect3DDevice9接口对象指针

	//读取GPU型号
	m_pD3D9->GetAdapterIdentifier(0, 0, &D3D9Adapter);	//读取GPU信息
	nSize = MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, D3D9Adapter.Description, -1, m_wcD3D9AdapterType, nSize);

	return S_OK;//OK
}
//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsBeginScene(void)
// @Purpose: DirectGraphics 开始渲染
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsBeginScene(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->BeginScene());	//开始渲染
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsEndScene(void)
// @Purpose: DirectGraphics 结束渲染
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsEndScene(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->EndScene());		//结束渲染
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsBegin(void)
// @Purpose: DirectGraphics 开始渲染
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsBegin(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));		//清空图像
	VERIFY(m_pD3D9Device->BeginScene());	//开始渲染
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsEnd(void)
// @Purpose: DirectGraphics 结束渲染
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsEnd(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->EndScene());		//结束渲染
	VERIFY(m_pD3D9Device->Present(NULL, NULL, NULL, NULL));		//提交渲染(显示)
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsPresent(void)
// @Purpose: DirectGraphics 提交渲染(显示)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsPresent(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Present(NULL,NULL,NULL,NULL));		//提交渲染(显示)
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsClear(void)
// @Purpose: DirectGraphics 清空图像
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsClear(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));		//清空图像
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsClear(DWORD dwColor)
// @Purpose: DirectGraphics 清空图像
// @Since: v1.00a
// @Para: DWORD dwColor(背景颜色)
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsClear(DWORD dwColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pD3D9Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, dwColor, 1.0f, 0));		//清空图像
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit()
// @Purpose: DirectGraphics 字体初始化
// @Since: v1.01a
// @Para: None
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsFontInit()
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, 20, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(int nFontSize)
// @Purpose: DirectGraphics 字体初始化
// @Since: v1.01a
// @Para: int nFontSize		//字体大小
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsFontInit(int nFontSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, _T("Consolas"), &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType)
// @Purpose: DirectGraphics 字体初始化
// @Since: v1.01a
// @Para: int nFontSize			//字体大小
// @Para: LPWSTR lpszFontType	//字体类型
// @Return: HRESULT(初始化状态:成功:S_OK,失败:E_FAIL)
//---------------------------------------------------------------------------------------------------
HRESULT WINAPI DirectGraphics::DirectGraphicsFontInit(int nFontSize, LPWSTR lpszFontType)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(D3DXCreateFont(m_pD3D9Device, nFontSize, 0, 0, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, lpszFontType, &m_pD3DXFont));
	return S_OK;//OK
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphicsFontDrawText(HWND hWnd)
// @Purpose: DirectGraphics 绘制HAL信息
// @Since: v1.01a
// @Para: HWND hWnd		//窗口句柄
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
// @Purpose: DirectGraphics 绘制HAL信息
// @Since: v1.01a
// @Para: HWND hWnd				//窗口句柄
// @Para: D3DXCOLOR dwColor		//字体颜色
// @Return: None
//---------------------------------------------------------------------------------------------------
void WINAPI DirectGraphics::DirectGraphicsFontDrawText(HWND hWnd, D3DXCOLOR dwColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	RECT Rect;

	GetClientRect(hWnd, &Rect);
	m_pD3DXFont->DrawText(NULL, m_wcD3D9AdapterType, -1, &Rect, DT_TOP | DT_LEFT, dwColor);
}