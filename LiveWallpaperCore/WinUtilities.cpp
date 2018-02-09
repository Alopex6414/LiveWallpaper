/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Alopex/Helium
*     All rights reserved.
*
* @file		WinUtilities.cpp
* @brief	This Program is WinUtilities DLL Project.
* @author	Alopex/Helium
* @version	v1.10a
* @date		2017-11-28	v1.00a	alopex	Create Project
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
*/
#include "WinUtilities.h"

//WinUtilities主要用于Win32窗口项目注册窗口、初始化、消息处理...
//Variable
HWND g_hWnd;					//窗口句柄
HINSTANCE g_hInstance;			//窗口实例句柄

//------------------------------------------------------------------
// @Function:	 MyRegisterClass(HINSTANCE hInstance)
// @Purpose: Win32注册窗口类
// @Since: v1.00a
// @Para: HINSTANCE hInstance	//窗口实例句柄
// @Para: WndPara* lpsWndPara	//窗口初始化参数
// @Return: ATOM(DWORD)			//窗口类结构体
//------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance, WndPara* lpsWndPara)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);//WNDCLASSEX类大小
	wcex.style = CS_HREDRAW | CS_VREDRAW;//窗口类样式
	wcex.lpfnWndProc = WndProc;//窗口类回调函数
	wcex.cbClsExtra = 0;//窗口类结构附加字节数
	wcex.cbWndExtra = 0;//窗口实例附加字节数
	wcex.hInstance = hInstance;//窗口句柄
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(lpsWndPara->wIcon));//图标句柄
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);//光标句柄
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//背景画刷颜色(自动)
	wcex.lpszMenuName = MAKEINTRESOURCE(lpsWndPara->wIcon);//菜单指针
	wcex.lpszClassName = L"WinClass";//类名指针
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(lpsWndPara->wIcon));//小图标句柄

	return RegisterClassEx(&wcex);
}

//------------------------------------------------------------------
// @Function:	 InitWndInstance(HINSTANCE hInstance, int nCmdShow)
// @Purpose: Win32初始化窗口实例句柄
// @Since: v1.00a
// @Para: HINSTANCE hInstance	//窗口实例句柄
// @Para: int nCmdShow			//命令行代码
// @Para: WndPara* lpsWndPara	//窗口初始化参数
// @Para: pCallBackInitWndExtra	//窗口初始化回调函数
// @Return: BOOL				//窗口实例句柄初始化状态
//------------------------------------------------------------------
BOOL InitWndInstance(HINSTANCE hInstance, int nCmdShow, WndPara* lpsWndPara, LPCALLBACKINITWNDEXTRAFUNC pCallBackInitWndExtra)
{
	HWND hWnd;//窗口句柄
	WINDOWINFO WindowInfo;//窗口信息
	RECT Rect;//窗口矩形区域
	int nPosX = 0;//窗口初始坐标X
	int nPosY = 0;//窗口初始坐标Y
	int nWindowWidth = 0;//窗口宽度
	int nWindowHeight = 0;//窗口高度
	int nScreenWidth = 0;//屏幕宽度
	int nScreenHeight = 0;//屏幕高度

	SetRect(&Rect, 0, 0, lpsWndPara->nWndWidth, lpsWndPara->nWndHeight);//设置窗口区域矩形
	AdjustWindowRect(&Rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);//窗口具有标题栏、菜单栏、最小化窗口

	hWnd = CreateWindow(L"WinClass", lpsWndPara->lpszTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hInstance, NULL);//初始化窗口
	if (!hWnd)
	{
		return FALSE;//初始化窗口失败(Exit)
	}

	g_hWnd = hWnd;//存储窗口句柄
	g_hInstance = hInstance;//存储窗口实例句柄

	GetWindowInfo(hWnd, &WindowInfo);//获取窗口信息
	nWindowWidth = Rect.right - Rect.left;//计算窗口宽度
	nWindowHeight = Rect.bottom - Rect.top;//计算窗口高度
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);//获取屏幕宽度
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);//获取屏幕高度

	if (nScreenWidth > nWindowWidth && nScreenHeight > nWindowHeight)
	{
		nPosX = (nScreenWidth - nWindowWidth) >> 1;//窗口初始X坐标
		nPosY = (nScreenHeight - nWindowHeight) >> 1;//窗口初始Y坐标
		SetWindowPos(hWnd, HWND_TOP, nPosX, nPosY, 0, 0, SWP_NOSIZE);//设置窗口位置(ScreenCenter)
	}

	if (pCallBackInitWndExtra != NULL)//如果传入参数不为NULL
	{
		if (!(*pCallBackInitWndExtra)())//窗口额外初始化内容
		{
			return FALSE;//初始化窗口失败(Exit) 
		}
	}

	ShowWindow(hWnd, nCmdShow);//显示窗口
	UpdateWindow(hWnd);//刷新窗口

	return TRUE;//初始化窗口成功OK
}

//-----------------------------------------------------------------------------
// @Function:	 WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// @Purpose: Win32初始化窗口实例句柄
// @Since: v1.00a
// @Para: HWND hWnd				//窗口句柄
// @Para: UINT message			//窗口消息
// @Para: WPARAM wParam			//窗口参数
// @Para: LPARAM lParam			//窗口参数
// @Return: LRESULT				//窗口状态
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);//控件ID
		wmEvent = HIWORD(wParam);//通知码
		break;
	case WM_ERASEBKGND:
		break;
	case WM_KEYDOWN:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------------
// @Function:	 InitWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
// @Purpose: Win32初始化窗口WinMain函数
// @Since: v1.00a
// @Para: HINSTANCE hInstance
// @Para: HINSTANCE hPrevInstance
// @Para: LPSTR lpCmdLine
// @Para: int nCmdShow
// @Para: LPCALLBACKSETWNDPARAFUNC pCallBackSetWndPara
// @Para: LPCALLBACKINITWNDEXTRAFUNC pCallBackInitWndExtra
// @Return: HRESULT
//-------------------------------------------------------------------------------------------------------
HRESULT InitWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LPCALLBACKSETWNDPARAFUNC pCallBackSetWndPara, LPCALLBACKINITWNDEXTRAFUNC pCallBackInitWndExtra)
{
	WndPara* lpWndPara = NULL;
	BOOL bState;

	UNREFERENCED_PARAMETER(hPrevInstance);//编译器不检测变量hPrevInstance警告
	UNREFERENCED_PARAMETER(lpCmdLine);//编译器不检测变量lpCmdLine警告

	lpWndPara = (*pCallBackSetWndPara)();//获取WinMain窗口参数设置
	MyRegisterClass(hInstance, lpWndPara);//注册窗口类
	bState = InitWndInstance(hInstance, nCmdShow, lpWndPara, pCallBackInitWndExtra);//初始化窗口实例句柄
	if (!bState) return E_FAIL;//FAIL

	return S_OK;//OK
}

//-------------------------------------------------------------------------------------------------------
// @Function:	 WinMainLoop(void)
// @Purpose: Win32窗口WinMain主循环函数
// @Since: v1.00a
// @Para: LPCALLBACKDIRECT3DRENDERFUNC pCallBackDirect3DRender
// @Para: LPCALLBACKRELEASEWNDEXTRAFUNC pCallBackReleaseWndExtra
// @Return: None
//-------------------------------------------------------------------------------------------------------
int WinMainLoop(LPCALLBACKDIRECT3DRENDERFUNC pCallBackDirect3DRender, LPCALLBACKRELEASEWNDEXTRAFUNC pCallBackReleaseWndExtra)
{
	MSG msg;

	ZeroMemory(&msg, sizeof(msg));//清除消息信息

	while (msg.message != WM_QUIT)//主消息循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			(*pCallBackDirect3DRender)();//Direct3D渲染
		}
	}

	if (pCallBackReleaseWndExtra != NULL)
	{
		(*pCallBackReleaseWndExtra)();//释放资源
	}

	return (int)msg.wParam;
}