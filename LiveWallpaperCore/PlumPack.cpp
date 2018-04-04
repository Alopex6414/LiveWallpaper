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

//PlumPack用于游戏资源打包/解包(Pack/UnPack)

//------------------------------------------------------------------
// @Function:	 CPlumPack()
// @Purpose: CPlumPack构造函数
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
// @Purpose: CPlumPack析构函数
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
// @Purpose: CPlumPack访问
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
// @Purpose: CPlumPack打包函数
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//打包源文件名数组(加密文件)
// @Para: int nArrSize					//打包源文件数量
// @Para: const char* pDest				//打包目标文件名
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//打开目标文件
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//分析目标文件信息
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//查找成功
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//查找失败
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//写入打包文件信息
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

	//预留相应字节数地址
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//循环打开
	for (int i = 0; i < nArrSize; ++i)
	{
		//读取当前文件指针位置
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//打开源文件
		hFileSrc = CreateFileA(*(pSrcArr + i), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//分析文件
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

		//打开文件信息
		hFileMsg = CreateFileA(pMsg, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileMsg == INVALID_HANDLE_VALUE)
		{
			if (pMsg) free(pMsg);
			CloseHandle(hFileMsg);
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//写入Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//写入文件
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

	//重新写入文件地址信息
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumPackFile(const char* pSrcArr[], int nArrSize, char* pDest)
// @Purpose: CPlumPack打包函数
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//打包源文件名数组
// @Para: int nArrSize					//打包源文件数量
// @Para: const char* pDest				//打包目标文件名
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFileA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//打开目标文件
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//分析目标文件信息
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//查找成功
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//查找失败
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//写入打包文件信息
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

	//预留相应字节数地址
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//循环打开
	for (int i = 0; i < nArrSize; ++i)
	{
		//读取当前文件指针位置
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//加密文件
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

		//打开源文件
		hFileSrc = CreateFileA(pDat, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//分析文件
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

		//打开文件信息
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

		//写入Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//写入文件
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

	//重新写入文件地址信息
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumUnPackFile(const char* pSrc, char* pDest)
// @Purpose: CPlumPack解包函数(解包存储到文件)
// @Since: v1.00a
// @Para: const char* pSrc				//解包源文件名
// @Para: char* pDest					//解包目标文件路径(不是文件名称!)
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumUnPackFileA(const char* pSrc, const char* pDest)
{
	HANDLE hFileSrc;

	//打开源文件
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//分析封包信息
	PlumPackInfo sPackMsg;
	int	nFileAllNum;
	DWORD dwRealReadPackMsg;

	ReadFile(hFileSrc, &sPackMsg, sizeof(sPackMsg), &dwRealReadPackMsg, NULL);
	if (dwRealReadPackMsg == 0) return;

	nFileAllNum = sPackMsg.dwFileAllNum;//封包文件总数
	if (nFileAllNum == 0) return;

	//存储各个文件偏移地址
	char* pDestFileName = NULL;
	DWORD* pFileAddress = NULL;
	DWORD dwFileReadSize = 0;

	pFileAddress = new DWORD[nFileAllNum];
	for (int i = 0; i < nFileAllNum; ++i)
	{
		ReadFile(hFileSrc, (pFileAddress + i), sizeof(DWORD), &dwRealReadPackMsg, NULL);
	}

	//循环读取
	for (int i = 0; i < nFileAllNum; ++i)
	{
		//设置解包文件地址
		SetFilePointer(hFileSrc, *(pFileAddress + i), NULL, FILE_BEGIN);

		//分析文件信息
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

		//解包文件
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
// @Purpose: CPlumPack解包函数(解包存储到内存)
// @Since: v1.00a
// @Para: const char* pSrc				//解包源文件名
// @Return: None
//----------------------------------------------------------------------------------
void CPlumPack::PlumUnPackFileA(const char* pSrc)
{
	HANDLE hFileSrc;

	//打开源文件
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//分析封包信息
	PlumPackInfo sPackMsg;
	int	nFileAllNum;
	DWORD dwRealReadPackMsg;

	ReadFile(hFileSrc, &sPackMsg, sizeof(sPackMsg), &dwRealReadPackMsg, NULL);
	if (dwRealReadPackMsg == 0) return;

	nFileAllNum = sPackMsg.dwFileAllNum;//封包文件总数
	if (nFileAllNum == 0) return;

	//存储解包文件地址数量
	m_nArrSize = nFileAllNum;
	m_pCryptArr = new CPlumCrypt[m_nArrSize];

	//存储各个文件偏移地址
	char* pDestFileName = NULL;
	DWORD* pFileAddress = NULL;
	DWORD dwFileReadSize = 0;

	pFileAddress = new DWORD[nFileAllNum];
	for (int i = 0; i < nFileAllNum; ++i)
	{
		ReadFile(hFileSrc, (pFileAddress + i), sizeof(DWORD), &dwRealReadPackMsg, NULL);
	}

	//循环读取
	for (int i = 0; i < nFileAllNum; ++i)
	{
		//设置解包文件地址
		SetFilePointer(hFileSrc, *(pFileAddress + i), NULL, FILE_BEGIN);

		//分析文件信息
		PlumFileInfo sMsg;
		char* pArray = NULL;
		ReadFile(hFileSrc, &sMsg, sizeof(sMsg), &dwRealReadPackMsg, NULL);
		dwFileReadSize = sMsg.dwCryptFileSize;
		pArray = new char[dwFileReadSize];
		ReadFile(hFileSrc, pArray, dwFileReadSize, &dwRealReadPackMsg, NULL);

		//解包文件
		(m_pCryptArr + i)->PlumDeCryptFileInMemoryStoreInMemoryExA((const void*)pArray, sMsg);

		delete[] pDestFileName;
		delete[] pArray;
	}


	delete[] pFileAddress;

	CloseHandle(hFileSrc);
}

//-----------------------------------------------------------------------------
// @Function:	 PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, char* pDest)
// @Purpose: CPlumPack打包函数
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//打包源文件名数组
// @Para: int nArrSize					//打包源文件数量
// @Para: const char* pDest				//打包目标文件名
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, int* pCount)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//打开目标文件
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//分析目标文件信息
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//查找成功
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//查找失败
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//写入打包文件信息
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

	//预留相应字节数地址
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//循环打开
	for (int i = 0; i < nArrSize; ++i)
	{
		//读取当前文件指针位置
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//打开源文件
		hFileSrc = CreateFileA(*(pSrcArr + i), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//分析文件
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

		//打开文件信息
		hFileMsg = CreateFileA(pMsg, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileMsg == INVALID_HANDLE_VALUE)
		{
			if (pMsg) free(pMsg);
			CloseHandle(hFileMsg);
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//写入Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//写入文件
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

	//重新写入文件地址信息
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, char* pDest)
// @Purpose: CPlumPack打包函数
// @Since: v1.00a
// @Para: const char* pSrcArr[]			//打包源文件名数组
// @Para: int nArrSize					//打包源文件数量
// @Para: const char* pDest				//打包目标文件名
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumPackFilePackerA(const char* pSrcArr[], int nArrSize, const char* pDest, DWORD* pLuckyArr, int* pCount)
{
	HANDLE hFileSrc;
	HANDLE hFileDest;
	HANDLE hFileMsg;

	//打开目标文件
	hFileDest = CreateFileA(pDest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileDest == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileDest);
		return;
	}

	//分析目标文件信息
	char* pTemp;
	char* pDestName;
	int nCount;

	pTemp = strrchr((char*)pDest, '\\');
	if (pTemp != NULL)//查找成功
	{
		nCount = strlen(++pTemp);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}
	else//查找失败
	{
		nCount = strlen(pDest);
		pDestName = (char*)malloc((nCount + 1)*sizeof(char));
		memset(pDestName, 0, (nCount + 1));
		strcpy_s(pDestName, (nCount + 1), pTemp);
	}

	//写入打包文件信息
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

	//预留相应字节数地址
	DWORD* pFileAddressArr = NULL;

	pFileAddressArr = new DWORD[nArrSize];
	memset(pFileAddressArr, 0, nArrSize*sizeof(DWORD));
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	//循环打开
	for (int i = 0; i < nArrSize; ++i)
	{
		//读取当前文件指针位置
		*(pFileAddressArr + i) = SetFilePointer(hFileDest, NULL, NULL, FILE_CURRENT);

		//加密文件
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

		//打开源文件
		hFileSrc = CreateFileA(pDat, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFileSrc == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileSrc);
			CloseHandle(hFileDest);
			return;
		}

		//分析文件
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

		//打开文件信息
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

		//写入Msg
		PlumFileInfo sMsg;
		DWORD dwMsgRead;
		DWORD dwMsgWrite;

		ReadFile(hFileMsg, &sMsg, sizeof(sMsg), &dwMsgRead, NULL);
		WriteFile(hFileDest, &sMsg, sizeof(sMsg), &dwMsgWrite, NULL);

		//写入文件
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

	//重新写入文件地址信息
	SetFilePointer(hFileDest, sizeof(sPackMsg), NULL, FILE_BEGIN);
	WriteFile(hFileDest, pFileAddressArr, nArrSize*sizeof(DWORD), &dwRealWritePackMsg, NULL);

	delete[] pFileAddressArr;

	CloseHandle(hFileDest);
	hFileDest = NULL;
}

//-----------------------------------------------------------------------------
// @Function:	 PlumUnPackPackerFile(const char* pSrc, char* pDest)
// @Purpose: CPlumPack解包函数(解包存储到文件)
// @Since: v1.00a
// @Para: const char* pSrc				//解包源文件名
// @Para: char* pDest					//解包目标文件路径(不是文件名称!)
// @Return: None
//-----------------------------------------------------------------------------
void CPlumPack::PlumUnPackFilePackerA(const char* pSrc, const char* pDest, int* pSize, int* pCount)
{
	HANDLE hFileSrc;

	//打开源文件
	hFileSrc = CreateFileA(pSrc, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileSrc == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSrc);
		return;
	}

	//分析封包信息
	PlumPackInfo sPackMsg;
	int	nFileAllNum;
	DWORD dwRealReadPackMsg;

	ReadFile(hFileSrc, &sPackMsg, sizeof(sPackMsg), &dwRealReadPackMsg, NULL);
	if (dwRealReadPackMsg == 0) return;

	nFileAllNum = sPackMsg.dwFileAllNum;//封包文件总数
	if (nFileAllNum == 0) return;

	*pSize = nFileAllNum;

	//存储各个文件偏移地址
	char* pDestFileName = NULL;
	DWORD* pFileAddress = NULL;
	DWORD dwFileReadSize = 0;

	pFileAddress = new DWORD[nFileAllNum];
	for (int i = 0; i < nFileAllNum; ++i)
	{
		ReadFile(hFileSrc, (pFileAddress + i), sizeof(DWORD), &dwRealReadPackMsg, NULL);
	}

	//循环读取
	for (int i = 0; i < nFileAllNum; ++i)
	{
		//设置解包文件地址
		SetFilePointer(hFileSrc, *(pFileAddress + i), NULL, FILE_BEGIN);

		//分析文件信息
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

		//解包文件
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