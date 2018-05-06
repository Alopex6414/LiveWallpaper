/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox 
*     All rights reserved.
*
* @file		DirectSprite.cpp
* @brief	This File is DirectSprite DLL Project Header.
* @author	Alopex/Helium
* @version	v1.22a
* @date		2017-11-28	v1.00a	alopex	Create This Project.
* @date		2017-12-8	v1.10a	alopex	Code Do Not Rely On MSVCR Library.
* @date		2018-1-10	v1.20a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-1-10	v1.21a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-4-12	v1.22a	alopex	Add Macro Call Mode.
*/
#include "DirectCommon.h"
#include "DirectSprite.h"
#include "DirectThreadSafe.h"

//D3DXSprite����(һ������2D������Ⱦ)

//------------------------------------------------------------------
// @Function:	 DirectSprite()
// @Purpose: DirectSprite���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::DirectSprite()
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = NULL;		//IDirect3DDevice9�ӿ�ָ���ʼ��(NULL)
	m_pSpriteTexture = NULL;	//ID3DXSprite��������ӿ�ָ���ʼ��(NULL)
	m_pSprite = NULL;			//ID3DXSprite�㾫��ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 ~DirectSprite()
// @Purpose: DirectSprite��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
DirectSprite::~DirectSprite()
{
	SAFE_RELEASE(m_pSpriteTexture);	//�ͷ�m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);		//�ͷ�m_pSprite

	if (m_bThreadSafe) DeleteCriticalSection(&m_cs);	//ɾ���ٽ���
}

//------------------------------------------------------------------
// @Function:	 DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device)
// @Purpose: DirectSprite���캯��
// @Since: v1.00a
// @Para: LPDIRECT3DDEVICE9 pD3D9Device		//Direct3D�ӿ�ָ��
// @Return: None
//------------------------------------------------------------------
DirectSprite::DirectSprite(LPDIRECT3DDEVICE9 pD3D9Device)
{
	m_bThreadSafe = true;									//�̰߳�ȫ
	if (m_bThreadSafe) InitializeCriticalSection(&m_cs);	//��ʼ���ٽ���

	m_pD3D9Device = pD3D9Device;//IDirect3DDevice9�ӿ�ָ���ʼ��(����D3D9�豸ָ��)
	m_pSpriteTexture = NULL;	//ID3DXSprite��������ӿ�ָ���ʼ��(NULL)
	m_pSprite = NULL;			//ID3DXSprite�㾫��ӿ�ָ���ʼ��(NULL)
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteInit(LPCWSTR lpszStr)
// @Purpose: DirectSprite��ʼ������
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//��������·��
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteInit(LPCWSTR lpszStr)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));//D3DXSprite�����������
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));//D3DXSprite���鴴��

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteReload(LPCWSTR lpszStr)
// @Purpose: DirectSprite���¼�������
// @Since: v1.00a
// @Para: LPCWSTR lpszStr		//��������·��
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteReload(LPCWSTR lpszStr)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);

	SAFE_RELEASE(m_pSpriteTexture);	//�ͷ�m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);		//�ͷ�m_pSprite
	VERIFY(D3DXCreateTextureFromFile(m_pD3D9Device, lpszStr, &m_pSpriteTexture));//D3DXSprite�����������
	VERIFY(D3DXCreateSprite(m_pD3D9Device, &m_pSprite));//D3DXSprite���鴴��

	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteReset(void)
// @Purpose: DirectSprite��ʧ�豸
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteReset(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	SAFE_RELEASE(m_pSpriteTexture);	//�ͷ�m_pSpriteTexture
	SAFE_RELEASE(m_pSprite);		//�ͷ�m_pSprite
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteBegin(void)
// @Purpose: DirectSprite��ʼ��Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteBegin(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pSprite->Begin(D3DXSPRITE_ALPHABLEND));
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteEnd(void)
// @Purpose: DirectSprite������Ⱦ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HRESULT DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteEnd(void)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	VERIFY(m_pSprite->End());
	return S_OK;
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteGetTransform(D3DXMATRIX* pMatrix)
// @Purpose: DirectSprite��ȡ��ǰ�任����
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteGetTransform(D3DXMATRIX* pMatrix)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->GetTransform(pMatrix);
}

//------------------------------------------------------------------
// @Function:	 DirectSpriteSetTransform(D3DXMATRIX* pMatrix)
// @Purpose: DirectSprite���õ�ǰ�任����
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteSetTransform(D3DXMATRIX* pMatrix)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->SetTransform(pMatrix);
}

//----------------------------------------------------------------------
// @Function:	 DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara)
// @Purpose: DirectSprite���õ�ǰ�任����
// @Since: v1.00a
// @Para: DirectSpriteDrawPara* sSpriteDrawPara
// @Return: None
//----------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDraw(DirectSpriteDrawPara* sSpriteDrawPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
}

//----------------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor)
// @Purpose: DirectSprite���ƾ���
// @Since: v1.00a
// @Para: RECT* pSpriteRect				//���ƾ�������
// @Para: D3DXVECTOR3* pSpriteCenter	//������������
// @Para: D3DXVECTOR3* pSpritePosition	//����λ������
// @Para: D3DCOLOR SpriteColor			//������ɫ
// @Return: None
//----------------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDraw(RECT* pSpriteRect, D3DXVECTOR3* pSpriteCenter, D3DXVECTOR3* pSpritePosition, D3DCOLOR SpriteColor)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	m_pSprite->Draw(m_pSpriteTexture, pSpriteRect, pSpriteCenter, pSpritePosition, SpriteColor);
}

//---------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX, float fScaleY)
// @Purpose: DirectSprite��������任
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//---------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, float fScaleX, float fScaleY)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, fScaleX, fScaleY, 1.0f);
	Matrix = Matrix * MatrixScale;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sScalePara)
// @Purpose: DirectSprite��������任
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawScale(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteScale sScalePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sScalePara.fScaleX, sScalePara.fScaleY, 1.0f);
	Matrix = Matrix * MatrixScale;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ)
// @Purpose: DirectSprite������ת�任
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, float fRotateZ)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixRotate;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixRotationZ(&MatrixRotate, fRotateZ);
	Matrix = Matrix * MatrixRotate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-----------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara)
// @Purpose: DirectSprite������ת�任
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-----------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawRotate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteRotate sRotatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixRotate;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixRotationZ(&MatrixRotate, sRotatePara.fRotateZ);
	Matrix = Matrix * MatrixRotate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//---------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX, float fTranslateY)
// @Purpose: DirectSprite����ƽ�Ʊ任
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//---------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, float fTranslateX, float fTranslateY)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixTranslation(&MatrixTranslate, fTranslateX, fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite����ƽ�Ʊ任
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawTranslate(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTranslate sTranslatePara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixTranslation(&MatrixTranslate, sTranslatePara.fTranslateX, sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite���Ʊ任����
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;
	D3DXMATRIX MatrixRotate;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sTransformPara.sScalePara.fScaleX, sTransformPara.sScalePara.fScaleY, 1.0f);
	D3DXMatrixRotationZ(&MatrixRotate, sTransformPara.sRotatePara.fRotateZ);
	D3DXMatrixTranslation(&MatrixTranslate, sTransformPara.sTranslatePara.fTranslateX, sTransformPara.sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixScale * MatrixRotate * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	m_pSprite->SetTransform(&MatrixNative);
}

//-------------------------------------------------------------------------------------------------------------------------
// @Function:	 DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara)
// @Purpose: DirectSprite���Ʊ任����
// @Since: v1.00a
// @Para: D3DXMATRIX* pMatrix
// @Return: None
//-------------------------------------------------------------------------------------------------------------------------
void DIRECTSPRITE_CALLMODE DirectSprite::DirectSpriteDrawTransform(DirectSpriteDrawPara* sSpriteDrawPara, DirectSpriteTransformPara sTransformPara, int nNowY, int nPosY)
{
	DirectThreadSafe ThreadSafe(&m_cs, m_bThreadSafe);
	D3DXMATRIX Matrix;
	D3DXMATRIX MatrixNative;
	D3DXMATRIX MatrixScale;
	D3DXMATRIX MatrixRotate;
	D3DXMATRIX MatrixTranslate;
	D3DXMATRIX MatrixInvrsT;

	m_pSprite->GetTransform(&MatrixNative);
	Matrix = MatrixNative;
	D3DXMatrixScaling(&MatrixScale, sTransformPara.sScalePara.fScaleX, sTransformPara.sScalePara.fScaleY, 1.0f);
	D3DXMatrixRotationZ(&MatrixRotate, sTransformPara.sRotatePara.fRotateZ);
	D3DXMatrixTranslation(&MatrixTranslate, sTransformPara.sTranslatePara.fTranslateX, sTransformPara.sTranslatePara.fTranslateY, 0.0f);
	D3DXMatrixInverse(&MatrixInvrsT, NULL, &MatrixTranslate);
	Matrix = Matrix * MatrixInvrsT * MatrixScale * MatrixRotate * MatrixTranslate;
	m_pSprite->SetTransform(&Matrix);
	if (nNowY >= nPosY)
	{
		m_pSprite->Draw(m_pSpriteTexture, &(sSpriteDrawPara->SpriteRect), &(sSpriteDrawPara->SpriteCenter), &(sSpriteDrawPara->SpritePosition), sSpriteDrawPara->SpriteColor);
	}
	m_pSprite->SetTransform(&MatrixNative);
}