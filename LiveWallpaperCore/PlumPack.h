/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumPack.h
* @brief	This Program is PlumPack DLL Project.
* @author	Alopex/Helium
* @version	v1.02a
* @date		2017-12-16	v1.00a	alopex	Create Project.
* @date		2017-12-23	v1.01a	alopex	Add Function UnPack to Memory.
* @date		2018-1-16	v1.02a	alopex	Add For PackerMaker Function.
*/
#pragma once

#ifndef __PLUMPACK_H_
#define __PLUMPACK_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>

//Include Crypt File
#include "PlumCipherA.h"
#include "PlumCrypt.h"

//Macro Definition
#ifdef	PLUMPACK_EXPORTS
#define PLUMPACK_API	__declspec(dllexport)
#else
#define PLUMPACK_API	__declspec(dllimport)
#endif

//Struct Definition
typedef struct
{
	char cFileName[24];
	char cCodeAuthor[8];
	DWORD dwFileAllNum;
	DWORD dwFileAllSize;
} PlumPackInfo;

//Class Definition
class CPlumPack
{
private:
	CPlumCrypt* m_pCryptArr;
	int m_nArrSize;


public:
	CPlumPack();
	virtual ~CPlumPack();

	//访问
	virtual void PlumGetArray(CPlumCrypt** ppCryptArr, int* pArrSize) const;

	//AES Pack(AES封包/解包)
	virtual void PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest);
	virtual void PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr);
	virtual void PlumUnPackFileA(const char* pSrc, const char* pDest);
	virtual void PlumUnPackFileA(const char* pSrc);

	//AES Packer(PackerMaker)
	virtual void PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, int* pCount);
	virtual void PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr, int* pCount);
	virtual void PlumUnPackFilePackerA(const char* pSrc, const char* pDest, int* pSize, int* pCount, char* pUnpack, int nSize);
};

#endif