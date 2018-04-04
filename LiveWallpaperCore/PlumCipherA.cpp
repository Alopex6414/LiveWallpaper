/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumCipherA.cpp
* @brief	This Program is PlumCipherA DLL Project.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-12-13	v1.00a	alopex	Create Project
*/
#include "PlumCipherA.h"

//This Class is AES Cipher Algorithm(AES加密/解密)

//------------------------------------------------------------------
// @Function:	 CPlumCipherA()
// @Purpose: CPlumCipherA构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumCipherA::CPlumCipherA()
{
	memset(m_cSBox, 0, sizeof(m_cSBox));
	memset(m_cInvSBox, 0, sizeof(m_cInvSBox));
	memset(m_cExMatrix, 0, sizeof(m_cExMatrix));
}

//------------------------------------------------------------------
// @Function:	 ~CPlumCipherA()
// @Purpose: CPlumCipherA析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumCipherA::~CPlumCipherA()
{
}

//------------------------------------------------------------------
// @Function:	 CPlumCipherA(unsigned char* Key)
// @Purpose: CPlumCipherA构造函数
// @Since: v1.00a
// @Para: unsigned char* Key(秘钥)
// @Return: None
//------------------------------------------------------------------
CPlumCipherA::CPlumCipherA(unsigned char* Key)
{
	unsigned char SBox[256] =
	{
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16,
	};
	unsigned char InvSBox[256] =
	{
		0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
		0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
		0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
		0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
		0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
		0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
		0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
		0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
		0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
		0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
		0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
		0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
		0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
		0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
		0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
		0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,
	};

	memcpy(m_cSBox, SBox, 256);
	memcpy(m_cInvSBox, InvSBox, 256);
	KeyExMatrix(Key, m_cExMatrix);
}

//------------------------------------------------------------------------
// @Function:	 KeyExMatrix(unsigned char* Key, unsigned char Ex[][4][4])
// @Purpose: CPlumCipherA秘钥扩展
// @Since: v1.00a
// @Para: unsigned char* Key(秘钥)
// @Para: unsigned char  Ex[][4][4](扩展数组)
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::KeyExMatrix(unsigned char* Key, unsigned char Ex[][4][4])
{
	unsigned char Shift[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
	unsigned char* pSrc;
	unsigned char* pDest;

	for (pSrc = Key, pDest = &Ex[0][0][0]; pSrc < (Key + 16);)
	{
		*pDest++ = *pSrc++;
	}

	for (int i = 1; i <= 10; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			unsigned char T[4];

			for (int k = 0; k < 4; ++k)
			{
				T[k] = j ? Ex[i][k][j - 1] : Ex[i - 1][k][3];
			}
			if (j == 0)
			{
				unsigned char Temp = T[0];
				for (int k = 0; k < 3; ++k)
				{
					T[k] = m_cSBox[T[(k + 1) % 4]];
				}
				T[3] = m_cSBox[Temp];
				T[0] ^= Shift[i - 1];
			}
			for (int k = 0; k < 4; ++k)
			{
				Ex[i][k][j] = Ex[i - 1][k][j] ^ T[k];
			}
		}
	}
}

//------------------------------------------------------------------------
// @Function:	 FFMul(unsigned char Var1, unsigned char Var2)
// @Purpose: CPlumCipherA秘钥计算
// @Since: v1.00a
// @Para: unsigned char	Var1
// @Para: unsigned char Var2
// @Return: None
//------------------------------------------------------------------------
unsigned char CPlumCipherA::FFMul(unsigned char Var1, unsigned char Var2)
{
	unsigned char Arr[4];
	unsigned char Res = 0;

	Arr[0] = Var2;
	for (int i = 1; i < 4; ++i)
	{
		Arr[i] = Arr[i - 1] << 1;
		if (Arr[i - 1] & 0x80)
		{
			Arr[i] ^= 0x1b;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		if ((Var1 >> i) & 0x01)
		{
			Res ^= Arr[i];
		}
	}

	return Res;
}

//------------------------------------------------------------------------
// @Function:	 SubBytes(unsigned char* pState)
// @Purpose: CPlumCipherA秘钥计算
// @Since: v1.00a
// @Para: unsigned char* pState
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::SubBytes(unsigned char* pState)
{
	unsigned char* pSBox;
	unsigned char* pTemp;

	for (pTemp = pState, pSBox = m_cSBox; pTemp < (pState + 16);)
	{
		*pTemp++ = *(pSBox + *pTemp);
	}
}

//------------------------------------------------------------------------
// @Function:	 ShiftRows(unsigned char State[][4])
// @Purpose: CPlumCipherA秘钥计算
// @Since: v1.00a
// @Para: unsigned char State[][4]
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::ShiftRows(unsigned char State[][4])
{
	unsigned char T[4];

	for (int i = 1; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			T[j] = State[i][(i + j) % 4];
		}
		for (int j = 0; j < 4; ++j)
		{
			State[i][j] = T[j];
		}
	}
}

//------------------------------------------------------------------------
// @Function:	 MixColumns(unsigned char State[][4])
// @Purpose: CPlumCipherA秘钥计算
// @Since: v1.00a
// @Para: unsigned char State[][4]
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::MixColumns(unsigned char State[][4])
{
	unsigned char T[4];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			T[j] = State[j][i];
		}
		for (int j = 0; j < 4; ++j)
		{
			State[j][i] = FFMul(0x02, T[j])
				^ FFMul(0x03, T[(j + 1) % 4])
				^ FFMul(0x01, T[(j + 2) % 4])
				^ FFMul(0x01, T[(j + 3) % 4]);
		}
	}
}

//--------------------------------------------------------------------------
// @Function:	 AddRoundKey(unsigned char* pState, unsigned char* pK)
// @Purpose: CPlumCipherA秘钥计算
// @Since: v1.00a
// @Para: unsigned char* pState
// @Para: unsigned char* pK
// @Return: None
//--------------------------------------------------------------------------
void CPlumCipherA::AddRoundKey(unsigned char* pState, unsigned char* pK)
{
	unsigned char* pTemp;
	unsigned char* pKey;

	for (pTemp = pState, pKey = pK; pTemp < (pState + 16);)
	{
		*pTemp++ ^= *pKey++;
	}
}

//------------------------------------------------------------------------
// @Function:	 InvSubBytes(unsigned char* pState)
// @Purpose: CPlumCipherA解密计算
// @Since: v1.00a
// @Para: unsigned char* pState
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::InvSubBytes(unsigned char* pState)
{
	unsigned char* pInvSBox;
	unsigned char* pTemp;

	for (pTemp = pState, pInvSBox = m_cInvSBox; pTemp < (pState + 16);)
	{
		*pTemp++ = *(pInvSBox + *pTemp);
	}
}

//------------------------------------------------------------------------
// @Function:	 InvShiftRows(unsigned char State[][4])
// @Purpose: CPlumCipherA解密计算
// @Since: v1.00a
// @Para: unsigned char State[][4]
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::InvShiftRows(unsigned char State[][4])
{
	unsigned char T[4];

	for (int i = 1; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			T[j] = State[i][(j - i + 4) % 4];
		}
		for (int j = 0; j < 4; ++j)
		{
			State[i][j] = T[j];
		}
	}
}

//------------------------------------------------------------------------
// @Function:	 InvMixColumns(unsigned char State[][4])
// @Purpose: CPlumCipherA解密计算
// @Since: v1.00a
// @Para: unsigned char State[][4]
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::InvMixColumns(unsigned char State[][4])
{
	unsigned char T[4];

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			T[j] = State[j][i];
		}
		for (int j = 0; j < 4; ++j)
		{
			State[j][i] = FFMul(0x0e, T[j])
				^ FFMul(0x0b, T[(j + 1) % 4])
				^ FFMul(0x0d, T[(j + 2) % 4])
				^ FFMul(0x09, T[(j + 3) % 4]);
		}
	}
}

//------------------------------------------------------------------------
// @Function:	 EnCipher(unsigned char* pSrc)
// @Purpose: CPlumCipherA矩阵加密(4x4)
// @Since: v1.00a
// @Para: const void* pSrc	//源数组
// @Para: void* pDest		//目标数组
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::EnCipher(const unsigned char* pSrc, unsigned char* pDest)
{
	unsigned char State[4][4];

	//Copy
	for (int i = 0; i < 16; ++i)
	{
		*(pDest + i) = *(pSrc + i);
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			State[i][j] = pDest[i + 4 * j];
		}
	}

	AddRoundKey(&State[0][0], &m_cExMatrix[0][0][0]);

	for (int i = 1; i <= 10; ++i)
	{
		SubBytes(&State[0][0]);
		ShiftRows(State);
		if (i != 10)
		{
			MixColumns(State);
		}
		AddRoundKey(&State[0][0], &m_cExMatrix[i][0][0]);
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			pDest[i + 4 * j] = State[i][j];
		}
	}

}

//------------------------------------------------------------------------
// @Function:	 DeCipher(unsigned char* pSrc)
// @Purpose: CPlumCipherA矩阵解密(4x4)
// @Since: v1.00a
// @Para: const void* pSrc	//源数组
// @Para: void* pDest		//目标数组
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::DeCipher(const unsigned char* pSrc, unsigned char* pDest)
{
	unsigned char State[4][4];

	//Copy
	for (int i = 0; i < 16; ++i)
	{
		*(pDest + i) = *(pSrc + i);
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			State[i][j] = pDest[i + 4 * j];
		}
	}

	AddRoundKey(&State[0][0], &m_cExMatrix[10][0][0]);

	for (int i = 9; i >= 0; --i)
	{
		InvShiftRows(State);
		InvSubBytes(&State[0][0]);
		AddRoundKey(&State[0][0], &m_cExMatrix[i][0][0]);
		if (i)
		{
			InvMixColumns(State);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			pDest[i + 4 * j] = State[i][j];
		}
	}

}

//------------------------------------------------------------------------
// @Function:	 EnCrypt(const void* pSrc, void* pDest, int nLen)
// @Purpose: CPlumCipherA加密
// @Since: v1.00a
// @Para: const void* pSrc	//源数组
// @Para: void* pDest		//目标数组
// @Para: int nLen			//数组长度
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::EnCrypt(const void* pSrc, void* pDest, int nLen)
{
	unsigned char* pIn = (unsigned char*)pSrc;
	unsigned char* pOu = (unsigned char*)pDest;

	for (int i = 0; i < nLen; i += 16)
	{
		EnCipher((pIn + i), (pOu + i));
	}
}

//------------------------------------------------------------------------
// @Function:	 DeCrypt(void* pSrc, int nLen)
// @Purpose: CPlumCipherA矩阵解密
// @Since: v1.00a
// @Para: const void* pSrc	//源数组
// @Para: void* pDest		//目标数组
// @Para: int nLen			//数组长度
// @Return: None
//------------------------------------------------------------------------
void CPlumCipherA::DeCrypt(const void* pSrc, void* pDest, int nLen)
{
	unsigned char* pIn = (unsigned char*)pSrc;
	unsigned char* pOu = (unsigned char*)pDest;

	for (int i = 0; i < nLen; i += 16)
	{
		DeCipher((pIn + i), (pOu + i));
	}
}