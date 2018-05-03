/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreWait.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-05-02
*/
#include "LiveCoreWait.h"

//------------------------------------------------------------------
// @Function:	 CLiveCoreWait()
// @Purpose: CLiveCoreWait构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWait::CLiveCoreWait()
{
	m_hWnd = NULL;
	m_pLiveWaitGraphics = NULL;
	m_pLiveWaitTexture = NULL;
	memset(m_tcTexturePath, 0, MAX_PATH * sizeof(TCHAR));
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreWait()
// @Purpose: CLiveCoreWait析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreWait::~CLiveCoreWait()
{
	SAFE_DELETE(m_pLiveWaitTexture);
	SAFE_DELETE(m_pLiveWaitGraphics);
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWait_Convert_A2W()
// @Purpose: CLiveCoreWait转换小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWait_Convert_A2W(LPCSTR szArr, LPCTSTR wszArr, int nSize)
{
	int nSrcSize = 0;
	wchar_t* pwszArr = NULL;

	nSrcSize = ::MultiByteToWideChar(CP_ACP, 0, szArr, -1, NULL, NULL);
	if (nSize < nSrcSize + 1)
	{
		return FALSE;
	}

	pwszArr = new wchar_t[nSrcSize + 1];
	memset(pwszArr, 0, (nSrcSize + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, szArr, -1, (LPWSTR)pwszArr, nSrcSize);

	memset((void*)wszArr, 0, nSize * sizeof(wchar_t));
	memcpy_s((void*)wszArr, nSize * sizeof(wchar_t), pwszArr, (nSrcSize + 1) * sizeof(wchar_t));

	delete[] pwszArr;
	pwszArr = NULL;

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWait_Texture_GetPath()
// @Purpose: CLiveCoreWait获取纹理路径小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWait_Texture_GetPath(LPCSTR szFile)
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chArr, MAX_PATH);
	pTemp = strrchr(chArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}

	strcat_s(chArr, "\\");
	strcat_s(chArr, szFile);

	BOOL bRet = FALSE;

	memset(m_tcTexturePath, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveCoreWait_Convert_A2W(chArr, m_tcTexturePath, MAX_PATH);
	if (!bRet)
	{
		return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitInit()
// @Purpose: CLiveCoreWait初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitInit()
{
	int nPosX = 0;
	int nPosY = 0;
	int nScreenWidth = 0;
	int nScreenHeight = 0;

	m_hWnd = CreateDialog(g_hInstance, (LPCTSTR)IDD_DIALOG_WAIT, NULL, (DLGPROC)LiveCoreWaitProc);
	if (!m_hWnd)
	{
		return FALSE;
	}

	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);//获取屏幕宽度
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);//获取屏幕高度

	nPosX = (nScreenWidth - LIVECOREWAIT_DLG_WIDTH) >> 1;//设置窗口坐标
	nPosY = (nScreenHeight - LIVECOREWAIT_DLG_HEIGHT) >> 1;//设置窗口坐标

	//设置窗口样式
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, ::GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	HRESULT hr;

	//获取纹理路径
	LiveCoreWait_Texture_GetPath("frame\\Wait\\Wait.png");

	//初始化D3D
	m_pLiveWaitGraphics = new DirectGraphics();
	hr = m_pLiveWaitGraphics->DirectGraphicsInit(m_hWnd, true, LIVECOREWAIT_DLG_WIDTH, LIVECOREWAIT_DLG_HEIGHT);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//初始化D3D纹理
	m_pLiveWaitTexture = new DirectTexture(m_pLiveWaitGraphics->DirectGraphicsGetDevice());
	hr = m_pLiveWaitTexture->DirectTextureLoadTexture(m_tcTexturePath);
	if (FAILED(hr))
	{
		return FALSE;
	}

	SetWindowPos(m_hWnd, NULL, nPosX, nPosY, LIVECOREWAIT_DLG_WIDTH, LIVECOREWAIT_DLG_HEIGHT, SWP_NOACTIVATE | SWP_SHOWWINDOW);

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitUpdate()
// @Purpose: CLiveCoreWait刷新
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitUpdate()
{

}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitUpdate()
// @Purpose: CLiveCoreWait渲染
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitRender()
{
	m_pLiveWaitGraphics->DirectGraphicsBegin();

	m_pLiveWaitGraphics->DirectGraphicsEnd();
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitProc()
// @Purpose: CLiveCoreWait处理函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
LRESULT CLiveCoreWait::LiveCoreWaitProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 1;
	default:
		break;
	}

	return 0;
}