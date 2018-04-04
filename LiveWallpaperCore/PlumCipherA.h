/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumCipherA.h
* @brief	This Program is PlumCipherA DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-12-13	v1.00a	alopex	Create Project
*/
#pragma once

#ifndef __PLUMCIPHERA_H_
#define __PLUMCIPHERA_H_

//Include Windows Header File
#include <Windows.h>

//Macro Definition
#ifdef	PLUMPACK_EXPORTS
#define PLUMCRYPT_API	__declspec(dllexport)
#else
#define PLUMCRYPT_API	__declspec(dllimport)
#endif

//Class Definition
class CPlumCipherA
{
private:
	unsigned char m_cSBox[256];
	unsigned char m_cInvSBox[256];
	unsigned char m_cExMatrix[11][4][4];

public:
	CPlumCipherA();														//构造
	~CPlumCipherA();													//析构

	CPlumCipherA(unsigned char* Key);									//构造

	void KeyExMatrix(unsigned char* Key, unsigned char Ex[][4][4]);
	unsigned char FFMul(unsigned char Var1, unsigned char Var2);

	void SubBytes(unsigned char* pState);
	void ShiftRows(unsigned char State[][4]);
	void MixColumns(unsigned char State[][4]);
	void AddRoundKey(unsigned char* pState, unsigned char* pK);
	
	void InvSubBytes(unsigned char* pState);
	void InvShiftRows(unsigned char State[][4]);
	void InvMixColumns(unsigned char State[][4]);
	
	void EnCipher(const unsigned char* pSrc, unsigned char* pDest);		//加密数组Array[4][4]	
	void DeCipher(const unsigned char* pSrc, unsigned char* pDest);		//解密数组Array[4][4]
	void EnCrypt(const void* pSrc, void* pDest, int nLen);				//加密数组
	void DeCrypt(const void* pSrc, void* pDest, int nLen);				//解密数组
};

#endif