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

#include "LiveUI.h"

//WinUtilities��Ҫ����Win32������Ŀע�ᴰ�ڡ���ʼ������Ϣ����...
//Variable
HWND g_hWnd;					//���ھ��
HINSTANCE g_hInstance;			//����ʵ�����

//------------------------------------------------------------------
// @Function:	 MyRegisterClass(HINSTANCE hInstance)
// @Purpose: Win32ע�ᴰ����
// @Since: v1.00a
// @Para: HINSTANCE hInstance	//����ʵ�����
// @Para: WndPara* lpsWndPara	//���ڳ�ʼ������
// @Return: ATOM(DWORD)			//������ṹ��
//------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance, WndPara* lpsWndPara)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);//WNDCLASSEX���С
	wcex.style = CS_HREDRAW | CS_VREDRAW;//��������ʽ
	wcex.lpfnWndProc = WndProc;//������ص�����
	wcex.cbClsExtra = 0;//������ṹ�����ֽ���
	wcex.cbWndExtra = 0;//����ʵ�������ֽ���
	wcex.hInstance = hInstance;//���ھ��
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(lpsWndPara->wIcon));//ͼ����
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);//�����
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//������ˢ��ɫ(�Զ�)
	wcex.lpszMenuName = MAKEINTRESOURCE(lpsWndPara->wIcon);//�˵�ָ��
	wcex.lpszClassName = L"WinClass";//����ָ��
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(lpsWndPara->wIcon));//Сͼ����

	return RegisterClassEx(&wcex);
}

//------------------------------------------------------------------
// @Function:	 InitWndInstance(HINSTANCE hInstance, int nCmdShow)
// @Purpose: Win32��ʼ������ʵ�����
// @Since: v1.00a
// @Para: HINSTANCE hInstance	//����ʵ�����
// @Para: int nCmdShow			//�����д���
// @Para: WndPara* lpsWndPara	//���ڳ�ʼ������
// @Para: pCallBackInitWndExtra	//���ڳ�ʼ���ص�����
// @Return: BOOL				//����ʵ�������ʼ��״̬
//------------------------------------------------------------------
BOOL InitWndInstance(HINSTANCE hInstance, int nCmdShow, WndPara* lpsWndPara, LPCALLBACKINITWNDEXTRAFUNC pCallBackInitWndExtra)
{
	HWND hWnd;//���ھ��
	WINDOWINFO WindowInfo;//������Ϣ
	RECT Rect;//���ھ�������
	int nPosX = 0;//���ڳ�ʼ����X
	int nPosY = 0;//���ڳ�ʼ����Y
	int nWindowWidth = 0;//���ڿ��
	int nWindowHeight = 0;//���ڸ߶�
	int nScreenWidth = 0;//��Ļ���
	int nScreenHeight = 0;//��Ļ�߶�

	SetRect(&Rect, 0, 0, lpsWndPara->nWndWidth, lpsWndPara->nWndHeight);//���ô����������
	AdjustWindowRect(&Rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false);//���ھ��б��������˵�������С������

	hWnd = CreateWindow(L"WinClass", lpsWndPara->lpszTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, 0, (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hInstance, NULL);//��ʼ������
	if (!hWnd)
	{
		return FALSE;//��ʼ������ʧ��(Exit)
	}

	g_hWnd = hWnd;//�洢���ھ��
	g_hInstance = hInstance;//�洢����ʵ�����

	GetWindowInfo(hWnd, &WindowInfo);//��ȡ������Ϣ
	nWindowWidth = Rect.right - Rect.left;//���㴰�ڿ��
	nWindowHeight = Rect.bottom - Rect.top;//���㴰�ڸ߶�
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);//��ȡ��Ļ���
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);//��ȡ��Ļ�߶�

	if (nScreenWidth > nWindowWidth && nScreenHeight > nWindowHeight)
	{
		nPosX = (nScreenWidth - nWindowWidth) >> 1;//���ڳ�ʼX����
		nPosY = (nScreenHeight - nWindowHeight) >> 1;//���ڳ�ʼY����
		SetWindowPos(hWnd, HWND_TOP, nPosX, nPosY, 0, 0, SWP_NOSIZE);//���ô���λ��(ScreenCenter)
	}

	if (pCallBackInitWndExtra != NULL)//������������ΪNULL
	{
		if (!(*pCallBackInitWndExtra)())//���ڶ����ʼ������
		{
			return FALSE;//��ʼ������ʧ��(Exit) 
		}
	}

	ShowWindow(hWnd, nCmdShow);//��ʾ����
	UpdateWindow(hWnd);//ˢ�´���

	return TRUE;//��ʼ�����ڳɹ�OK
}

//-----------------------------------------------------------------------------
// @Function:	 WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// @Purpose: Win32��ʼ������ʵ�����
// @Since: v1.00a
// @Para: HWND hWnd				//���ھ��
// @Para: UINT message			//������Ϣ
// @Para: WPARAM wParam			//���ڲ���
// @Para: LPARAM lParam			//���ڲ���
// @Return: LRESULT				//����״̬
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);//�ؼ�ID
		wmEvent = HIWORD(wParam);//֪ͨ��
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
		return g_cLiveUI.OnTimer(wParam, lParam);
	case WM_CLOSE:
		return g_cLiveUI.OnClose(wParam, lParam);
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
// @Purpose: Win32��ʼ������WinMain����
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

	UNREFERENCED_PARAMETER(hPrevInstance);//��������������hPrevInstance����
	UNREFERENCED_PARAMETER(lpCmdLine);//��������������lpCmdLine����

	lpWndPara = (*pCallBackSetWndPara)();//��ȡWinMain���ڲ�������
	MyRegisterClass(hInstance, lpWndPara);//ע�ᴰ����
	bState = InitWndInstance(hInstance, nCmdShow, lpWndPara, pCallBackInitWndExtra);//��ʼ������ʵ�����
	if (!bState) return E_FAIL;//FAIL

	return S_OK;//OK
}

//-------------------------------------------------------------------------------------------------------
// @Function:	 WinMainLoop(void)
// @Purpose: Win32����WinMain��ѭ������
// @Since: v1.00a
// @Para: LPCALLBACKDIRECT3DRENDERFUNC pCallBackDirect3DRender
// @Para: LPCALLBACKRELEASEWNDEXTRAFUNC pCallBackReleaseWndExtra
// @Return: None
//-------------------------------------------------------------------------------------------------------
int WinMainLoop(LPCALLBACKRELEASEWNDEXTRAFUNC pCallBackReleaseWndExtra)
{
	MSG msg;

	ZeroMemory(&msg, sizeof(msg));//�����Ϣ��Ϣ

	while (GetMessage(&msg, NULL, 0, 0))//����Ϣѭ��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (pCallBackReleaseWndExtra != NULL)
	{
		(*pCallBackReleaseWndExtra)();//�ͷ���Դ
	}

	return (int)msg.wParam;
}