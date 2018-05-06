/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectGraphics2D.h
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
#pragma once

#ifndef __DIRECTGRAPHICS2D_H_
#define __DIRECTGRAPHICS2D_H_

//Include Windows Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	DIRECTGRAPHICS2D_EXPORTS
#define DIRECTGRAPHICS2D_API	__declspec(dllexport)
#else
#define DIRECTGRAPHICS2D_API	__declspec(dllimport)
#endif

#define DIRECTGRAPHICS2D_CALLMODE	__stdcall

//Struct Definition
//Vertex 2D Base(2D���������ʽ)
struct Vertex2DBase
{
	float X, Y, Z, RHW;
	DWORD COLOR;
	Vertex2DBase(float x, float y, float z, float rhw, DWORD Color) :X(x), Y(y), Z(z), RHW(rhw), COLOR(Color) {}
};

#define D3DFVF_VERTEX2D_BASE	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)				//���������ʽģʽ(2D����/���������)

//Vertex 2D Texture(2D�������ʽ)
struct Vertex2DTexture
{
	float X, Y, Z, RHW;
	DWORD COLOR;
	float U, V;
	Vertex2DTexture(float x, float y, float z, float rhw, DWORD Color, float u, float v) :X(x), Y(y), Z(z), RHW(rhw), COLOR(Color), U(u), V(v) {}
};

#define D3DFVF_VERTEX2D_TEXTURE	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//�������ʽģʽ(2D����/���������/����ͼ��)

//Vertex 2D Diffuse Specular Texture(2D���淴���������ʽ)
struct Vertex2DSpecularTexture
{
	float X, Y, Z, RHW;
	DWORD DIFFUSE;
	DWORD SPECULAR;
	float U, V;
	Vertex2DSpecularTexture(float x, float y, float z, float rhw, DWORD Diffuse, DWORD Specular, float u, float v) :X(x), Y(y), Z(z), RHW(rhw), DIFFUSE(Diffuse), SPECULAR(Specular), U(u), V(v) {}
};

#define D3DFVF_VERTEX2D_SPECULAR_TEXTURE	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)	//�����������ʽģʽ(2D����/���������/���淴�����/����ͼ��)

//Enum Definition
enum Vertex2DType
{
	Vertex2D_Type_Base = 0,				//Base����
	Vertex2D_Type_Texture = 1,			//Texture����
	Vertex2D_Type_Specular_Texture = 2,	//SpecularTexture����
};

//Class Definition
class DirectGraphics2D
{
protected:
	LPDIRECT3DDEVICE9 m_pD3D9Device;						//The Direct3D 9 Render Device 
	LPDIRECT3DVERTEXBUFFER9 m_pD3D9VertexBuffer;			//The Direct3D 9 Vertex Buffer
	LPDIRECT3DINDEXBUFFER9 m_pD3D9IndexBuffer;				//The Direct3D 9 Index  Buffer

private:
	LPDIRECT3DTEXTURE9 m_pD3D9Texture;						//The Direct3D 9 Texture

	CRITICAL_SECTION m_cs;									//Thread Safe(CriticalSection)
	bool m_bThreadSafe;										//Thread Safe Status

public:
	DirectGraphics2D();										//DirectGraphics2D Constructor Function(���캯��)
	~DirectGraphics2D();									//DirectGraphics2D Destructor  Function(��������)

	//����
	DirectGraphics2D(LPDIRECT3DDEVICE9 pD3D9Device);		//DirectGraphics2D Constructor Function(���캯��)(����D3D9 Device)(Important)

	//����
	virtual LPDIRECT3DDEVICE9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetD3D9Device(void) const;				//DirectGraphics2D D3D9 Get Device Pointer
	virtual LPDIRECT3DVERTEXBUFFER9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetVertexBuffer(void) const;		//DirectGraphics2D D3D9 Get Vertex Buffer
	virtual LPDIRECT3DINDEXBUFFER9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetIndexBuffer(void) const;		//DirectGraphics2D D3D9 Get Index Buffer
	virtual LPDIRECT3DTEXTURE9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetTexture(void) const;				//DirectGraphics2D D3D9 Get Texture

	//����
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetD3D9Device(LPDIRECT3DDEVICE9 pD3D9Device);				//DirectGraphics2D D3D9 Set Device Pointer
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 pD3D9VertexBuffer);	//DirectGraphics2D D3D9 Set Vertex Buffer
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetIndexBuffer(LPDIRECT3DINDEXBUFFER9 pD3D9IndexBuffer);		//DirectGraphics2D D3D9 Set Index Buffer
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetTexture(LPDIRECT3DTEXTURE9 pD3D9Texture);					//DirectGraphics2D D3D9 Set Texture

	//����(��ʧ�豸)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DReset(void);												//DirectGraphics2D D3D9 Reset(����)(Reset����Ҫ����Init�������³�ʼ��)

	//��ʼ��
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(int nPlane);														//DirectGraphics2D Initialization(��ʼ��)(ƽ����)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(int nPlane, LPCWSTR lpszStrTexture);								//DirectGraphics2D Initialization(��ʼ��)(ƽ����/����)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane);							//DirectGraphics2D Initialization(��ʼ��)(��������/ƽ����)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane, LPCWSTR lpszStrTexture);	//DirectGraphics2D Initialization(��ʼ��)(��������/ƽ����/����)

	//���
	//����
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertex(Vertex2DBase* VertexArray, int nSize);						//DirectGraphics2D Padding Vertex(��䶥������)(2D���������ʽ)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertex(Vertex2DTexture* VertexArray, int nSize);					//DirectGraphics2D Padding Vertex(��䶥������)(2D���������ʽ)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertex(Vertex2DSpecularTexture* VertexArray, int nSize);			//DirectGraphics2D Padding Vertex(��䶥������)(2D���㾵�������ʽ)

	//����
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingIndex(int nPlane);												//DirectGraphics2D Padding Index(�����������)

	//All
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DBase* VertexArray, int nPlane);						//DirectGraphics2D Padding Vertex and Index(��䶥�����������)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DTexture* VertexArray, int nPlane);						//DirectGraphics2D Padding Vertex and Index(��䶥�����������)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DSpecularTexture* VertexArray, int nPlane);				//DirectGraphics2D Padding Vertex and Index(��䶥�����������)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DType eVertex2DType, LPVOID VertexArray, int nPlane);	//DirectGraphics2D Padding Vertex and Index(��䶥�����������)

	//��Ⱦ
	//��Ⱦģʽ
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateAlphaEnable(void);														//DirectGraphics2D Render State Setting(����Alpha���)//��Ⱦ��Ϲر�Alpha���
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateAlphaDisable(void);														//DirectGraphics2D Render State Setting(�ر�Alpha���)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateSetting(void);															//DirectGraphics2D Render State Setting
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateAlphaMix(void);															//DirectGraphics2D Render State Setting(Alpha�ں�����)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateColorMix(void);															//DirectGraphics2D Render State Setting(Color�ں�����)(ѡ��)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateColorMix(D3DXCOLOR MixColor);												//DirectGraphics2D Render State Setting(Color�ں�����)(���)

	//����
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRender(Vertex2DType eVertex2DType, int nPlane, bool bIsTexture = false);											//DirectGraphics2D Render(��Ⱦ)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRender(Vertex2DType eVertex2DType, int nStartIndex, int nPlane, bool bIsTexture = false);						//DirectGraphics2D Render(��Ⱦ)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRender(Vertex2DType eVertex2DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture);				//DirectGraphics2D Render(��Ⱦ)
};

#endif