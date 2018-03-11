/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumFile.h
* @brief	This Program is PlumFile DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2017-12-25	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __PLUMFILE_H_
#define __PLUMFILE_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>

//Macro Definition
#ifdef	PLUMFILE_EXPORTS
#define PLUMFILE_API	__declspec(dllexport)
#else
#define PLUMFILE_API	__declspec(dllimport)
#endif

//Macro Point
#define SAFE_DELETE(Pointer)	{if(Pointer){delete(Pointer);(Pointer) = NULL;}}
#define SAFE_DELETE_ARRAY(Pointer) {if(Pointer){delete[](Pointer);(Pointer) = NULL;}}

//Class Definition
class CPlumFile
{
private:
	

public:
	CPlumFile();
	virtual ~CPlumFile();

	//访问
	//文件路径
	virtual void PlumFileGetCurrentDirectoryA(char* pArr, DWORD dwSize);
	virtual void PlumFileGetCurrentDirectoryW(wchar_t* pArr, DWORD dwSize);
	virtual void PlumFileGetModuleFileNameA(char* pArr, DWORD dwSize);
	virtual void PlumFileGetModuleFileNameW(wchar_t* pArr, DWORD dwSize);

	//文件夹路径
	virtual void PlumFileCreateDirectoryA(const char* pSrc);
	virtual void PlumFileCreateDirectoryW(const wchar_t* pSrc);

	//文件操作
	virtual void PlumFileCopyFileA(const char* pSrc, const char* pDest, BOOL bNoCover = TRUE);
	virtual void PlumFileCopyFileW(const wchar_t* pSrc, const wchar_t* pDest, BOOL bNoCover = TRUE);
	virtual void PlumFileDeleteFileA(const char* pSrc);
	virtual void PlumFileDeleteFileW(const wchar_t* pSrc);

	//文件读写
	virtual bool PlumFileReadFileSaveInMemory(const char* pSrc, char** ppDest, DWORD* pSize);
	virtual bool PlumFileReadFileSaveInMemory(const wchar_t* pSrc, char** ppDest, DWORD* pSize);
	virtual bool PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const char* pDest);
	virtual bool PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const wchar_t* pDest);
};

#endif