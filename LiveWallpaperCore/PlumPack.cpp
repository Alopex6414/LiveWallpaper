/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumPack.cpp
* @brief	This Program is PlumPack DLL Project.
* @author	Alopex/Helium
* @version	v1.01a
* @date		2017-12-16	v1.00a	alopex	Create Project.
* @date		2017-12-23	v1.01a	alopex	Add Function UnPack to Memory.
* @date		2018-1-16	v1.02a	alopex	Add For PackerMaker Function.
*/
#include "PlumPack.h"

//PlumPack������Ϸ��Դ���/���(Pack/UnPack)

//------------------------------------------------------------------
// @Function:	 CPlumPack()
// @Purpose: CPlumPack���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumPack::CPlumPack()
{
	m_pCryptArr = NULL;
	m_nArrSize = 0;
}

//------------------------------------------------------------------
// @Function:	 ~CPlumPack()
// @Purpose: CPlumPack��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumPack::~CPlumPack()
{
	SAFE_DELETE_ARRAY(m_pCryptArr);
}

//-----------------------------------------------------------------------------
// @Function:	 PlumGetArray(CPlumCrypt** ppCryptArr, int* pArrSize) const
// @Purpose: CPlumPack����
// @Since: v1.00a
// @Para: CPlumCrypt** ppCryptArr
// @Para: int* pArrSize
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumGetArray(CPlumCrypt** ppCryptArr, int* pArrSize) const
{
	*ppCryptArr = m_pCryptArr;
	*pArrSize = m_nArrSize;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumPackFile(const char* pSrcArr[], int nArrSize, char* pDest)
// @Purpose: CPlumPack�������
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//���Դ�ļ�������(�����ļ�)
// @Para: int nArrSize					//���Դ�ļ�����
// @Para: const char* pDest				//���Ŀ���ļ���
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//����Ŀ���ļ���Ϣ
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//���ҳɹ�
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//����ʧ��
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//д�����ļ���Ϣ
	int i = 0;
	PlumPackInfo sPackMsg;
	DWORD dwRealWritePackMsg;

	memset(&sPackMsg, 0, sizeof(sPackMsg));
	for (i = 0, pTemp = pDestName; i < sizeof(sPackMsg.cFileName) && *pTemp != '\0'; ++i, ++pTemp)
	{
		*(sPackMsg.cFileName + i) = *pTemp;
	}
	memcpy(&(sPackMsg.cCodeAuthor), "alopex", sizeof("alopex"));
	sPackMsg.dwFileAllNum = nArrSize;
	//sPackMsg.dwFileAllSize = 0;
	WriteFile(hFileDest, &sPackMsg, sizeof(sPackMsg), &dwRealWritePackMsg, NULL);

	if (pDestName) free(pDestName);

	//Ԥ����Ӧ�ֽ�����ַ
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//ѭ����
	for (int i = 0; i < nArrSize; ++i)
	{
		//��ȡ��ǰ�ļ�ָ��λ��
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//��Դ�ļ�
		hFileSrc = CreateFileA(*(pSrcArr + i), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//�����ļ�
		char* pTemp;
		char* pMsg;
		int nCount;

		pTemp = (char*)(*(pSrcArr + i));
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
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//д��Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//д���ļ�
		unsigned char* pSrcArr = NULL;
		unsigned char* pDestArr = NULL;
		int nSrcSize = CRYPTARRAYSIZE;
		int nDestSize = CRYPTARRAYSIZE;
		DWORD dwRealRead = 0;
		DWORD dwRealWrite = 0;

		pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
		pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

		for (;;)
		{
			memset(pSrcArr, 0, nSrcSize);
			memset(pDestArr, 0, nDestSize);

			ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
			if (dwRealRead == 0) break;

			memcpy(pDestArr, pSrcArr, dwRealRead);

			WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
			if (dwRealWrite == 0) break;
		}

		if (pMsg) free(pMsg);
		if (pSrcArr) free(pSrcArr);
		if (pDestArr) free(pDestArr);

		CloseHandle(hFileMsg);
		hFileMsg = NULL;
		CloseHandle(hFileSrc);
		hFileSrc = NULL;
	}

	//����д���ļ���ַ��Ϣ
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumPackFile(const char* pSrcArr[], int nArrSize, char* pDest)
// @Purpose: CPlumPack�������
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//���Դ�ļ�������
// @Para: int nArrSize					//���Դ�ļ�����
// @Para: const char* pDest				//���Ŀ���ļ���
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//����Ŀ���ļ���Ϣ
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//���ҳɹ�
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//����ʧ��
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//д�����ļ���Ϣ
	int i = 0;
	PlumPackInfo sPackMsg;
	DWORD dwRealWritePackMsg;

	memset(&sPackMsg, 0, sizeof(sPackMsg));
	for (i = 0, pTemp = pDestName; i < sizeof(sPackMsg.cFileName) && *pTemp != '\0'; ++i, ++pTemp)
	{
		*(sPackMsg.cFileName + i) = *pTemp;
	}
	memcpy(&(sPackMsg.cCodeAuthor), "alopex", sizeof("alopex"));
	sPackMsg.dwFileAllNum = nArrSize;
	//sPackMsg.dwFileAllSize = 0;
	WriteFile(hFileDest, &sPackMsg, sizeof(sPackMsg), &dwRealWritePackMsg, NULL);

	if (pDestName) free(pDestName);

	//Ԥ����Ӧ�ֽ�����ַ
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//ѭ����
	for (int i = 0; i < nArrSize; ++i)
	{
		//��ȡ��ǰ�ļ�ָ��λ��
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//�����ļ�
		CPlumCrypt* pCrypt = new CPlumCrypt;

		char* pTempSrc;
		char* pDat;
		int nSize;

		pTempSrc = (char*)(*(pSrcArr + i));
		nSize = strlen(pTempSrc);
		pDat = (char*)malloc((nSize + 1)*sizeof(char));
		strcpy_s(pDat, (nSize + 1), pTempSrc);
		pTempSrc = strrchr(pDat, '.');
		*pTempSrc = '.';
		*(pTempSrc + 1) = 'd';
		*(pTempSrc + 2) = 'a';
		*(pTempSrc + 3) = 't';
		*(pTempSrc + 4) = '\0';

		pCrypt->PlumEnCryptFileExA(*(pSrcArr + i), (const char*)pDat, pLuckyArr);

		delete pCrypt;

		//��Դ�ļ�
		hFileSrc = CreateFileA(pDat, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//�����ļ�
		char* pTemp;
		char* pMsg;
		int nCount;

		pTemp = (char*)(*(pSrcArr + i));
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
			if (pDat) free(pDat);
			if (pMsg) free(pMsg);
			CloseHandle(hFileMsg);
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//д��Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//д���ļ�
		unsigned char* pSrcArr = NULL;
		unsigned char* pDestArr = NULL;
		int nSrcSize = CRYPTARRAYSIZE;
		int nDestSize = CRYPTARRAYSIZE;
		DWORD dwRealRead = 0;
		DWORD dwRealWrite = 0;

		pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
		pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

		for (;;)
		{
			memset(pSrcArr, 0, nSrcSize);
			memset(pDestArr, 0, nDestSize);

			ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
			if (dwRealRead == 0) break;

			memcpy(pDestArr, pSrcArr, dwRealRead);

			WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
			if (dwRealWrite == 0) break;
		}


		if (pSrcArr) free(pSrcArr);
		if (pDestArr) free(pDestArr);

		CloseHandle(hFileMsg);
		hFileMsg = NULL;
		CloseHandle(hFileSrc);
		hFileSrc = NULL;

		DeleteFileA(pDat);
		DeleteFileA(pMsg);

		if (pDat) free(pDat);
		if (pMsg) free(pMsg);
	}

	//����д���ļ���ַ��Ϣ
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumUnPackFile(const char* pSrc, char* pDest)
// @Purpose: CPlumPack�������(����洢���ļ�)
// @Since: v1.00a
// @Para: const char* pSrc				//���Դ�ļ���
// @Para: char* pDest					//���Ŀ���ļ�·��(�����ļ�����!)
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumUnPackFileA(const char* pSrc, const char* pDest)
{
	HANDLE hFileSrc;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//���������Ϣ
	PlumPackInfo sPackMsg;
	int	nFileAllNum;
	DWORD dwRealReadPackMsg;

	ReadFile(hFileSrc, &sPackMsg, sizeof(sPackMsg), &dwRealReadPackMsg, NULL);
	if (dwRealReadPackMsg == 0) return;

	nFileAllNum = sPackMsg.dwFileAllNum;//����ļ�����
	if (nFileAllNum == 0) return;

	//�洢�����ļ�ƫ�Ƶ�ַ
	char* pDestFileName = NULL;
	DWORD* pFileAddress = NULL;
	DWORD dwFileReadSize = 0;

	pFileAddress = new DWORD[nFileAllNum];
	for (int i = 0; i < nFileAllNum; ++i)
	{
		ReadFile(hFileSrc, (pFileAddress + i), sizeof(DWORD), &dwRealReadPackMsg, NULL);
	}

	//ѭ����ȡ
	for (int i = 0; i < nFileAllNum; ++i)
	{
		//���ý���ļ���ַ
		SetFilePointer(hFileSrc, *(pFileAddress + i), NULL, FILE_BEGIN);

		//�����ļ���Ϣ
		PlumFileInfo sMsg; 
		char* pArray = NULL;
		int nDestSize = 0;
		int nFileNameSize = 0;
		ReadFile(hFileSrc, &sMsg, sizeof(sMsg), &dwRealReadPackMsg, NULL);
		dwFileReadSize = sMsg.dwCryptFileSize;
		nDestSize = strlen(pDest);
		nFileNameSize = strlen(sMsg.cFileName);
		pDestFileName = new char[nDestSize + nFileNameSize + 1];
		memset(pDestFileName, 0, (nDestSize + nFileNameSize + 1)*sizeof(char));
		memcpy(pDestFileName, pDest, nDestSize);
		memcpy(pDestFileName + nDestSize, sMsg.cFileName, nFileNameSize);

		pArray = new char[dwFileReadSize];
		ReadFile(hFileSrc, pArray, dwFileReadSize, &dwRealReadPackMsg, NULL);

		//����ļ�
		CPlumCrypt* pCrypt = new CPlumCrypt;

		pCrypt->PlumDeCryptFileInMemoryStoreInFileExA((const void*)pArray, sMsg, pDestFileName);

		delete[] pDestFileName;
		delete[] pArray;
		delete pCrypt;
	}


	delete[] pFileAddress;

	CloseHandle(hFileSrc);
}

//----------------------------------------------------------------------------------
// @Function:	 PlumUnPackFile(const char* pSrc)
// @Purpose: CPlumPack�������(����洢���ڴ�)
// @Since: v1.00a
// @Para: const char* pSrc				//���Դ�ļ���
// @Return: None
//----------------------------------------------------------------------------------
void CPlumPack::PlumUnPackFileA(const char* pSrc)
{
	HANDLE hFileSrc;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//���������Ϣ
	PlumPackInfo sPackMsg;
	int	nFileAllNum;
	DWORD dwRealReadPackMsg;

	ReadFile(hFileSrc, &sPackMsg, sizeof(sPackMsg), &dwRealReadPackMsg, NULL);
	if (dwRealReadPackMsg == 0) return;

	nFileAllNum = sPackMsg.dwFileAllNum;//����ļ�����
	if (nFileAllNum == 0) return;

	//�洢����ļ���ַ����
	m_nArrSize = nFileAllNum;
	m_pCryptArr = new CPlumCrypt[m_nArrSize];

	//�洢�����ļ�ƫ�Ƶ�ַ
	char* pDestFileName = NULL;
	DWORD* pFileAddress = NULL;
	DWORD dwFileReadSize = 0;

	pFileAddress = new DWORD[nFileAllNum];
	for (int i = 0; i < nFileAllNum; ++i)
	{
		ReadFile(hFileSrc, (pFileAddress + i), sizeof(DWORD), &dwRealReadPackMsg, NULL);
	}

	//ѭ����ȡ
	for (int i = 0; i < nFileAllNum; ++i)
	{
		//���ý���ļ���ַ
		SetFilePointer(hFileSrc, *(pFileAddress + i), NULL, FILE_BEGIN);

		//�����ļ���Ϣ
		PlumFileInfo sMsg;
		char* pArray = NULL;
		ReadFile(hFileSrc, &sMsg, sizeof(sMsg), &dwRealReadPackMsg, NULL);
		dwFileReadSize = sMsg.dwCryptFileSize;
		pArray = new char[dwFileReadSize];
		ReadFile(hFileSrc, pArray, dwFileReadSize, &dwRealReadPackMsg, NULL);

		//����ļ�
		(m_pCryptArr + i)->PlumDeCryptFileInMemoryStoreInMemoryExA((const void*)pArray, sMsg);

		delete[] pDestFileName;
		delete[] pArray;
	}


	delete[] pFileAddress;

	CloseHandle(hFileSrc);
}

//-----------------------------------------------------------------------------
// @Function:	 PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, char* pDest)
// @Purpose: CPlumPack�������
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//���Դ�ļ�������
// @Para: int nArrSize					//���Դ�ļ�����
// @Para: const char* pDest				//���Ŀ���ļ���
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, int* pCount)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//����Ŀ���ļ���Ϣ
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//���ҳɹ�
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//����ʧ��
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//д�����ļ���Ϣ
	int i = 0;
	PlumPackInfo sPackMsg;
	DWORD dwRealWritePackMsg;

	memset(&sPackMsg, 0, sizeof(sPackMsg));
	for (i = 0, pTemp = pDestName; i < sizeof(sPackMsg.cFileName) && *pTemp != '\0'; ++i, ++pTemp)
	{
		*(sPackMsg.cFileName + i) = *pTemp;
	}
	memcpy(&(sPackMsg.cCodeAuthor), "alopex", sizeof("alopex"));
	sPackMsg.dwFileAllNum = nArrSize;
	//sPackMsg.dwFileAllSize = 0;
	WriteFile(hFileDest, &sPackMsg, sizeof(sPackMsg), &dwRealWritePackMsg, NULL);

	if (pDestName) free(pDestName);

	//Ԥ����Ӧ�ֽ�����ַ
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//ѭ����
	for (int i = 0; i < nArrSize; ++i)
	{
		//��ȡ��ǰ�ļ�ָ��λ��
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//��Դ�ļ�
		hFileSrc = CreateFileA(*(pSrcArr + i), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//�����ļ�
		char* pTemp;
		char* pMsg;
		int nCount;

		pTemp = (char*)(*(pSrcArr + i));
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
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//д��Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//д���ļ�
		unsigned char* pSrcArr = NULL;
		unsigned char* pDestArr = NULL;
		int nSrcSize = CRYPTARRAYSIZE;
		int nDestSize = CRYPTARRAYSIZE;
		DWORD dwRealRead = 0;
		DWORD dwRealWrite = 0;

		pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
		pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

		for (;;)
		{
			memset(pSrcArr, 0, nSrcSize);
			memset(pDestArr, 0, nDestSize);

			ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
			if (dwRealRead == 0) break;

			memcpy(pDestArr, pSrcArr, dwRealRead);

			WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
			if (dwRealWrite == 0) break;
		}

		if (pMsg) free(pMsg);
		if (pSrcArr) free(pSrcArr);
		if (pDestArr) free(pDestArr);

		CloseHandle(hFileMsg);
		hFileMsg = NULL;
		CloseHandle(hFileSrc);
		hFileSrc = NULL;

		*pCount = i + 1;
	}

	//����д���ļ���ַ��Ϣ
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, char* pDest)
// @Purpose: CPlumPack�������
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//���Դ�ļ�������
// @Para: int nArrSize					//���Դ�ļ�����
// @Para: const char* pDest				//���Ŀ���ļ���
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr, int* pCount)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//��Ŀ���ļ�
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//����Ŀ���ļ���Ϣ
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//���ҳɹ�
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//����ʧ��
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//д�����ļ���Ϣ
	int i = 0;
	PlumPackInfo sPackMsg;
	DWORD dwRealWritePackMsg;

	memset(&sPackMsg, 0, sizeof(sPackMsg));
	for (i = 0, pTemp = pDestName; i < sizeof(sPackMsg.cFileName) && *pTemp != '\0'; ++i, ++pTemp)
	{
		*(sPackMsg.cFileName + i) = *pTemp;
	}
	memcpy(&(sPackMsg.cCodeAuthor), "alopex", sizeof("alopex"));
	sPackMsg.dwFileAllNum = nArrSize;
	//sPackMsg.dwFileAllSize = 0;
	WriteFile(hFileDest, &sPackMsg, sizeof(sPackMsg), &dwRealWritePackMsg, NULL);

	if (pDestName) free(pDestName);

	//Ԥ����Ӧ�ֽ�����ַ
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//ѭ����
	for (int i = 0; i < nArrSize; ++i)
	{
		//��ȡ��ǰ�ļ�ָ��λ��
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//�����ļ�
		CPlumCrypt* pCrypt = new CPlumCrypt;

		char* pTempSrc;
		char* pDat;
		int nSize;

		pTempSrc = (char*)(*(pSrcArr + i));
		nSize = strlen(pTempSrc);
		pDat = (char*)malloc((nSize + 1)*sizeof(char));
		strcpy_s(pDat, (nSize + 1), pTempSrc);
		pTempSrc = strrchr(pDat, '.');
		*pTempSrc = '.';
		*(pTempSrc + 1) = 'd';
		*(pTempSrc + 2) = 'a';
		*(pTempSrc + 3) = 't';
		*(pTempSrc + 4) = '\0';

		pCrypt->PlumEnCryptFileExA(*(pSrcArr + i), (const char*)pDat, pLuckyArr);

		delete pCrypt;

		//��Դ�ļ�
		hFileSrc = CreateFileA(pDat, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//�����ļ�
		char* pTemp;
		char* pMsg;
		int nCount;

		pTemp = (char*)(*(pSrcArr + i));
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
			if (pDat) free(pDat);
			if (pMsg) free(pMsg);
			CloseHandle(hFileMsg);
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//д��Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//д���ļ�
		unsigned char* pSrcArr = NULL;
		unsigned char* pDestArr = NULL;
		int nSrcSize = CRYPTARRAYSIZE;
		int nDestSize = CRYPTARRAYSIZE;
		DWORD dwRealRead = 0;
		DWORD dwRealWrite = 0;

		pSrcArr = (unsigned char*)malloc(nSrcSize*sizeof(unsigned char));
		pDestArr = (unsigned char*)malloc(nDestSize*sizeof(unsigned char));

		for (;;)
		{
			memset(pSrcArr, 0, nSrcSize);
			memset(pDestArr, 0, nDestSize);

			ReadFile(hFileSrc, pSrcArr, nSrcSize, &dwRealRead, NULL);
			if (dwRealRead == 0) break;

			memcpy(pDestArr, pSrcArr, dwRealRead);

			WriteFile(hFileDest, pDestArr, dwRealRead, &dwRealWrite, NULL);
			if (dwRealWrite == 0) break;
		}


		if (pSrcArr) free(pSrcArr);
		if (pDestArr) free(pDestArr);

		CloseHandle(hFileMsg);
		hFileMsg = NULL;
		CloseHandle(hFileSrc);
		hFileSrc = NULL;

		DeleteFileA(pDat);
		DeleteFileA(pMsg);

		if (pDat) free(pDat);
		if (pMsg) free(pMsg);

		*pCount = i + 1;
	}

	//����д���ļ���ַ��Ϣ
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumUnPackPackerFile(const char* pSrc, char* pDest)
// @Purpose: CPlumPack�������(����洢���ļ�)
// @Since: v1.00a
// @Para: const char* pSrc				//���Դ�ļ���
// @Para: char* pDest					//���Ŀ���ļ�·��(�����ļ�����!)
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumUnPackFilePackerA(const char* pSrc, const char* pDest, int* pSize, int* pCount)
{
	HANDLE hFileSrc;

	//��Դ�ļ�
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//���������Ϣ
	PlumPackInfo sPackMsg;
	int	nFileAllNum;
	DWORD dwRealReadPackMsg;

	ReadFile(hFileSrc, &sPackMsg, sizeof(sPackMsg), &dwRealReadPackMsg, NULL);
	if (dwRealReadPackMsg == 0) return;

	nFileAllNum = sPackMsg.dwFileAllNum;//����ļ�����
	if (nFileAllNum == 0) return;

	*pSize = nFileAllNum;

	//�洢�����ļ�ƫ�Ƶ�ַ
	char* pDestFileName = NULL;
	DWORD* pFileAddress = NULL;
	DWORD dwFileReadSize = 0;

	pFileAddress = new DWORD[nFileAllNum];
	for (int i = 0; i < nFileAllNum; ++i)
	{
		ReadFile(hFileSrc, (pFileAddress + i), sizeof(DWORD), &dwRealReadPackMsg, NULL);
	}

	//ѭ����ȡ
	for (int i = 0; i < nFileAllNum; ++i)
	{
		//���ý���ļ���ַ
		SetFilePointer(hFileSrc, *(pFileAddress + i), NULL, FILE_BEGIN);

		//�����ļ���Ϣ
		PlumFileInfo sMsg;
		char* pArray = NULL;
		int nDestSize = 0;
		int nFileNameSize = 0;
		ReadFile(hFileSrc, &sMsg, sizeof(sMsg), &dwRealReadPackMsg, NULL);
		dwFileReadSize = sMsg.dwCryptFileSize;
		nDestSize = strlen(pDest);
		nFileNameSize = strlen(sMsg.cFileName);
		pDestFileName = new char[nDestSize + nFileNameSize + 1];
		memset(pDestFileName, 0, (nDestSize + nFileNameSize + 1)*sizeof(char));
		memcpy(pDestFileName, pDest, nDestSize);
		memcpy(pDestFileName + nDestSize, sMsg.cFileName, nFileNameSize);

		pArray = new char[dwFileReadSize];
		ReadFile(hFileSrc, pArray, dwFileReadSize, &dwRealReadPackMsg, NULL);

		//����ļ�
		CPlumCrypt* pCrypt = new CPlumCrypt;

		pCrypt->PlumDeCryptFileInMemoryStoreInFileExA((const void*)pArray, sMsg, pDestFileName);

		delete[] pDestFileName;
		delete[] pArray;
		delete pCrypt;

		*pCount = i + 1;
	}


	delete[] pFileAddress;

	CloseHandle(hFileSrc);
}