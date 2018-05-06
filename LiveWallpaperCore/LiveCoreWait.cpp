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
	m_bShow = false;
	m_bSakuraStop = false;
	m_bUnpackStop = false;
	m_nSakuraCount = 0;
	m_hWnd = NULL;
	m_pLiveWaitGraphics = NULL;
	m_pLiveWaitGraphics2D = NULL;
	m_pLiveWaitTexture = NULL;
	m_pLiveWaitSprite = NULL;
	memset(m_tcTexturePath, 0, MAX_PATH * sizeof(TCHAR));
	memset(m_tcSpritePath, 0, MAX_PATH * sizeof(TCHAR));
	memset(m_arrSakura, 0, LIVECOREWAIT_PARTICLE_NUMBER * sizeof(TLiveCoreSakura));
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
	SAFE_DELETE(m_pLiveWaitSprite);
	SAFE_DELETE(m_pLiveWaitTexture);
	SAFE_DELETE(m_pLiveWaitGraphics2D);
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
// @Function:	 LiveCoreWait_Sprite_GetPath()
// @Purpose: CLiveCoreWait获取点精灵路径小程序
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWait_Sprite_GetPath(LPCSTR szFile)
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

	memset(m_tcSpritePath, 0, MAX_PATH * sizeof(TCHAR));
	bRet = LiveCoreWait_Convert_A2W(chArr, m_tcSpritePath, MAX_PATH);
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
	LiveCoreWait_Sprite_GetPath("frame\\Wait\\Sakura.png");

	//初始化D3D
	m_pLiveWaitGraphics = new DirectGraphics();
	hr = m_pLiveWaitGraphics->DirectGraphicsInit(m_hWnd, true, LIVECOREWAIT_DLG_WIDTH, LIVECOREWAIT_DLG_HEIGHT);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//初始化D3D渲染2D图形
	m_pLiveWaitGraphics2D = new DirectGraphics2D(m_pLiveWaitGraphics->DirectGraphicsGetDevice());
	hr = m_pLiveWaitGraphics2D->DirectGraphics2DInit(Vertex2D_Type_Texture, 1);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//初始化D3D纹理
	m_pLiveWaitTexture = new DirectTexture(m_pLiveWaitGraphics->DirectGraphicsGetDevice());
	hr = m_pLiveWaitTexture->DirectTextureLoadTextureEx(m_tcTexturePath, 1024, 256);
	if (FAILED(hr))
	{
		return FALSE;
	}

	//初始化Sakura樱花粒子
	m_pLiveWaitSprite = new DirectSprite(m_pLiveWaitGraphics->DirectGraphicsGetDevice());
	hr = m_pLiveWaitSprite->DirectSpriteInit(m_tcSpritePath);
	if (FAILED(hr))
	{
		return FALSE;
	}

	LiveCoreWaitSetSakura(0, 80, 640, 480);
	LiveCoreWaitInitSakura();

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
	static bool bAlpha = true;
	static float fAlpha = 0.5f;
	Vertex2DTexture pVertex2DTextureArray[] =
	{
		Vertex2DTexture(0.0f, 0.0f, 0.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha), (0.0f / 1024.0f), (0.0f / 256.0f)),
		Vertex2DTexture(640.0f, 0.0f, 0.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha), (640.0f / 1024.0f), (0.0f / 256.0f)),
		Vertex2DTexture(640.0f, 80.0f, 0.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha), (640.0f / 1024.0f), (80.0f / 256.0f)),
		Vertex2DTexture(0.0f, 80.0f, 0.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha), (0.0f / 1024.0f), (80.0f / 256.0f)),
	};

	if (!bAlpha)
	{
		fAlpha -= 0.02f;
		if (fAlpha <= 0.5f)
		{
			fAlpha = 0.5f;
			bAlpha = true;
		}
	}
	else
	{
		fAlpha += 0.02f;
		if (fAlpha >= 1.0f)
		{
			fAlpha = 1.0f;
			bAlpha = false;
		}
	}

	m_pLiveWaitGraphics2D->DirectGraphics2DPaddingVertex(pVertex2DTextureArray, 4);
	m_pLiveWaitGraphics2D->DirectGraphics2DPaddingIndex(1);

	LiveCoreWaitUpdateSakura();
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
	m_pLiveWaitGraphics2D->DirectGraphics2DRenderStateSetting();

	m_pLiveWaitGraphics2D->DirectGraphics2DRender(Vertex2D_Type_Texture, 0, 1, m_pLiveWaitTexture->DirectTextureGetTexture());
	::SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

	LiveCoreWaitRenderSakura();

	m_pLiveWaitGraphics2D->DirectGraphics2DRenderStateAlphaDisable();
	m_pLiveWaitGraphics->DirectGraphicsEnd();
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitShowWindow()
// @Purpose: CLiveCoreWait显示窗口
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitShowWindow()
{
	if (!m_bShow)
	{
		ShowWindow(m_hWnd, SW_SHOW);
		m_bShow = true;
	}
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitSetSakura()
// @Purpose: CLiveCoreWait设置樱花粒子区域
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitSetSakura(int nX, int nY, int nWidth, int nHeight)
{
	m_nSakuraPosX = nX;
	m_nSakuraPosY = nY;
	m_nSakuraWidth = nWidth;
	m_nSakuraHeight = nHeight;
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitInitSakura()
// @Purpose: CLiveCoreWait初始化樱花粒子
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitInitSakura()
{
	srand(GetTickCount());	//初始化随机数种子

	for (int i = 0; i < LIVECOREWAIT_PARTICLE_NUMBER; ++i)
	{
		m_arrSakura[i].fAlpha = (float)(0.5f + ((rand() % 101) * 1.0f / 200.0f));				//粒子Alpha: (0.5f~1.0f)
		m_arrSakura[i].fFallSpeed = (float)(m_nSakuraHeight * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * m_nSakuraHeight);//粒子下落速度
		m_arrSakura[i].fMoveSpeed = (float)(((rand() % 100) * 1.0f / 500.0f) * m_nSakuraWidth);	//粒子移动速度
		m_arrSakura[i].fRotateSpeed = (float)(D3DX_PI * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * D3DX_PI);		//例子旋转速度
		m_arrSakura[i].nMoveDirect = rand() % 2;	//移动方向: (0~左 1~右)
		m_arrSakura[i].nRotateDirect = rand() % 2;	//旋转方向: (0~左 1~右)
		m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX = (float)(m_nSakuraPosX + m_nSakuraWidth * 0.1f + (rand() % m_nSakuraWidth) * 0.9f);					//粒子X坐标: (x~x+width)
		m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY = (float)(m_nSakuraPosY + rand() % m_nSakuraHeight - m_nSakuraHeight);	//粒子Y左边: (y~y+height)
		m_arrSakura[i].sTransformPara.sScalePara.fScaleX = (float)(0.2f + ((rand() % 80) * 1.0f / 100.0f));			//粒子拉伸变换系数: (0.2f~1.0f)
		m_arrSakura[i].sTransformPara.sScalePara.fScaleY = m_arrSakura[i].sTransformPara.sScalePara.fScaleX;		//粒子拉伸变换系数: (0.2f~1.0f)
		m_arrSakura[i].sTransformPara.sRotatePara.fRotateZ = (float)(((rand() % 100) * 1.0f / 600.0f) * D3DX_PI);	//粒子旋转变换系数: (Arc:0~Pi/6)
	}

}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitUpdateSakura()
// @Purpose: CLiveCoreWait刷新樱花粒子
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitUpdateSakura()
{
	HRESULT hr;

	hr = m_pLiveWaitGraphics->DirectGraphicsTestCooperativeLevel();
	if (hr != S_OK)
	{
		if (hr == D3DERR_DEVICELOST)
		{
			return;
		}

		if (hr == D3DERR_DEVICENOTRESET)
		{
			IDirect3DDevice9* pD3D9Device = NULL;
			IDirect3DSurface9* pD3D9BackBuffer = NULL;

			pD3D9Device = m_pLiveWaitGraphics->DirectGraphicsGetDevice();
			pD3D9Device->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &pD3D9BackBuffer);
			SAFE_RELEASE(pD3D9BackBuffer);

			m_pLiveWaitGraphics2D->DirectGraphics2DReset();
			m_pLiveWaitTexture->DirectTextureReset();
			m_pLiveWaitSprite->DirectSpriteReset();

			m_pLiveWaitGraphics->DirectGraphicsResetDevice();

			m_pLiveWaitGraphics2D->DirectGraphics2DInit(Vertex2D_Type_Texture, 1);
			m_pLiveWaitTexture->DirectTextureLoadTextureEx(m_tcTexturePath, 1024, 256);
			m_pLiveWaitSprite->DirectSpriteInit(m_tcSpritePath);

		}

	}

	for (int i = 0; i < LIVECOREWAIT_PARTICLE_NUMBER; ++i)
	{
		m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY += m_arrSakura[i].fFallSpeed * 0.0167f;
		if (m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY > m_nSakuraHeight * 0.9f
			|| m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX < m_nSakuraWidth * 0.1f
			|| m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX > m_nSakuraWidth * 0.9f)
		{
			if (!m_bUnpackStop)
			{
				m_arrSakura[i].fAlpha = (float)(0.5f + ((rand() % 101) * 1.0f / 200.0f));				//粒子Alpha: (0.5f~1.0f)
				m_arrSakura[i].fFallSpeed = (float)(m_nSakuraHeight * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * m_nSakuraHeight);//粒子下落速度
				m_arrSakura[i].fMoveSpeed = (float)(((rand() % 100) * 1.0f / 500.0f) * m_nSakuraWidth);	//粒子移动速度
				m_arrSakura[i].fRotateSpeed = (float)(D3DX_PI * 1.0f / 5.0f + ((rand() % 100) * 1.0f / 200.0f) * D3DX_PI);		//粒子旋转速度
				m_arrSakura[i].nMoveDirect = rand() % 2;	//移动方向: (0~左 1~右)
				m_arrSakura[i].nRotateDirect = rand() % 2;	//旋转方向: (0~左 1~右)
				m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX = (float)(m_nSakuraPosX + m_nSakuraWidth * 0.1f + (rand() % m_nSakuraWidth) * 0.9f);					//粒子X坐标: (x~x+width)
				m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY = (float)(m_nSakuraPosY + rand() % m_nSakuraHeight - m_nSakuraHeight);	//粒子Y左边: (y~y+height)
				m_arrSakura[i].sTransformPara.sScalePara.fScaleX = (float)(0.2f + ((rand() % 80) * 1.0f / 100.0f));			//粒子拉伸变换系数: (0.2f~1.0f)
				m_arrSakura[i].sTransformPara.sScalePara.fScaleY = m_arrSakura[i].sTransformPara.sScalePara.fScaleX;		//粒子拉伸变换系数: (0.2f~1.0f)
				m_arrSakura[i].sTransformPara.sRotatePara.fRotateZ = (float)(((rand() % 100) * 1.0f / 600.0f) * D3DX_PI);	//粒子旋转变换系数: (Arc:0~Pi/6)
			}
			else
			{
				m_arrSakura[i].fAlpha = (float)(0.5f + ((rand() % 101) * 1.0f / 200.0f));				//粒子Alpha: (0.5f~1.0f)
				m_arrSakura[i].fFallSpeed = 0.0f;	//粒子下落速度
				m_arrSakura[i].fMoveSpeed = 0.0f;	//粒子移动速度
				m_arrSakura[i].fRotateSpeed = 0.0f;	//粒子旋转速度
				m_arrSakura[i].nMoveDirect = rand() % 2;	//移动方向: (0~左 1~右)
				m_arrSakura[i].nRotateDirect = rand() % 2;	//旋转方向: (0~左 1~右)
				m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX = (float)(m_nSakuraPosX + m_nSakuraWidth * 0.1f + (rand() % m_nSakuraWidth) * 0.9f);					//粒子X坐标: (x~x+width)
				m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY = (float)(m_nSakuraPosY + rand() % m_nSakuraHeight - m_nSakuraHeight);	//粒子Y左边: (y~y+height)
				m_arrSakura[i].sTransformPara.sScalePara.fScaleX = (float)(0.2f + ((rand() % 80) * 1.0f / 100.0f));			//粒子拉伸变换系数: (0.2f~1.0f)
				m_arrSakura[i].sTransformPara.sScalePara.fScaleY = m_arrSakura[i].sTransformPara.sScalePara.fScaleX;		//粒子拉伸变换系数: (0.2f~1.0f)
				m_arrSakura[i].sTransformPara.sRotatePara.fRotateZ = (float)(((rand() % 100) * 1.0f / 600.0f) * D3DX_PI);	//粒子旋转变换系数: (Arc:0~Pi/6)

				m_nSakuraCount++;
				if(m_nSakuraCount == LIVECOREWAIT_PARTICLE_NUMBER)
				{
					m_bSakuraStop = true;
				}

			}
		}

		if (m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY > m_nSakuraHeight * 0.8f)
		{
			m_arrSakura[i].fAlpha -= 0.05f;
			if (m_arrSakura[i].fAlpha <= 0.5f)
			{
				m_arrSakura[i].fAlpha = 0.5f;
			}
		}

		if (m_arrSakura[i].nMoveDirect == 0)
		{
			m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX += m_arrSakura[i].fMoveSpeed * 0.0167f;
		}
		else
		{
			m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX -= m_arrSakura[i].fMoveSpeed * 0.0167f;
		}

		if (m_arrSakura[i].nRotateDirect == 0)
		{
			m_arrSakura[i].sTransformPara.sRotatePara.fRotateZ += m_arrSakura[i].fRotateSpeed * 0.0167f;
		}
		else
		{
			m_arrSakura[i].sTransformPara.sRotatePara.fRotateZ -= m_arrSakura[i].fRotateSpeed * 0.0167f;
		}

	}

}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitRenderSakura()
// @Purpose: CLiveCoreWait渲染樱花粒子
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void LIVECOREWAIT_CALLMODE CLiveCoreWait::LiveCoreWaitRenderSakura()
{
	m_pLiveWaitSprite->DirectSpriteBegin();

	for (int i = 0; i < LIVECOREWAIT_PARTICLE_NUMBER; ++i)
	{
		DirectSpriteDrawPara sDrawPara = { 0 };
		SetRect(&sDrawPara.SpriteRect, 0, 0, 64, 64);
		sDrawPara.SpriteCenter = D3DXVECTOR3(30.0f, 32.0f, 0.0f);
		sDrawPara.SpritePosition = D3DXVECTOR3(m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateX, m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY, 0.0f);
		sDrawPara.SpriteColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_arrSakura[i].fAlpha);

		m_pLiveWaitSprite->DirectSpriteDrawTransform(&sDrawPara, m_arrSakura[i].sTransformPara, m_arrSakura[i].sTransformPara.sTranslatePara.fTranslateY, m_nSakuraPosY);
	}

	m_pLiveWaitSprite->DirectSpriteEnd();
}

//------------------------------------------------------------------
// @Function:	 LiveCoreWaitSakuraSetFlag()
// @Purpose: CLiveCoreWait设置解包标志
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CLiveCoreWait::LiveCoreWaitSakuraSetFlag(bool bStop)
{
	m_bUnpackStop = bStop;
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
	case WM_PAINT:
		break;
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