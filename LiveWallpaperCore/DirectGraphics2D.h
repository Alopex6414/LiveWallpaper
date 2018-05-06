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
//Vertex 2D Base(2D基本顶点格式)
struct Vertex2DBase
{
	float X, Y, Z, RHW;
	DWORD COLOR;
	Vertex2DBase(float x, float y, float z, float rhw, DWORD Color) :X(x), Y(y), Z(z), RHW(rhw), COLOR(Color) {}
};

#define D3DFVF_VERTEX2D_BASE	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)				//基本顶点格式模式(2D坐标/漫反射光线)

//Vertex 2D Texture(2D纹理顶点格式)
struct Vertex2DTexture
{
	float X, Y, Z, RHW;
	DWORD COLOR;
	float U, V;
	Vertex2DTexture(float x, float y, float z, float rhw, DWORD Color, float u, float v) :X(x), Y(y), Z(z), RHW(rhw), COLOR(Color), U(u), V(v) {}
};

#define D3DFVF_VERTEX2D_TEXTURE	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//纹理顶点格式模式(2D坐标/漫反射光线/纹理图样)

//Vertex 2D Diffuse Specular Texture(2D镜面反射纹理顶点格式)
struct Vertex2DSpecularTexture
{
	float X, Y, Z, RHW;
	DWORD DIFFUSE;
	DWORD SPECULAR;
	float U, V;
	Vertex2DSpecularTexture(float x, float y, float z, float rhw, DWORD Diffuse, DWORD Specular, float u, float v) :X(x), Y(y), Z(z), RHW(rhw), DIFFUSE(Diffuse), SPECULAR(Specular), U(u), V(v) {}
};

#define D3DFVF_VERTEX2D_SPECULAR_TEXTURE	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1)	//镜面纹理顶点格式模式(2D坐标/漫反射光线/镜面反射光线/纹理图样)

//Enum Definition
enum Vertex2DType
{
	Vertex2D_Type_Base = 0,				//Base类型
	Vertex2D_Type_Texture = 1,			//Texture类型
	Vertex2D_Type_Specular_Texture = 2,	//SpecularTexture类型
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
	DirectGraphics2D();										//DirectGraphics2D Constructor Function(构造函数)
	~DirectGraphics2D();									//DirectGraphics2D Destructor  Function(析构函数)

	//构造
	DirectGraphics2D(LPDIRECT3DDEVICE9 pD3D9Device);		//DirectGraphics2D Constructor Function(构造函数)(传入D3D9 Device)(Important)

	//访问
	virtual LPDIRECT3DDEVICE9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetD3D9Device(void) const;				//DirectGraphics2D D3D9 Get Device Pointer
	virtual LPDIRECT3DVERTEXBUFFER9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetVertexBuffer(void) const;		//DirectGraphics2D D3D9 Get Vertex Buffer
	virtual LPDIRECT3DINDEXBUFFER9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetIndexBuffer(void) const;		//DirectGraphics2D D3D9 Get Index Buffer
	virtual LPDIRECT3DTEXTURE9 DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DGetTexture(void) const;				//DirectGraphics2D D3D9 Get Texture

	//控制
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetD3D9Device(LPDIRECT3DDEVICE9 pD3D9Device);				//DirectGraphics2D D3D9 Set Device Pointer
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 pD3D9VertexBuffer);	//DirectGraphics2D D3D9 Set Vertex Buffer
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetIndexBuffer(LPDIRECT3DINDEXBUFFER9 pD3D9IndexBuffer);		//DirectGraphics2D D3D9 Set Index Buffer
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DSetTexture(LPDIRECT3DTEXTURE9 pD3D9Texture);					//DirectGraphics2D D3D9 Set Texture

	//重置(丢失设备)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DReset(void);												//DirectGraphics2D D3D9 Reset(重置)(Reset后需要调用Init函数重新初始化)

	//初始化
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(int nPlane);														//DirectGraphics2D Initialization(初始化)(平面数)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(int nPlane, LPCWSTR lpszStrTexture);								//DirectGraphics2D Initialization(初始化)(平面数/纹理)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane);							//DirectGraphics2D Initialization(初始化)(顶点类型/平面数)
	virtual HRESULT DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DInit(Vertex2DType eVertex2DType, int nPlane, LPCWSTR lpszStrTexture);	//DirectGraphics2D Initialization(初始化)(顶点类型/平面数/纹理)

	//填充
	//顶点
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertex(Vertex2DBase* VertexArray, int nSize);						//DirectGraphics2D Padding Vertex(填充顶点数据)(2D基本顶点格式)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertex(Vertex2DTexture* VertexArray, int nSize);					//DirectGraphics2D Padding Vertex(填充顶点数据)(2D顶点纹理格式)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertex(Vertex2DSpecularTexture* VertexArray, int nSize);			//DirectGraphics2D Padding Vertex(填充顶点数据)(2D顶点镜面纹理格式)

	//索引
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingIndex(int nPlane);												//DirectGraphics2D Padding Index(填充索引数据)

	//All
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DBase* VertexArray, int nPlane);						//DirectGraphics2D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DTexture* VertexArray, int nPlane);						//DirectGraphics2D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DSpecularTexture* VertexArray, int nPlane);				//DirectGraphics2D Padding Vertex and Index(填充顶点和索引数据)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DPaddingVertexAndIndex(Vertex2DType eVertex2DType, LPVOID VertexArray, int nPlane);	//DirectGraphics2D Padding Vertex and Index(填充顶点和索引数据)

	//渲染
	//渲染模式
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateAlphaEnable(void);														//DirectGraphics2D Render State Setting(开启Alpha混合)//渲染完毕关闭Alpha混合
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateAlphaDisable(void);														//DirectGraphics2D Render State Setting(关闭Alpha混合)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateSetting(void);															//DirectGraphics2D Render State Setting
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateAlphaMix(void);															//DirectGraphics2D Render State Setting(Alpha融合类型)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateColorMix(void);															//DirectGraphics2D Render State Setting(Color融合类型)(选择)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRenderStateColorMix(D3DXCOLOR MixColor);												//DirectGraphics2D Render State Setting(Color融合类型)(混合)

	//绘制
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRender(Vertex2DType eVertex2DType, int nPlane, bool bIsTexture = false);											//DirectGraphics2D Render(渲染)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRender(Vertex2DType eVertex2DType, int nStartIndex, int nPlane, bool bIsTexture = false);						//DirectGraphics2D Render(渲染)
	virtual void DIRECTGRAPHICS2D_CALLMODE DirectGraphics2DRender(Vertex2DType eVertex2DType, int nStartIndex, int nPlane, LPDIRECT3DTEXTURE9 pRenderTexture);				//DirectGraphics2D Render(渲染)
};

#endif