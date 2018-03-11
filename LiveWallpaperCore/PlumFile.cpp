/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumFile.cpp
* @brief	This Program is PlumFile DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2017-12-25	v1.00a	alopex	Create Project.
*/
#include "PlumFile.h"

//This Class is File Operation(文件操作)

//------------------------------------------------------------------
// @Function:	 CPlumFile()
// @Purpose: CPlumFile构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumFile::CPlumFile()
{
}

//------------------------------------------------------------------
// @Function:	 ~CPlumFile()
// @Purpose: CPlumFile析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumFile::~CPlumFile()
{
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetCurrentDirectoryA()
// @Purpose: CPlumFile获取当前文件路径(Unicode)
// @Since: v1.00a
// @Para: char* pArr			//数组地址
// @Para: DWORD dwSize			//数组长度
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetCurrentDirectoryA(char* pArr, DWORD dwSize)
{
	GetCurrentDirectoryA(dwSize, pArr);
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetCurrentDirectoryW()
// @Purpose: CPlumFile获取当前文件路径(多字节)
// @Since: v1.00a
// @Para: wchar_t* pArr			//数组地址
// @Para: DWORD dwSize			//数组长度
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetCurrentDirectoryW(wchar_t* pArr, DWORD dwSize)
{
	GetCurrentDirectoryW(dwSize, pArr);
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetModuleFileNameA()
// @Purpose: CPlumFile获取当前文件路径(Unicode)
// @Since: v1.00a
// @Para: char* pArr			//数组地址
// @Para: DWORD dwSize			//数组长度
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetModuleFileNameA(char* pArr, DWORD dwSize)
{
	GetModuleFileNameA(NULL, pArr, dwSize);
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetModuleFileNameW()
// @Purpose: CPlumFile获取当前文件路径(多字节)
// @Since: v1.00a
// @Para: wchar_t* pArr			//数组地址
// @Para: DWORD dwSize			//数组长度
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetModuleFileNameW(wchar_t* pArr, DWORD dwSize)
{
	GetModuleFileNameW(NULL, pArr, dwSize);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCreateDirectoryA(const char* pSrc)
// @Purpose: CPlumFile创建文件夹
// @Since: v1.00a
// @Para: const char* pSrc			//文件夹路径
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCreateDirectoryA(const char* pSrc)
{
	CreateDirectoryA(pSrc, NULL);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCreateDirectoryW(const wchar_t* pSrc)
// @Purpose: CPlumFile创建文件夹
// @Since: v1.00a
// @Para: const wchar_t* pSrc		//文件夹路径
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCreateDirectoryW(const wchar_t* pSrc)
{
	CreateDirectoryW(pSrc, NULL);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCopyFileA(const char* pSrc, char* pDest, BOOL bCover)
// @Purpose: CPlumFile创建文件夹
// @Since: v1.00a
// @Para: const char* pSrc			//文件夹路径
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCopyFileA(const char* pSrc, const char* pDest, BOOL bNoCover)
{
	CopyFileA(pSrc, pDest, bNoCover);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCopyFileW(const char* pSrc, char* pDest, BOOL bCover)
// @Purpose: CPlumFile创建文件夹
// @Since: v1.00a
// @Para: const char* pSrc			//文件夹路径
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCopyFileW(const wchar_t* pSrc, const wchar_t* pDest, BOOL bNoCover)
{
	CopyFileW(pSrc, pDest, bNoCover);
}

//------------------------------------------------------------------
// @Function:	 PlumFileDeleteFileA(const char* pSrc)
// @Purpose: CPlumFile创建文件夹
// @Since: v1.00a
// @Para: const char* pSrc			//文件夹路径
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileDeleteFileA(const char* pSrc)
{
	DeleteFileA(pSrc);
}

//------------------------------------------------------------------
// @Function:	 PlumFileDeleteFileW(const char* pSrc)
// @Purpose: CPlumFile创建文件夹
// @Since: v1.00a
// @Para: const char* pSrc			//文件夹路径
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileDeleteFileW(const wchar_t* pSrc)
{
	DeleteFileW(pSrc);
}

//--------------------------------------------------------------------------------------------------
// @Function:	 PlumFileReadFileSaveInMemory(const char* pSrc, char** ppDest, DWORD* pSize)
// @Purpose: CPlumFile读取文件写入内存
// @Since: v1.00a
// @Para: const char* pSrc			//读取文件路径(Unicode)
// @Para: char** ppDest				//内存数组地址指针(传入指针未申请内存)(初始化为NULL)(记住释放内存!)
// @Para: DWORD* pSize				//内存数组长度指针(文件长度)
// @Return: bool(true: 函数执行成功 false: 函数执行失败)
//--------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileReadFileSaveInMemory(const char* pSrc, char** ppDest, DWORD* pSize)
{
	HANDLE hFileSrc;

	//打开源文件
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return false;//FIAL
	}

	DWORD dwFileSize = 0;
	DWORD dwArraySize = 0;
	DWORD dwRealRead = 0;

	//获取文件信息
	dwFileSize = GetFileSize(hFileSrc, NULL);
	dwArraySize = dwFileSize;
	*pSize = dwArraySize;

	//申请存储空间
	*ppDest = new char[dwArraySize];
	memset(*ppDest, 0, dwArraySize*sizeof(char));

	//读取文件存入内存数组
	ReadFile(hFileSrc, *ppDest, dwArraySize, &dwRealRead, NULL);
	if (dwRealRead == 0)
	{
		CloseHandle(hFileSrc);
		SAFE_DELETE_ARRAY(pSize);
		return false;//FIAL
	}

	CloseHandle(hFileSrc);
	return true;//OK
}

//--------------------------------------------------------------------------------------------------
// @Function:	 PlumFileReadFileSaveInMemory(const wchar_t* pSrc, char** ppDest, DWORD* pSize)
// @Purpose: CPlumFile读取文件写入内存
// @Since: v1.00a
// @Para: const wchar_t* pSrc		//读取文件路径(多字节)
// @Para: char** ppDest				//内存数组地址指针(传入指针未申请内存)(初始化为NULL)(记住释放内存!)
// @Para: DWORD* pSize				//内存数组长度指针(文件长度)
// @Return: bool(true: 函数执行成功 false: 函数执行失败)
//--------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileReadFileSaveInMemory(const wchar_t* pSrc, char** ppDest, DWORD* pSize)
{
	HANDLE hFileSrc;

	//打开源文件
	hFileSrc = CreateFileW(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return false;//FIAL
	}

	DWORD dwFileSize = 0;
	DWORD dwArraySize = 0;
	DWORD dwRealRead = 0;

	//获取文件信息
	dwFileSize = GetFileSize(hFileSrc, NULL);
	dwArraySize = dwFileSize;
	*pSize = dwArraySize;

	//申请存储空间
	*ppDest = new char[dwArraySize];
	memset(*ppDest, 0, dwArraySize*sizeof(char));

	//读取文件存入内存数组
	ReadFile(hFileSrc, *ppDest, dwArraySize, &dwRealRead, NULL);
	if (dwRealRead == 0)
	{
		CloseHandle(hFileSrc);
		SAFE_DELETE_ARRAY(pSize);
		return false;//FIAL
	}

	CloseHandle(hFileSrc);
	return true;//OK
}

//----------------------------------------------------------------------------------------------------
// @Function:	 PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const char* pDest)
// @Purpose: CPlumFile读取文件写入内存
// @Since: v1.00a
// @Para: const char* pSrc			//内存数组地址
// @Para: DWORD dwSize				//内存数组长度
// @Para: const char* pDest			//写入文件路径(Unicode)
// @Return: bool(true: 函数执行成功 false: 函数执行失败)
//-----------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const char* pDest)
{
	HANDLE hFileDest;

	//打开目标文件
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return false;//FAIL
	}

	DWORD dwRealWrite = 0;

	//读取内存数组信息写入文件
	WriteFile(hFileDest, pSrc, dwSize, &dwRealWrite, NULL);
	if (dwRealWrite == 0)
	{
		CloseHandle(hFileDest);
		return false;//FAIL
	}

	CloseHandle(hFileDest);
	return true;//OK
}

//----------------------------------------------------------------------------------------------------
// @Function:	 PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const wchar_t* pDest)
// @Purpose: CPlumFile读取文件写入内存
// @Since: v1.00a
// @Para: const char* pSrc			//内存数组地址
// @Para: DWORD dwSize				//内存数组长度
// @Para: const wchar_t* pDest		//写入文件路径(多字节)
// @Return: bool(true: 函数执行成功 false: 函数执行失败)
//-----------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const wchar_t* pDest)
{
	HANDLE hFileDest;

	//打开目标文件
	hFileDest = CreateFileW(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return false;//FAIL
	}

	DWORD dwRealWrite = 0;

	//读取内存数组信息写入文件
	WriteFile(hFileDest, pSrc, dwSize, &dwRealWrite, NULL);
	if (dwRealWrite == 0)
	{
		CloseHandle(hFileDest);
		return false;//FAIL
	}

	CloseHandle(hFileDest);
	return true;//OK
}