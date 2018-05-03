/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumConsole.cpp
* @brief	This Program is PlumConsole DLL Project.
* @notes	Console����̨����
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-12-23	v1.00a	alopex	Create Project.
*/
#include "PlumConsole.h"

//This Class is Use for Console Debug(����̨����)
#pragma warning(disable: 4996)

//------------------------------------------------------------------
// @Function:	 CPlumConsole()
// @Purpose: CPlumConsole���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumConsole::CPlumConsole()
{
	m_hConsole = NULL;
	memset(&m_sConsoleInfo, 0, sizeof(m_sConsoleInfo));
}

//------------------------------------------------------------------
// @Function:	 ~CPlumConsole()
// @Purpose: CPlumConsole��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CPlumConsole::~CPlumConsole()
{
	CloseHandle(m_hConsole);
}

//------------------------------------------------------------------
// @Function:	 PlumConsoleGetHandle(void) const
// @Purpose: CPlumConsole���ʿ���̨���
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
HANDLE CPlumConsole::PlumConsoleGetHandle(void) const
{
	return m_hConsole;
}

//------------------------------------------------------------------
// @Function:	 PlumConsoleSetConsoleTitle(LPCWSTR lpcszTitle)
// @Purpose: CPlumConsole���ÿ���̨����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumConsole::PlumConsoleSetConsoleTitle(LPCWSTR lpcszTitle)
{
	SetConsoleTitle(lpcszTitle);
}

//------------------------------------------------------------------
// @Function:	 PlumConsoleSetCursorPosition(COORD Coord)
// @Purpose: CPlumConsole���ÿ���̨���λ��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumConsole::PlumConsoleSetCursorPosition(COORD Coord)
{
	SetConsoleCursorPosition(m_hConsole, Coord);
}

//------------------------------------------------------------------
// @Function:	 PlumConsoleGetScreenBufferInfo(void)
// @Purpose: CPlumConsole��ȡ����̨��������Ϣ
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumConsole::PlumConsoleGetScreenBufferInfo(void)
{
	GetConsoleScreenBufferInfo(m_hConsole, &m_sConsoleInfo);
}

//------------------------------------------------------------------
// @Function:	 PlumConsoleInit()
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void CPlumConsole::PlumConsoleInit(LPCWSTR lpcszTitle)
{
	COORD Coord;
	SMALL_RECT SmallRect;

	Coord.X = GetSystemMetrics(SM_CXMIN);
	Coord.Y = GetSystemMetrics(SM_CYMIN);

	SmallRect.Left = 0;
	SmallRect.Top = 0;
	SmallRect.Right = Coord.X - 1;
	SmallRect.Bottom = Coord.Y - 1;

	AllocConsole();
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleScreenBufferSize(m_hConsole, Coord);
	SetConsoleWindowInfo(m_hConsole, TRUE, &SmallRect);
	
	SetConsoleTitle(lpcszTitle);
	
	GetConsoleScreenBufferInfo(m_hConsole, &m_sConsoleInfo);
}

//------------------------------------------------------------------
// @Function:	 PlumConsoleInit(COORD Coord)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: COORD Coord			//Console���ڻ�������С
// @Return: None
//------------------------------------------------------------------
void CPlumConsole::PlumConsoleInit(COORD Coord, LPCWSTR lpcszTitle)
{
	SMALL_RECT SmallRect;

	SmallRect.Left = 0;
	SmallRect.Top = 0;
	SmallRect.Right = Coord.X - 1;
	SmallRect.Bottom = Coord.Y - 1;

	AllocConsole();
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleScreenBufferSize(m_hConsole, Coord);
	SetConsoleWindowInfo(m_hConsole, TRUE, &SmallRect);

	SetConsoleTitle(lpcszTitle);

	GetConsoleScreenBufferInfo(m_hConsole, &m_sConsoleInfo);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleInit(int nX, int nY, int nWidth, int nHeight)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: int nX			//Console����X
// @Para: int nY			//Console����Y
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleInit(int nWidth, int nHeight, LPCWSTR lpcszTitle)
{
	COORD Coord;
	SMALL_RECT SmallRect;

	Coord.X = nWidth;
	Coord.Y = nHeight;

	SmallRect.Left = 0;
	SmallRect.Top = 0;
	SmallRect.Right = nWidth - 1;
	SmallRect.Bottom = nHeight - 1;

	AllocConsole();
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleScreenBufferSize(m_hConsole, Coord);
	SetConsoleWindowInfo(m_hConsole, TRUE, &SmallRect);

	SetConsoleTitle(lpcszTitle);

	GetConsoleScreenBufferInfo(m_hConsole, &m_sConsoleInfo);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleClear(void)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: None
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleClear(void)
{
	COORD StartPos;

	StartPos.X = 0;
	StartPos.Y = 0;

	FillConsoleOutputCharacterA(m_hConsole, ' ', m_sConsoleInfo.dwSize.X * m_sConsoleInfo.dwSize.Y, StartPos, NULL);
	SetConsoleCursorPosition(m_hConsole, StartPos);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleClearLine(int Y)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: int Y				//���һ��
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleClearLine(int Y)
{
	COORD StartPos;

	StartPos.X = 0;
	StartPos.Y = Y;

	FillConsoleOutputCharacterA(m_hConsole, ' ', m_sConsoleInfo.dwSize.X, StartPos, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWrite(const void* lpcszStr)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWrite(const void* lpcszStr)
{
	DWORD dwWriteCount;

	WriteConsoleA(m_hConsole, lpcszStr, strlen((const char*)lpcszStr), &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWrite(const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWrite(const void* lpcszStr, int nSize)
{
	DWORD dwWriteCount;

	WriteConsoleA(m_hConsole, lpcszStr, nSize, &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWrite(const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWrite(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine)
{
	DWORD dwWriteCount;

	if (!bIsUnderLine)
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor);
	}
	else
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor | COMMON_LVB_UNDERSCORE);
	}

	WriteConsoleA(m_hConsole, lpcszStr, strlen((const char*)lpcszStr), &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWrite(const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWrite(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine)
{
	DWORD dwWriteCount;

	if (!bIsUnderLine)
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor);
	}
	else
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor | COMMON_LVB_UNDERSCORE);
	}

	WriteConsoleA(m_hConsole, lpcszStr, nSize, &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteLine(const void* lpcszStr)
// @Purpose: CPlumConsole����̨���(����) 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLine(const void* lpcszStr)
{
	PlumConsoleWrite(lpcszStr);
	PlumConsoleWrite("\n");
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteLine(const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨���(����) 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLine(const void* lpcszStr, int nSize)
{
	PlumConsoleWrite(lpcszStr, nSize);
	PlumConsoleWrite("\n");
}

//---------------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteLine(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨���(����) 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//---------------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLine(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine)
{
	PlumConsoleWrite(lpcszStr, wTextColor, bIsUnderLine);
	PlumConsoleWrite("\n");
}

//--------------------------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteLine(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨���(����) 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//--------------------------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLine(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine)
{
	PlumConsoleWrite(lpcszStr, nSize, wTextColor, bIsUnderLine);
	PlumConsoleWrite("\n");
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteEx(int X, int Y, const void* lpcszStr)
{
	COORD Coord;

	Coord.X = X;
	Coord.Y = Y;

	SetConsoleCursorPosition(m_hConsole, Coord);
	PlumConsoleWrite(lpcszStr);
}

//--------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//--------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize)
{
	COORD Coord;

	Coord.X = X;
	Coord.Y = Y;

	SetConsoleCursorPosition(m_hConsole, Coord);
	PlumConsoleWrite(lpcszStr, nSize);
}

//---------------------------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//---------------------------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine)
{
	COORD Coord;

	Coord.X = X;
	Coord.Y = Y;

	SetConsoleCursorPosition(m_hConsole, Coord);
	PlumConsoleWrite(lpcszStr, wTextColor, bIsUnderLine);
}

//--------------------------------------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//--------------------------------------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine)
{
	COORD Coord;

	Coord.X = X;
	Coord.Y = Y;

	SetConsoleCursorPosition(m_hConsole, Coord);
	PlumConsoleWrite(lpcszStr, nSize, wTextColor, bIsUnderLine);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr)
{
	PlumConsoleWriteEx(X, Y, lpcszStr);
	PlumConsoleWrite("\n");
}

//--------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//--------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize)
{
	PlumConsoleWriteEx(X, Y, lpcszStr, nSize);
	PlumConsoleWrite("\n");
}

//---------------------------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//---------------------------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine)
{
	PlumConsoleWriteEx(X, Y, lpcszStr, wTextColor, bIsUnderLine);
	PlumConsoleWrite("\n");
}

//--------------------------------------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//--------------------------------------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine)
{
	PlumConsoleWriteEx(X, Y, lpcszStr, nSize, wTextColor, bIsUnderLine);
	PlumConsoleWrite("\n");
}

//-----------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteInt(int nNumber, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//-----------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteInt(int nNumber, WORD wTextColor, bool bIsUnderLine)
{
	DWORD dwWriteCount;
	char StrArr[10];

	memset(StrArr, 0, sizeof(StrArr));
	_itoa_s(nNumber, StrArr, 10);

	if (!bIsUnderLine)
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor);
	}
	else
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor | COMMON_LVB_UNDERSCORE);
	}

	WriteConsoleA(m_hConsole, StrArr, strlen(StrArr), &dwWriteCount, NULL);
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteFloat(float fNumber, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteFloat(float fNumber, WORD wTextColor, bool bIsUnderLine)
{
	DWORD dwWriteCount;
	char StrArr[20];

	memset(StrArr, 0, sizeof(StrArr));
	sprintf_s(StrArr, "%.2f", fNumber);

	if (!bIsUnderLine)
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor);
	}
	else
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor | COMMON_LVB_UNDERSCORE);
	}

	WriteConsoleA(m_hConsole, StrArr, strlen(StrArr), &dwWriteCount, NULL);
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteDouble(double dNumber, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteDouble(double dNumber, WORD wTextColor, bool bIsUnderLine)
{
	DWORD dwWriteCount;
	char StrArr[20];

	memset(StrArr, 0, sizeof(StrArr));
	_gcvt_s(StrArr, dNumber, 6);

	if (!bIsUnderLine)
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor);
	}
	else
	{
		SetConsoleTextAttribute(m_hConsole, wTextColor | COMMON_LVB_UNDERSCORE);
	}

	WriteConsoleA(m_hConsole, StrArr, strlen(StrArr), &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteInt(int nNumber, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//-----------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineInt(int nNumber, WORD wTextColor, bool bIsUnderLine)
{
	PlumConsoleWriteInt(nNumber, wTextColor, bIsUnderLine);
	PlumConsoleWrite("\n");
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteFloat(float fNumber, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineFloat(float fNumber, WORD wTextColor, bool bIsUnderLine)
{
	PlumConsoleWriteFloat(fNumber, wTextColor, bIsUnderLine);
	PlumConsoleWrite("\n");
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteDouble(double dNumber, WORD wTextColor, bool bIsUnderLine)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineDouble(double dNumber, WORD wTextColor, bool bIsUnderLine)
{
	PlumConsoleWriteDouble(dNumber, wTextColor, bIsUnderLine);
	PlumConsoleWrite("\n");
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteNormal(LPCSTR lpcstr, ...)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: ...
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteNormal(LPCSTR lpcstr, ...)
{
	va_list arg_ptr;
	char WriteArr[MAX_PATH];
	DWORD dwWriteCount;

	va_start(arg_ptr, lpcstr);
	memset(WriteArr, 0, sizeof(WriteArr));
	_vsnprintf(WriteArr, sizeof(WriteArr), lpcstr, arg_ptr);
	va_end(arg_ptr);

	WriteConsoleA(m_hConsole, WriteArr, strlen((const char*)WriteArr), &dwWriteCount, NULL);
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteLineNormal(LPCSTR lpcstr, ...)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: ...
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineNormal(LPCSTR lpcstr, ...)
{
	va_list arg_ptr;
	char WriteArr[MAX_PATH];
	DWORD dwWriteCount;

	va_start(arg_ptr, lpcstr);
	memset(WriteArr, 0, sizeof(WriteArr));
	_vsnprintf(WriteArr, sizeof(WriteArr), lpcstr, arg_ptr);
	va_end(arg_ptr);

	WriteConsoleA(m_hConsole, WriteArr, strlen((const char*)WriteArr), &dwWriteCount, NULL);
	WriteConsoleA(m_hConsole, "\n", strlen("\n"), &dwWriteCount, NULL);
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteNormal(LPCSTR lpcstr, ...)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: ...
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteRepeat(int Y, LPCSTR lpcstr, ...)
{
	va_list arg_ptr;
	char WriteArr[MAX_PATH];
	COORD Coord;
	DWORD dwWriteCount;

	Coord.X = 0;
	Coord.Y = Y;

	PlumConsoleClearLine(Y);	//�����
	SetConsoleCursorPosition(m_hConsole, Coord);	//��������

	va_start(arg_ptr, lpcstr);
	memset(WriteArr, 0, sizeof(WriteArr));
	_vsnprintf(WriteArr, sizeof(WriteArr), lpcstr, arg_ptr);
	va_end(arg_ptr);

	WriteConsoleA(m_hConsole, WriteArr, strlen((const char*)WriteArr), &dwWriteCount, NULL);
}

//---------------------------------------------------------------------------------------
// @Function:	 PlumConsoleWriteNormal(LPCSTR lpcstr, ...)
// @Purpose: CPlumConsole����̨���
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: ...
// @Return: None
//---------------------------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteLineRepeat(int Y, LPCSTR lpcstr, ...)
{
	va_list arg_ptr;
	char WriteArr[MAX_PATH];
	COORD Coord;
	DWORD dwWriteCount;

	Coord.X = 0;
	Coord.Y = Y;

	PlumConsoleClearLine(Y);	//�����
	SetConsoleCursorPosition(m_hConsole, Coord);	//��������

	va_start(arg_ptr, lpcstr);
	memset(WriteArr, 0, sizeof(WriteArr));
	_vsnprintf(WriteArr, sizeof(WriteArr), lpcstr, arg_ptr);
	va_end(arg_ptr);

	WriteConsoleA(m_hConsole, WriteArr, strlen((const char*)WriteArr), &dwWriteCount, NULL);
	WriteConsoleA(m_hConsole, "\n", strlen("\n"), &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteA(const void* lpcszStr)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteA(const void* lpcszStr)
{
	DWORD dwWriteCount;

	WriteConsoleA(m_hConsole, lpcszStr, strlen((const char*)lpcszStr), &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteA(const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteA(const void* lpcszStr, int nSize)
{
	DWORD dwWriteCount;

	WriteConsoleA(m_hConsole, lpcszStr, nSize, &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteW(const void* lpcszStr)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteW(const void* lpcszStr)
{
	DWORD dwWriteCount;

	WriteConsoleW(m_hConsole, lpcszStr, strlen((const char*)lpcszStr)/2, &dwWriteCount, NULL);
}

//-----------------------------------------------------------------------
// @Function:	 PlumConsoleWriteW(const void* lpcszStr, int nSize)
// @Purpose: CPlumConsole����̨��ʼ�� 
// @Since: v1.00a
// @Para: const void* lpcszStr			//�ַ�����ַ
// @Para: int nSize						//�ַ�������
// @Return: None
//-----------------------------------------------------------------------
void CPlumConsole::PlumConsoleWriteW(const void* lpcszStr, int nSize)
{
	DWORD dwWriteCount;

	WriteConsoleW(m_hConsole, lpcszStr, nSize, &dwWriteCount, NULL);
}