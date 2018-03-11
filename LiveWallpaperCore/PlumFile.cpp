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

//This Class is File Operation(�ļ�����)

//------------------------------------------------------------------
// @Function:	 CPlumFile()
// @Purpose: CPlumFile���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumFile::CPlumFile()
{
}

//------------------------------------------------------------------
// @Function:	 ~CPlumFile()
// @Purpose: CPlumFile��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumFile::~CPlumFile()
{
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetCurrentDirectoryA()
// @Purpose: CPlumFile��ȡ��ǰ�ļ�·��(Unicode)
// @Since: v1.00a
// @Para: char* pArr			//�����ַ
// @Para: DWORD dwSize			//���鳤��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetCurrentDirectoryA(char* pArr, DWORD dwSize)
{
	GetCurrentDirectoryA(dwSize, pArr);
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetCurrentDirectoryW()
// @Purpose: CPlumFile��ȡ��ǰ�ļ�·��(���ֽ�)
// @Since: v1.00a
// @Para: wchar_t* pArr			//�����ַ
// @Para: DWORD dwSize			//���鳤��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetCurrentDirectoryW(wchar_t* pArr, DWORD dwSize)
{
	GetCurrentDirectoryW(dwSize, pArr);
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetModuleFileNameA()
// @Purpose: CPlumFile��ȡ��ǰ�ļ�·��(Unicode)
// @Since: v1.00a
// @Para: char* pArr			//�����ַ
// @Para: DWORD dwSize			//���鳤��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetModuleFileNameA(char* pArr, DWORD dwSize)
{
	GetModuleFileNameA(NULL, pArr, dwSize);
}

//------------------------------------------------------------------
// @Function:	 PlumFileGetModuleFileNameW()
// @Purpose: CPlumFile��ȡ��ǰ�ļ�·��(���ֽ�)
// @Since: v1.00a
// @Para: wchar_t* pArr			//�����ַ
// @Para: DWORD dwSize			//���鳤��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileGetModuleFileNameW(wchar_t* pArr, DWORD dwSize)
{
	GetModuleFileNameW(NULL, pArr, dwSize);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCreateDirectoryA(const char* pSrc)
// @Purpose: CPlumFile�����ļ���
// @Since: v1.00a
// @Para: const char* pSrc			//�ļ���·��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCreateDirectoryA(const char* pSrc)
{
	CreateDirectoryA(pSrc, NULL);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCreateDirectoryW(const wchar_t* pSrc)
// @Purpose: CPlumFile�����ļ���
// @Since: v1.00a
// @Para: const wchar_t* pSrc		//�ļ���·��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCreateDirectoryW(const wchar_t* pSrc)
{
	CreateDirectoryW(pSrc, NULL);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCopyFileA(const char* pSrc, char* pDest, BOOL bCover)
// @Purpose: CPlumFile�����ļ���
// @Since: v1.00a
// @Para: const char* pSrc			//�ļ���·��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCopyFileA(const char* pSrc, const char* pDest, BOOL bNoCover)
{
	CopyFileA(pSrc, pDest, bNoCover);
}

//------------------------------------------------------------------
// @Function:	 PlumFileCopyFileW(const char* pSrc, char* pDest, BOOL bCover)
// @Purpose: CPlumFile�����ļ���
// @Since: v1.00a
// @Para: const char* pSrc			//�ļ���·��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileCopyFileW(const wchar_t* pSrc, const wchar_t* pDest, BOOL bNoCover)
{
	CopyFileW(pSrc, pDest, bNoCover);
}

//------------------------------------------------------------------
// @Function:	 PlumFileDeleteFileA(const char* pSrc)
// @Purpose: CPlumFile�����ļ���
// @Since: v1.00a
// @Para: const char* pSrc			//�ļ���·��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileDeleteFileA(const char* pSrc)
{
	DeleteFileA(pSrc);
}

//------------------------------------------------------------------
// @Function:	 PlumFileDeleteFileW(const char* pSrc)
// @Purpose: CPlumFile�����ļ���
// @Since: v1.00a
// @Para: const char* pSrc			//�ļ���·��
// @Return: None
//------------------------------------------------------------------
void CPlumFile::PlumFileDeleteFileW(const wchar_t* pSrc)
{
	DeleteFileW(pSrc);
}

//--------------------------------------------------------------------------------------------------
// @Function:	 PlumFileReadFileSaveInMemory(const char* pSrc, char** ppDest, DWORD* pSize)
// @Purpose: CPlumFile��ȡ�ļ�д���ڴ�
// @Since: v1.00a
// @Para: const char* pSrc			//��ȡ�ļ�·��(Unicode)
// @Para: char** ppDest				//�ڴ������ַָ��(����ָ��δ�����ڴ�)(��ʼ��ΪNULL)(��ס�ͷ��ڴ�!)
// @Para: DWORD* pSize				//�ڴ����鳤��ָ��(�ļ�����)
// @Return: bool(true: ����ִ�гɹ� false: ����ִ��ʧ��)
//--------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileReadFileSaveInMemory(const char* pSrc, char** ppDest, DWORD* pSize)
{
	HANDLE hFileSrc;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return false;//FIAL
	}

	DWORD dwFileSize = 0;
	DWORD dwArraySize = 0;
	DWORD dwRealRead = 0;

	//��ȡ�ļ���Ϣ
	dwFileSize = GetFileSize(hFileSrc, NULL);
	dwArraySize = dwFileSize;
	*pSize = dwArraySize;

	//����洢�ռ�
	*ppDest = new char[dwArraySize];
	memset(*ppDest, 0, dwArraySize*sizeof(char));

	//��ȡ�ļ������ڴ�����
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
// @Purpose: CPlumFile��ȡ�ļ�д���ڴ�
// @Since: v1.00a
// @Para: const wchar_t* pSrc		//��ȡ�ļ�·��(���ֽ�)
// @Para: char** ppDest				//�ڴ������ַָ��(����ָ��δ�����ڴ�)(��ʼ��ΪNULL)(��ס�ͷ��ڴ�!)
// @Para: DWORD* pSize				//�ڴ����鳤��ָ��(�ļ�����)
// @Return: bool(true: ����ִ�гɹ� false: ����ִ��ʧ��)
//--------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileReadFileSaveInMemory(const wchar_t* pSrc, char** ppDest, DWORD* pSize)
{
	HANDLE hFileSrc;

	//��Դ�ļ�
	hFileSrc = CreateFileW(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return false;//FIAL
	}

	DWORD dwFileSize = 0;
	DWORD dwArraySize = 0;
	DWORD dwRealRead = 0;

	//��ȡ�ļ���Ϣ
	dwFileSize = GetFileSize(hFileSrc, NULL);
	dwArraySize = dwFileSize;
	*pSize = dwArraySize;

	//����洢�ռ�
	*ppDest = new char[dwArraySize];
	memset(*ppDest, 0, dwArraySize*sizeof(char));

	//��ȡ�ļ������ڴ�����
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
// @Purpose: CPlumFile��ȡ�ļ�д���ڴ�
// @Since: v1.00a
// @Para: const char* pSrc			//�ڴ������ַ
// @Para: DWORD dwSize				//�ڴ����鳤��
// @Para: const char* pDest			//д���ļ�·��(Unicode)
// @Return: bool(true: ����ִ�гɹ� false: ����ִ��ʧ��)
//-----------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const char* pDest)
{
	HANDLE hFileDest;

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return false;//FAIL
	}

	DWORD dwRealWrite = 0;

	//��ȡ�ڴ�������Ϣд���ļ�
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
// @Purpose: CPlumFile��ȡ�ļ�д���ڴ�
// @Since: v1.00a
// @Para: const char* pSrc			//�ڴ������ַ
// @Para: DWORD dwSize				//�ڴ����鳤��
// @Para: const wchar_t* pDest		//д���ļ�·��(���ֽ�)
// @Return: bool(true: ����ִ�гɹ� false: ����ִ��ʧ��)
//-----------------------------------------------------------------------------------------------------
bool CPlumFile::PlumFileWriteMemorySaveInFile(const char* pSrc, DWORD dwSize, const wchar_t* pDest)
{
	HANDLE hFileDest;

	//��Ŀ���ļ�
	hFileDest = CreateFileW(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return false;//FAIL
	}

	DWORD dwRealWrite = 0;

	//��ȡ�ڴ�������Ϣд���ļ�
	WriteFile(hFileDest, pSrc, dwSize, &dwRealWrite, NULL);
	if (dwRealWrite == 0)
	{
		CloseHandle(hFileDest);
		return false;//FAIL
	}

	CloseHandle(hFileDest);
	return true;//OK
}