/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumCrypt.cpp
* @brief	This Program is PlumCrypt DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2017-12-13	v1.00a	alopex	Create Project.
* @date		2017-12-17	v1.01a	alopex	Add Function EnCrypt/DeCrypt In Memory.
*/
#include "PlumCrypt.h"

//This Class is File EnCrypt/DeCrypt(�ļ�����/����)

//------------------------------------------------------------------
// @Function:	 CPlumCrypt()
// @Purpose: CPlumCrypt���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumCrypt::CPlumCrypt()
{
	m_pArray = NULL;
	m_dwArrSize = 0;
}

//------------------------------------------------------------------
// @Function:	 ~CPlumCrypt()
// @Purpose: CPlumCrypt��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumCrypt::~CPlumCrypt()
{
	SAFE_DELETE_ARRAY(m_pArray);
}

//------------------------------------------------------------------
// @Function:	 PlumGetArray(char** ppArr, DWORD* pArrSize) const
// @Purpose: PlumCryptFileA�����ļ�
// @Since: v1.00a
// @Para: char** ppArr			//�����ַָ��
// @Para: DWORD* pArrSize		//���鳤��ָ��
// @Return: None
//------------------------------------------------------------------
void CPlumCrypt::PlumGetArray(char** ppArr, DWORD* pArrSize) const
{
	*ppArr = m_pArray;
	*pArrSize = m_dwArrSize;
}

//------------------------------------------------------------------
// @Function:	 PlumEnCryptFileA()
// @Purpose: PlumCryptFileA�����ļ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumCrypt::PlumEnCryptFileA(const char* pSrc, const char* pDest, DWORD* pLuckyArr)
{
	FILE* fin;
	FILE* fou;

	fopen_s(&fin, pSrc, "r+b");
	if (fin == NULL)
	{
		return;
	}

	fopen_s(&fou, pDest, "w+b");
	if (fou == NULL)
	{
		return;
	}

	CPlumCipherA* pCode = NULL;
	unsigned char KeyArr[16];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			KeyArr[4 * i + j] = (*(pLuckyArr + i) >> (8 * j)) & 0xff;
		}
	}

	pCode = new CPlumCipherA(KeyArr);

	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	int nReadSize = 0;
	int nWriteSize = 0;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		nReadSize = fread((void*)pSrcArr, sizeof(unsigned char), nSrcSize, fin);
		if (nReadSize == 0) break;
		if (nReadSize != nSrcSize)
		{
			while (nReadSize % 16)
			{
				++nReadSize;
			}
		}

		pCode->EnCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);

		nWriteSize = fwrite((void*)pDestArr, sizeof(unsigned char), nReadSize, fou);
		if (nWriteSize == 0) break;
	}

	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	fclose(fou);
	fclose(fin);
}

//------------------------------------------------------------------
// @Function:	 PlumDeCryptFileA()
// @Purpose: PlumCryptFileA�����ļ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumCrypt::PlumDeCryptFileA(const char* pSrc, const char* pDest, DWORD* pLuckyArr)
{
	FILE* fin;
	FILE* fou;

	fopen_s(&fin, pSrc, "r+b");
	if (fin == NULL)
	{
		return;
	}

	fopen_s(&fou, pDest, "w+b");
	if (fou == NULL)
	{
		return;
	}

	CPlumCipherA* pCode = NULL;
	unsigned char KeyArr[16];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			KeyArr[4 * i + j] = (*(pLuckyArr + i) >> (8 * j)) & 0xff;
		}
	}

	pCode = new CPlumCipherA(KeyArr);

	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	int nReadSize = 0;
	int nWriteSize = 0;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		nReadSize = fread((void*)pSrcArr, sizeof(unsigned char), nSrcSize, fin);
		if (nReadSize == 0) break;

		pCode->DeCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);

		nWriteSize = fwrite((void*)pDestArr, sizeof(unsigned char), nReadSize, fou);
		if (nWriteSize == 0) break;
	}

	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	fclose(fou);
	fclose(fin);
}

//------------------------------------------------------------------
// @Function:	 PlumEnCryptFileExA()
// @Purpose: PlumCryptFileA�����ļ�(Ex)(msg)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumCrypt::PlumEnCryptFileExA(const char* pSrc, const char* pDest, DWORD* pLuckyArr)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//�����ļ�
	char* pTemp;
	char* pMsg;
	char* pSrcName;
	int nCount;

	pTemp = (char*)pDest;
	nCount = strlen(pTemp);
	pMsg = (char*)malloc((nCount + 1)*sizeof(char));
	strcpy_s(pMsg, (nCount + 1), pTemp);
	pTemp = strrchr(pMsg, '.');
	*pTemp = '.';
	*(pTemp + 1) = 'm';
	*(pTemp + 2) = 's';
	*(pTemp + 3) = 'g';
	*(pTemp + 4) = '\0';

	pTemp = strrchr((char*)pSrc, '\\');
	nCount = strlen(++pTemp);
	pSrcName = (char*)malloc((nCount + 1)*sizeof(char));
	strcpy_s(pSrcName, (nCount + 1), pTemp);

	//���ļ���Ϣ
	hFileMsg = CreateFileA(pMsg, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileMsg == INVALID_HANDLE_VALUE)
	{
		if (pMsg) free(pMsg);
		if (pSrcName) free(pSrcName);
		CloseHandle(hFileMsg);
		return;
	}

	CPlumCipherA* pCode = NULL;
	unsigned char KeyArr[16];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			KeyArr[4 * i + j] = (*(pLuckyArr + i) >> (8 * j)) & 0xff;
		}
	}

	pCode = new CPlumCipherA(KeyArr);

	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	DWORD dwRealRead = 0;
	DWORD dwRealWrite = 0;
	DWORD dwFileSize = 0;
	DWORD dwCryptFileSize = 0;

	dwFileSize = GetFileSize(hFileSrc, NULL);//��ȡ�ļ�����

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
		if (dwRealRead == 0) break;
		if (dwRealRead != nSrcSize)
		{
			while (dwRealRead % 16)
			{
				++dwRealRead;
			}
		}

		pCode->EnCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);
		dwCryptFileSize += dwRealRead;

		WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
		if (dwRealWrite == 0) break;
	}

	//д��Msg
	int i = 0;
	PlumFileInfo sMsg;
	DWORD dwMsgWrite;

	memset(&sMsg, 0, sizeof(sMsg));
	for (i = 0, pTemp = pSrcName; i < sizeof(sMsg.cFileName) && *pTemp != '\0'; ++i, ++pTemp)
	{
		*(sMsg.cFileName + i) = *pTemp;
	}
	memcpy((void*)(sMsg.cCodeAuthor), "alopex", sizeof("alopex"));
	memcpy((void*)(sMsg.dwLuckyNum), pLuckyArr, sizeof(sMsg.dwLuckyNum));
	sMsg.dwFileSize = dwFileSize;
	sMsg.dwCryptFileSize = dwCryptFileSize;

	WriteFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

	if (pMsg) free(pMsg);
	if (pSrcName) free(pSrcName);
	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	CloseHandle(hFileMsg);
	CloseHandle(hFileDest);
	CloseHandle(hFileSrc);
}

//------------------------------------------------------------------
// @Function:	 PlumDeCryptFileExA()
// @Purpose: PlumCryptFileA�����ļ�(Ex)(msg)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumCrypt::PlumDeCryptFileExA(const char* pSrc, const char* pDest)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//�����ļ�
	char* pTemp;
	char* pMsg;
	int nCount;

	pTemp = (char*)pSrc;
	nCount = strlen(pTemp);
	pMsg = (char*)malloc((nCount + 1)*sizeof(char));
	strcpy_s(pMsg, (nCount + 1), pTemp);
	pTemp = strrchr(pMsg, '.');
	*pTemp = '.';
	*(pTemp + 1) = 'm';
	*(pTemp + 2) = 's';
	*(pTemp + 3) = 'g';
	*(pTemp + 4) = '\0';

	//���ļ���Ϣ
	hFileMsg = CreateFileA(pMsg, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileMsg == INVALID_HANDLE_VALUE)
	{
		if (pMsg) free(pMsg);
		CloseHandle(hFileMsg);
		return;
	}

	//����Msg
	PlumFileInfo sMsg;
	DWORD dwMsgRead;

	ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);

	CPlumCipherA* pCode = new CPlumCipherA((unsigned char*)(sMsg.dwLuckyNum));
	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	DWORD dwRealRead = 0;
	DWORD dwRealWrite = 0;
	DWORD dwWriteAllCount = 0;
	DWORD dwWriteLastSize = 0;
	DWORD dwWriteCount = 0;

	dwWriteAllCount = sMsg.dwFileSize / nSrcSize + 1;
	dwWriteLastSize = sMsg.dwFileSize % nSrcSize;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
		if (dwRealRead == 0) break;

		pCode->DeCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);

		++dwWriteCount;
		if (dwWriteCount == dwWriteAllCount)
		{
			dwRealRead = dwWriteLastSize;
		}

		WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
		if (dwRealWrite == 0) break;
	}

	if (pMsg) free(pMsg);
	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	CloseHandle(hFileMsg);
	CloseHandle(hFileDest);
	CloseHandle(hFileSrc);
}

//------------------------------------------------------------------
// @Function:	 PlumDeCryptFileExA()
// @Purpose: PlumCryptFileA�����ļ�(Ex)(msg)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumCrypt::PlumDeCryptFileNoExA(const char* pSrc, const char* pDest)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//�����ļ�
	char* pTemp;
	char* pMsg;
	int nCount;

	pTemp = (char*)pSrc;
	nCount = strlen(pTemp);
	pMsg = (char*)malloc((nCount + 1)*sizeof(char));
	strcpy_s(pMsg, (nCount + 1), pTemp);
	pTemp = strrchr(pMsg, '.');
	*pTemp = '.';
	*(pTemp + 1) = 'm';
	*(pTemp + 2) = 's';
	*(pTemp + 3) = 'g';
	*(pTemp + 4) = '\0';

	//���ļ���Ϣ
	hFileMsg = CreateFileA(pMsg, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileMsg == INVALID_HANDLE_VALUE)
	{
		if (pMsg) free(pMsg);
		CloseHandle(hFileMsg);
		return;
	}

	//����Msg
	PlumFileInfo sMsg;
	DWORD dwMsgRead;

	ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
	
	char* pArr = NULL;
	int nDestCount = 0;
	int nMsgCount = 0;
	int i = 0;

	pTemp = (char*)pDest;
	nDestCount = strlen(pTemp);
	nMsgCount = strlen(sMsg.cFileName);
	nCount = nDestCount + nMsgCount;
	pArr = (char*)malloc((nCount + 2)*sizeof(char));
	for (i = 0; i < nDestCount; ++i)
	{
		*(pArr + i) = *(pTemp + i);
	}
	*(pArr + i) = '\\';
	for (int j = 0; j < nMsgCount; ++j)
	{
		*(pArr + i + 1 + j) = *(sMsg.cFileName + j);
	}
	*(pArr + nCount + 1) = '\0';

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pArr, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		if (pArr) free(pArr);
		CloseHandle(hFileDest);
		return;
	}

	CPlumCipherA* pCode = new CPlumCipherA((unsigned char*)(sMsg.dwLuckyNum));
	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	DWORD dwRealRead = 0;
	DWORD dwRealWrite = 0;
	DWORD dwWriteAllCount = 0;
	DWORD dwWriteLastSize = 0;
	DWORD dwWriteCount = 0;

	dwWriteAllCount = sMsg.dwFileSize / nSrcSize + 1;
	dwWriteLastSize = sMsg.dwFileSize % nSrcSize;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
		if (dwRealRead == 0) break;

		pCode->DeCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);

		++dwWriteCount;
		if (dwWriteCount == dwWriteAllCount)
		{
			dwRealRead = dwWriteLastSize;
		}

		WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
		if (dwRealWrite == 0) break;
	}

	if (pArr) free(pArr);
	if (pMsg) free(pMsg);
	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	CloseHandle(hFileMsg);
	CloseHandle(hFileDest);
	CloseHandle(hFileSrc);
}

//-------------------------------------------------------------------------------------------------
// @Function:	 PlumEnCryptFileExtractFromMemoryExA(const char* pDest, DWORD* pLuckyArr)
// @Purpose: PlumEnCryptFileExtractFromMemoryExA�����ڴ�����洢���ļ�Ex(Msg)
// @Since: v1.00a
// @Para: const char* pDest			//�����ļ���ַ
// @Para: DWORD* pLuckyArr			//��������ָ��
// @Return: None
//-------------------------------------------------------------------------------------------------
void CPlumCrypt::PlumEnCryptFileExtractFromMemoryExA(const char* pDest, DWORD* pLuckyArr)
{
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//�����ļ�
	char* pTemp;
	char* pMsg;
	char* pSrcName;
	int nCount;

	pTemp = (char*)pDest;
	nCount = strlen(pTemp);
	pMsg = (char*)malloc((nCount + 1)*sizeof(char));
	strcpy_s(pMsg, (nCount + 1), pTemp);
	pTemp = strrchr(pMsg, '.');
	*pTemp = '.';
	*(pTemp + 1) = 'm';
	*(pTemp + 2) = 's';
	*(pTemp + 3) = 'g';
	*(pTemp + 4) = '\0';

	pTemp = strrchr((char*)pDest, '\\');
	nCount = strlen(++pTemp);
	pSrcName = (char*)malloc((nCount + 1)*sizeof(char));
	strcpy_s(pSrcName, (nCount + 1), pTemp);

	//���ļ���Ϣ
	hFileMsg = CreateFileA(pMsg, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileMsg == INVALID_HANDLE_VALUE)
	{
		if (pMsg) free(pMsg);
		if (pSrcName) free(pSrcName);
		CloseHandle(hFileMsg);
		return;
	}

	CPlumCipherA* pCode = NULL;
	unsigned char KeyArr[16];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			KeyArr[4 * i + j] = (*(pLuckyArr + i) >> (8 * j)) & 0xff;
		}
	}

	pCode = new CPlumCipherA(KeyArr);

	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	DWORD dwRealRead = 0;
	DWORD dwRealWrite = 0;
	DWORD dwFileSize = 0;
	DWORD dwCryptFileSize = 0;
	DWORD dwReadAllCount = 0;
	DWORD dwReadLastSize = 0;
	DWORD dwReadCount = 0;
	DWORD dwReadOffSet = 0;

	dwFileSize = m_dwArrSize;//��ȡ�ļ�����

	dwReadAllCount = dwFileSize / nSrcSize + 1;
	dwReadLastSize = dwFileSize % nSrcSize;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		++dwReadCount;
		if (dwReadCount < dwReadAllCount)
		{
			dwRealRead = nSrcSize;
		}
		else if (dwReadCount == dwReadAllCount)
		{
			dwRealRead = dwReadLastSize;
		}
		else
		{
			break;
		}

		memcpy(pSrcArr, (m_pArray + dwReadOffSet), dwRealRead);
		dwReadOffSet += dwRealRead;

		if (dwRealRead != nSrcSize)
		{
			while (dwRealRead % 16)
			{
				++dwRealRead;
			}
		}

		pCode->EnCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);
		dwCryptFileSize += dwRealRead;

		WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
		if (dwRealWrite == 0) break;
	}

	//д��Msg
	int i = 0;
	PlumFileInfo sMsg;
	DWORD dwMsgWrite;

	memset(&sMsg, 0, sizeof(sMsg));
	for (i = 0, pTemp = pSrcName; i < sizeof(sMsg.cFileName) && *pTemp != '\0'; ++i, ++pTemp)
	{
		*(sMsg.cFileName + i) = *pTemp;
	}
	memcpy((void*)(sMsg.cCodeAuthor), "alopex", sizeof("alopex"));
	memcpy((void*)(sMsg.dwLuckyNum), pLuckyArr, sizeof(sMsg.dwLuckyNum));
	sMsg.dwFileSize = dwFileSize;
	sMsg.dwCryptFileSize = dwCryptFileSize;

	WriteFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

	if (pMsg) free(pMsg);
	if (pSrcName) free(pSrcName);
	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	CloseHandle(hFileMsg);
	CloseHandle(hFileDest);
}

//-------------------------------------------------------------------------------------------------
// @Function:	 PlumDeCryptFileStoreInMemoryExA(const char* pSrc)
// @Purpose: PlumDeCryptStoreInMemoryExA�����ļ��洢���ڴ�Ex(Msg)
// @Since: v1.00a
// @Para: const char* pSrc			//�����ļ���ַ
// @Return: None
//-------------------------------------------------------------------------------------------------
void CPlumCrypt::PlumDeCryptFileStoreInMemoryExA(const char* pSrc)
{
	HANDLE hFileSrc;
	HANDLE hFileMsg;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//�����ļ�
	char* pTemp;
	char* pMsg;
	int nCount;

	pTemp = (char*)pSrc;
	nCount = strlen(pTemp);
	pMsg = (char*)malloc((nCount + 1)*sizeof(char));
	strcpy_s(pMsg, (nCount + 1), pTemp);
	pTemp = strrchr(pMsg, '.');
	*pTemp = '.';
	*(pTemp + 1) = 'm';
	*(pTemp + 2) = 's';
	*(pTemp + 3) = 'g';
	*(pTemp + 4) = '\0';

	//���ļ���Ϣ
	hFileMsg = CreateFileA(pMsg, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileMsg == INVALID_HANDLE_VALUE)
	{
		if (pMsg) free(pMsg);
		CloseHandle(hFileMsg);
		return;
	}

	//����Msg
	PlumFileInfo sMsg;
	DWORD dwMsgRead;

	ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);

	SAFE_DELETE_ARRAY(m_pArray);
	m_dwArrSize = sMsg.dwFileSize;
	m_pArray = new char[sMsg.dwFileSize];

	CPlumCipherA* pCode = new CPlumCipherA((unsigned char*)(sMsg.dwLuckyNum));
	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	DWORD dwRealRead = 0;
	DWORD dwWriteAllCount = 0;
	DWORD dwWriteLastSize = 0;
	DWORD dwWriteCount = 0;
	DWORD dwWriteOffSet = 0;

	dwWriteAllCount = sMsg.dwFileSize / nSrcSize + 1;
	dwWriteLastSize = sMsg.dwFileSize % nSrcSize;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));
	
	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
		if (dwRealRead == 0) break;

		pCode->DeCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);

		++dwWriteCount;
		if (dwWriteCount == dwWriteAllCount)
		{
			dwRealRead = dwWriteLastSize;
		}

		memcpy((m_pArray + dwWriteOffSet), pDestArr, dwRealRead);
		dwWriteOffSet += dwRealRead;
	}

	if (pMsg) free(pMsg);
	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	CloseHandle(hFileMsg);
	CloseHandle(hFileSrc);
}

//-------------------------------------------------------------------------------------------------
// @Function:	 PlumDeCryptFileInMemoryStoreInFileExA(const char* pSrc)
// @Purpose: PlumDeCryptStoreInMemoryExA�����ڴ�����洢���ڴ�Ex(Msg)
// @Since: v1.00a
// @Para: const void* pSrcArr				//�ڴ������ַ
// @Para: DWORD dwArrSize					//�ڴ����鳤��
// @Para: PlumFileInfo sSrcArrInfo			//�ļ���Ϣ�ṹ��
// @Para: const char* pDest					//Ŀ���ļ���ַ
// @Return: None
//-------------------------------------------------------------------------------------------------
void CPlumCrypt::PlumDeCryptFileInMemoryStoreInFileExA(const void* pArray, PlumFileInfo sSrcArrayInfo, const char* pDest)
{
	HANDLE hFileDest;

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	CPlumCipherA* pCode = new CPlumCipherA((unsigned char*)(sSrcArrayInfo.dwLuckyNum));
	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	DWORD dwRealRead = 0;
	DWORD dwRealWrite = 0;
	DWORD dwWriteAllCount = 0;
	DWORD dwReadLastSize = 0;
	DWORD dwWriteLastSize = 0;
	DWORD dwWriteCount = 0;
	DWORD dwWriteOffSet = 0;
	DWORD dwReadCount = 0;
	DWORD dwReadOffSet = 0;

	m_dwArrSize = sSrcArrayInfo.dwFileSize;

	dwWriteAllCount = sSrcArrayInfo.dwFileSize / nSrcSize + 1;
	dwWriteLastSize = sSrcArrayInfo.dwFileSize % nSrcSize;
	dwReadLastSize = sSrcArrayInfo.dwCryptFileSize % nSrcSize;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		++dwReadCount;
		if (dwReadCount < dwWriteAllCount)
		{
			dwRealRead = nSrcSize;
		}
		else if (dwReadCount == dwWriteAllCount)
		{
			dwRealRead = dwReadLastSize;
		}
		else
		{
			break;
		}

		memcpy(pSrcArr, ((const char*)pArray + dwReadOffSet), dwRealRead);
		dwReadOffSet += dwRealRead;

		pCode->DeCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);

		++dwWriteCount;
		if (dwWriteCount == dwWriteAllCount)
		{
			dwRealRead = dwWriteLastSize;
		}

		WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
		if (dwRealWrite == 0) break;
		dwWriteOffSet += dwRealRead;
	}

	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;

	CloseHandle(hFileDest);
}

//-------------------------------------------------------------------------------------------------
// @Function:	 PlumDeCryptFileStoreInMemoryExA(const char* pSrc)
// @Purpose: PlumDeCryptStoreInMemoryExA�����ڴ�����洢���ڴ�Ex(Msg)
// @Since: v1.00a
// @Para: const void* pSrcArr				//�ڴ������ַ
// @Para: DWORD dwArrSize					//�ڴ����鳤��
// @Para: PlumFileInfo sSrcArrInfo			//�ļ���Ϣ�ṹ��
// @Return: None
//-------------------------------------------------------------------------------------------------
void CPlumCrypt::PlumDeCryptFileInMemoryStoreInMemoryExA(const void* pArray, PlumFileInfo sSrcArrayInfo)
{
	CPlumCipherA* pCode = new CPlumCipherA((unsigned char*)(sSrcArrayInfo.dwLuckyNum));
	unsigned char* pSrcArr = NULL;
	unsigned char* pDestArr = NULL;
	int nSrcSize = CRYPTARRAYSIZE;
	int nDestSize = CRYPTARRAYSIZE;
	DWORD dwRealRead = 0;
	DWORD dwWriteAllCount = 0;
	DWORD dwReadLastSize = 0;
	DWORD dwWriteLastSize = 0;
	DWORD dwWriteCount = 0;
	DWORD dwWriteOffSet = 0;
	DWORD dwReadCount = 0;
	DWORD dwReadOffSet = 0;

	SAFE_DELETE_ARRAY(m_pArray);
	m_dwArrSize = sSrcArrayInfo.dwFileSize;
	m_pArray = new char[m_dwArrSize];

	dwWriteAllCount = sSrcArrayInfo.dwFileSize / nSrcSize + 1;
	dwWriteLastSize = sSrcArrayInfo.dwFileSize % nSrcSize;
	dwReadLastSize = sSrcArrayInfo.dwCryptFileSize % nSrcSize;

	pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
	pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

	for (;;)
	{
		memset(pSrcArr, 0, nSrcSize);
		memset(pDestArr, 0, nDestSize);

		++dwReadCount;
		if (dwReadCount < dwWriteAllCount)
		{
			dwRealRead = nSrcSize;
		}
		else if (dwReadCount == dwWriteAllCount)
		{
			dwRealRead = dwReadLastSize;
		}
		else
		{
			break;
		}

		memcpy(pSrcArr, ((const char*)pArray + dwReadOffSet), dwRealRead);
		dwReadOffSet += dwRealRead;

		pCode->DeCrypt((void*)pSrcArr, (void*)pDestArr, nSrcSize);

		++dwWriteCount;
		if (dwWriteCount == dwWriteAllCount)
		{
			dwRealRead = dwWriteLastSize;
		}

		memcpy((m_pArray + dwWriteOffSet), pDestArr, dwRealRead);
		dwWriteOffSet += dwRealRead;
	}

	if (pSrcArr) free(pSrcArr);
	if (pDestArr) free(pDestArr);

	delete pCode;
}