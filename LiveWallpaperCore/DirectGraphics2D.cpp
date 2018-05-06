/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics2D.cpp
* @brief	This Program is DirectGraphics2D DLL Project.
* @author	Alopex/Helium
* @version	v1.21a
* @date		2017-11-2	v1.00a	alopex	Create Project.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-2-12	v1.22a	alopex	Add Reset Lost Device.
* @date		2018-4-12	v1.23a	alopex	Add Macro Call Mode.
*/
#include "DirectCommon.h"
#include "DirectGraphics2D.h"
#include "DirectThreadSafe.h"

//------------------------------------------------------------------
// @Function:	 DirectGraphics2D()
// @Purpose: DirectGraphics2D���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics2D::DirectGraphics2D()
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = NULL;					//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9VertexBuffer = NULL;				//IDirect3DVertexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9IndexBuffer = NULL;				//IDirect3DIndexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Texture = NULL;					//IDirect3DTexture9�ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 ~DirectGraphics2D()
// @Purpose: DirectGraphics2D��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectGraphics2D::~DirectGraphics2D()
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);		//IDirect3DVertexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9IndexBuffer);		//IDirect3DIndexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9Texture);			//IDirect3DTexture9�ӿ�ָ���ͷ�

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//ɾ���ٽ���
}

//-----------------------------------------------------------------------
// @Function:	 DirectGraphics2D(IDirect3DDevice9* pD3D9Device)
// @Purpose: DirectGraphics2D���캯��
// @Since: v1.00a
// @Para: IDirect3DDevice9* pD3D9Device		//Direct3D 9 Device (�����豸)
// @Return: None
//-----------------------------------------------------------------------
DirectGraphics2D::DirectGraphics2D(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = pD3D9Device;			//IDirect3DDevice9�ӿ�ָ���ʼ��
	m_pD3D9VertexBuffer = NULL;				//IDirect3DVertexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9IndexBuffer = NULL;				//IDirect3DIndexBuffer9�ӿ�ָ���ʼ��(NULL)
	m_pD3D9Texture = NULL;					//IDirect3DTexture9�ӿ�ָ���ʼ��(NULL)
}

//-----------------------------------------------------------------------
// @Function:	 DirectGraphics2DGetD3D9Device(void)
// @Purpose: DirectGraphics2D��ȡ�豸�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
LPDIRECT3DDEVICE9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DGetD3D9Device(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Device;
}

//-----------------------------------------------------------------------
// @Function:	 DirectGraphics2DGetVertexBuffer(void)
// @Purpose: DirectGraphics2D��ȡ���㻺��ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DGetVertexBuffer(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9VertexBuffer;
}

//-----------------------------------------------------------------------
// @Function:	 DirectGraphics2DGetIndexBuffer(void)
// @Purpose: DirectGraphics2D��ȡ��������ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
LPDIRECT3DINDEXBUFFER9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DGetIndexBuffer(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9IndexBuffer;
}

//-----------------------------------------------------------------------
// @Function:	 DirectGraphics2DGetTexture(void)
// @Purpose: DirectGraphics2D��ȡ����ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
LPDIRECT3DTEXTURE9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DGetTexture(void) const
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	return m_pD3D9Texture;
}

//---------------------------------------------------------------------------
// @Function:	 DirectGraphics2DSetD3D9Device(LPDIRECT3DDEVICE9 pD3D9Device)
// @Purpose: DirectGraphics2D�����豸�ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DSetD3D9Device(LPDIRECT3DDEVICE9 pD3D9Device)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device = pD3D9Device;
}

//-----------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DSetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 pD3D9VertexBuffer)
// @Purpose: DirectGraphics2D���ö��㻺��ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DSetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 pD3D9VertexBuffer)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9VertexBuffer = pD3D9VertexBuffer;
}

//-----------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DSetIndexBuffer(LPDIRECT3DINDEXBUFFER9 pD3D9IndexBuffer)
// @Purpose: DirectGraphics2D������������ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DSetIndexBuffer(LPDIRECT3DINDEXBUFFER9 pD3D9IndexBuffer)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9IndexBuffer = pD3D9IndexBuffer;
}

//-----------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DSetTexture(LPDIRECT3DTEXTURE9 pD3D9Texture)
// @Purpose: DirectGraphics2D��������ͼ���ӿ�ָ��
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DSetTexture(LPDIRECT3DTEXTURE9 pD3D9Texture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Texture = pD3D9Texture;
}

//-----------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DReset(void)
// @Purpose: DirectGraphics2D����(��ʧ�豸)
// @Since: v1.00a
// @Para: None
// @Return: HRESULT(�ɹ�:S_OK, ʧ��:E_FAIL)
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DReset(void)
{
	SAFE_RELEASE(m_pD3D9VertexBuffer);		//IDirect3DVertexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9IndexBuffer);		//IDirect3DIndexBuffer9�ӿ�ָ���ͷ�
	SAFE_RELEASE(m_pD3D9Texture);			//IDirect3DTexture9�ӿ�ָ���ͷ�
	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DInit(int nPlane)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: int nPlane	//ƽ�����
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DInit(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DBase), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	//IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DInit(int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: int nPlane				//ƽ�����
// @Para: LPCWSTR lpszStrTexture	//����·��
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DInit(int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//VertexBuffer�������㻺��
	VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DTexture), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));

	//IndexBuffer������������
	VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));

	//Texture����ƽ������
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));

	return S_OK;
}

//-----------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType	//��������
// @Para: int nPlane					//ƽ�����
// @Return: None
//-----------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DBase), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DTexture), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Specular_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DSpecularTexture), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane, LPCWSTR lpszStrTexture)
// @Purpose: DirectGraphics2D��ʼ��
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType	//��������
// @Para: int nPlane					//ƽ�����
// @Para: LPCWSTR lpszStrTexture		//����·��
// @Return: None
//---------------------------------------------------------------------------------------------------
HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane, LPCWSTR lpszStrTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DBase), 0, D3DFVF_VERTEX2D_BASE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		break;
	case Vertex2D_Type_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DTexture), 0, D3DFVF_VERTEX2D_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		//Texture����ƽ������
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	case Vertex2D_Type_Specular_Texture:
		//VertexBuffer�������㻺��
		VERIFY(m_pD3D9Device->CreateVertexBuffer(4 * nPlane * sizeof(Vertex2DSpecularTexture), 0, D3DFVF_VERTEX2D_SPECULAR_TEXTURE, D3DPOOL_DEFAULT, &m_pD3D9VertexBuffer, NULL));
		//IndexBuffer������������
		VERIFY(m_pD3D9Device->CreateIndexBuffer(6 * nPlane * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pD3D9IndexBuffer, NULL));
		//Texture����ƽ������
		VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStrTexture, &m_pD3D9Texture));
		break;
	default:
		return E_FAIL;
		break;
	}

	return S_OK;
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingVertex(Vertex2DBase* VertexArray, int nSize)
// @Purpose: DirectGraphics2D��䶥��(Base����)
// @Since: v1.00a
// @Para: Vertex2DBase* VertexArray		//��䶥�������ַ
// @Para: int nSize						//��䶥�����鳤��
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingVertex(Vertex2DBase* VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	Vertex2DBase* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingVertex(Vertex2DTexture* VertexArray, int nSize)
// @Purpose: DirectGraphics2D��䶥��(Texture����)
// @Since: v1.00a
// @Para: Vertex2DTexture* VertexArray	//��䶥�������ַ
// @Para: int nSize						//��䶥�����鳤��
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingVertex(Vertex2DTexture* VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	Vertex2DTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingVertex(Vertex2DSpecularTexture* VertexArray, int nSize)
// @Purpose: DirectGraphics2D��䶥��(Specular����)
// @Since: v1.00a
// @Para: Vertex2DSpecularTexture* VertexArray		//��䶥�������ַ
// @Para: int nSize									//��䶥�����鳤��
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingVertex(Vertex2DSpecularTexture* VertexArray, int nSize)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	Vertex2DSpecularTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < nSize; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingIndex(int nPlane)
// @Purpose: DirectGraphics2D�������
// @Since: v1.00a
// @Para: int nPlane	//ƽ����
// @Return: None
//--------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingIndex(int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingVertexAndIndex(Vertex2DBase* VertexArray, int nPlane)
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DBase* VertexArray					//��䶥�������ַ
// @Para: int nPlane								//���ƽ�����
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingVertexAndIndex(Vertex2DBase* VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//��䶥�㻺��
	Vertex2DBase* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingVertexAndIndex(Vertex2DTexture* VertexArray, int nPlane)
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DTexture* VertexArray				//��䶥�������ַ
// @Para: int nPlane								//���ƽ�����
// @Return: None
//---------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingVertexAndIndex(Vertex2DTexture* VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//��䶥�㻺��
	Vertex2DTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingVertexAndIndex(Vertex2DSpecularTexture* VertexArray, int nPlane)
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DSpecularTexture* VertexArray				//��䶥�������ַ
// @Para: int nPlane										//���ƽ�����
// @Return: None
//------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingVertexAndIndex(Vertex2DSpecularTexture* VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//��䶥�㻺��
	Vertex2DSpecularTexture* pVertices = NULL;

	m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices, 0);

	for (int i = 0; i < 4 * nPlane; ++i)
	{
		*(pVertices + i) = *(VertexArray + i);
	}

	m_pD3D9VertexBuffer->Unlock();

	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DPaddingVertexAndIndex(Vertex2DType eVertex2DType, LPVOID VertexArray, int nPlane)
// @Purpose: DirectGraphics2D��䶥������
// @Since: v1.00a
// @Para: Vertex2DType eVertex2DType						//��������
// @Para: LPVOID VertexArray								//��䶥�������ַ
// @Para: int nPlane										//���ƽ�����
// @Return: None
//---------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DPaddingVertexAndIndex(Vertex2DType eVertex2DType, LPVOID VertexArray, int nPlane)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	Vertex2DBase* pVertices2DBase = NULL;
	Vertex2DTexture* pVertices2DTexture = NULL;
	Vertex2DSpecularTexture* pVertices2DSpecularTexture = NULL;

	//��䶥�㻺��
	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DBase, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DBase + i) = *((Vertex2DBase*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DTexture + i) = *((Vertex2DTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9VertexBuffer->Lock(0, 0, (void**)&pVertices2DSpecularTexture, 0);

		for (int i = 0; i < 4 * nPlane; ++i)
		{
			*(pVertices2DSpecularTexture + i) = *((Vertex2DSpecularTexture*)VertexArray + i);
		}
		m_pD3D9VertexBuffer->Unlock();
		break;
	default:
		return;
		break;
	}

	//�����������
	//�����������
	WORD* pIndices = NULL;
	m_pD3D9IndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	for (int i = 0; i < nPlane; ++i)
	{
		*(pIndices + 6 * i + 0) = 4 * i + 0;
		*(pIndices + 6 * i + 1) = 4 * i + 1;
		*(pIndices + 6 * i + 2) = 4 * i + 2;

		*(pIndices + 6 * i + 3) = 4 * i + 0;
		*(pIndices + 6 * i + 4) = 4 * i + 2;
		*(pIndices + 6 * i + 5) = 4 * i + 3;
	}

	m_pD3D9IndexBuffer->Unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRenderStateAlphaEnable()
// @Purpose: DirectGraphics2D����Alpha���
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRenderStateAlphaEnable(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//Alpha��Ͽ���
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRenderStateAlphaDisable()
// @Purpose: DirectGraphics2D�ر�Alpha���
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRenderStateAlphaDisable(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					//Alpha��Ϲر�
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRenderStateSetting()
// @Purpose: DirectGraphics2D������Ⱦ״̬
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRenderStateSetting(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//��Ⱦģʽ:Alpha�������
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//Alpha��Ͽ���
	m_pD3D9Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					//Alpha���ģʽ:ADD
	m_pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//��Ⱦģʽ:����������
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);//D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRenderStateAlphaMix()
// @Purpose: DirectGraphics2D������Ⱦ״̬(Alpha�ں�)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRenderStateAlphaMix(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//��Ⱦģʽ:Alpha�������
	m_pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);					//Alpha��Ͽ���
	m_pD3D9Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);					//Alpha���ģʽ:ADD
	m_pD3D9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3D9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//��Ⱦģʽ:����������
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);//D3DTA_DIFFUSE//D3DTA_TEXTURE
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRenderStateColorMix()
// @Purpose: DirectGraphics2D������Ⱦ״̬(Color�ں�)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRenderStateColorMix(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//��Ⱦģʽ:����������
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRenderStateColorMix()
// @Purpose: DirectGraphics2D������Ⱦ״̬(Color�ں�)
// @Since: v1.00a
// @Para: None
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRenderStateColorMix(D3DXCOLOR MixColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	//��Ⱦģʽ:����������
	m_pD3D9Device->SetRenderState(D3DRS_TEXTUREFACTOR, MixColor);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3D9Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRender(Vertex2DType eVertex3DType, int nPlane, bool bIsTexture = false)
// @Purpose: DirectGraphics2D��Ⱦ����
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//����ö������
// @Para: int nPlane					//ƽ������
// @Para: bool bIsTexture				//�Ƿ���Ⱦ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRender(Vertex2DType eVertex2DType, int nPlane, bool bIsTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DBase));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DSpecularTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRender(Vertex2DType eVertex3DType, int nStartIndex, int nPlane, bool bIsTexture = false)
// @Purpose: DirectGraphics2D��Ⱦ����
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//����ö������
// @Para: int nStartIndex				//��ʼ����
// @Para: int nPlane					//ƽ������
// @Para: bool bIsTexture				//�Ƿ���Ⱦ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRender(Vertex2DType eVertex2DType, int nStartIndex, int nPlane, bool bIsTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DBase));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DSpecularTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		if (bIsTexture) m_pD3D9Device->SetTexture(0, m_pD3D9Texture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectGraphics2DRender(Vertex2DType eVertex2DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
// @Purpose: DirectGraphics2D��Ⱦ����
// @Since: v1.00a
// @Para: Vertex2DType eVertex3DType	//����ö������
// @Para: int nStartIndex				//��ʼ����
// @Para: int nPlane					//ƽ������
// @Para: bool bIsTexture				//�Ƿ���Ⱦ����
// @Return: None
//---------------------------------------------------------------------------------------------------------------------------------------------
void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2D::DirectGraphics2DRender(Vertex2DType eVertex2DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	switch (eVertex2DType)
	{
	case Vertex2D_Type_Base:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DBase));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_BASE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	case Vertex2D_Type_Specular_Texture:
		m_pD3D9Device->SetStreamSource(0, m_pD3D9VertexBuffer, 0, sizeof(Vertex2DSpecularTexture));
		m_pD3D9Device->SetFVF(D3DFVF_VERTEX2D_SPECULAR_TEXTURE);
		m_pD3D9Device->SetIndices(m_pD3D9IndexBuffer);
		m_pD3D9Device->SetTexture(0, pRenderTexture);
		m_pD3D9Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, nStartIndex, 0, 4 * nPlane, 0, 2 * nPlane);
		break;
	default:
		return;
		break;
	}
}