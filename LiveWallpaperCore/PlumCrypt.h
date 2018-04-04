/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumCrypt.h
* @brief	This Program is PlumCrypt DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2017-12-13	v1.00a	alopex	Create Project.
* @date		2017-12-17	v1.01a	alopex	Add Function EnCrypt/DeCrypt In Memory.
*/
#pragma once

#ifndef __PLUMCRYPT_H_
#define __PLUMCRYPT_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>

//Include Crypt Header File
#include "PlumCipherA.h"

//Macro Definition
#ifdef	PLUMPACK_EXPORTS
#define PLUMCRYPT_API	__declspec(dllexport)
#else
#define PLUMCRYPT_API	__declspec(dllimport)
#endif

#define CRYPTARRAYSIZE	1024

//Macro Point
#define SAFE_DELETE(Pointer)	{if(Pointer){delete(Pointer);(Pointer) = NULL;}}
#define SAFE_DELETE_ARRAY(Pointer) {if(Pointer){delete[](Pointer);(Pointer) = NULL;}}

//Struct Definition
typedef struct
{
	char cFileName[24];
	char cCodeAuthor[8];
	DWORD dwFileSize;
	DWORD dwCryptFileSize;
	DWORD dwLuckyNum[4];
} PlumFileInfo;

//Class Definition
class CPlumCrypt
{
private:
	char* m_pArray;			//内存资源数组地址
	DWORD m_dwArrSize;		//内存资源数组长度

public:
	CPlumCrypt();
	virtual ~CPlumCrypt();

	//访问
	virtual void PlumGetArray(char** ppArr, DWORD* pArrSize) const;

	//AES Crypt(AES加密)
	//File(文件)
	virtual void PlumEnCryptFileA(const char* pSrc, const char* pDest, DWORD* pLuckyArr);
	virtual void PlumDeCryptFileA(const char* pSrc, const char* pDest, DWORD* pLuckyArr);
	virtual void PlumEnCryptFileExA(const char* pSrc, const char* pDest, DWORD* pLuckyArr);
	virtual void PlumDeCryptFileExA(const char* pSrc, const char* pDest);
	virtual void PlumDeCryptFileNoExA(const char* pSrc, const char* pDest);
	//Memory(内存)
	virtual void PlumEnCryptFileExtractFromMemoryExA(const char* pDest, DWORD* pLuckyArr);
	virtual void PlumDeCryptFileStoreInMemoryExA(const char* pSrc);
	virtual void PlumDeCryptFileInMemoryStoreInFileExA(const void* pArray, PlumFileInfo sSrcArrayInfo, const char* pDest);
	virtual void PlumDeCryptFileInMemoryStoreInMemoryExA(const void* pArray, PlumFileInfo sSrcArrayInfo);
};

#endif