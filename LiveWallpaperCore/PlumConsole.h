/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumConsole.h
* @brief	This Program is PlumConsole DLL Project.
* @notes	Console����̨����
* @author	Alopex/Helium
* @version	v1.00a
* @date		2017-12-23	v1.00a	alopex	Create Project.
*/
#pragma once

#ifndef __PLUMCONSOLE_H_
#define __PLUMCONSOLE_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Run Header File
#include <stdio.h>
#include <stdarg.h>

//Macro Definition
#ifdef	PLUMCONSOLE_EXPORTS
#define PLUMCONSOLE_API	__declspec(dllexport)
#else
#define PLUMCONSOLE_API	__declspec(dllimport)
#endif

//About Console Output Color
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_RED	(WORD)(FOREGROUND_RED	| FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_GREEN	(WORD)(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_BLUE	(WORD)(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_PINK	(WORD)(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_YELLOW	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_CYAN	(WORD)(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define CONSOLE_TEXTCOLOR_BRIGHTNESS_WHITE	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#define CONSOLE_TEXTCOLOR_DARKNESS_RED		(WORD)(FOREGROUND_RED)
#define CONSOLE_TEXTCOLOR_DARKNESS_GREEN	(WORD)(FOREGROUND_GREEN)
#define CONSOLE_TEXTCOLOR_DARKNESS_BLUE		(WORD)(FOREGROUND_BLUE)
#define CONSOLE_TEXTCOLOR_DARKNESS_PINK		(WORD)(FOREGROUND_RED | FOREGROUND_BLUE)
#define CONSOLE_TEXTCOLOR_DARKNESS_YELLOW	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN)
#define CONSOLE_TEXTCOLOR_DARKNESS_CYAN		(WORD)(FOREGROUND_GREEN | FOREGROUND_BLUE)
#define CONSOLE_TEXTCOLOR_DARKNESS_WHITE	(WORD)(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

//Class Definition
class CPlumConsole
{
private:
	HANDLE m_hConsole;							//Console Handle ����̨���
	CONSOLE_SCREEN_BUFFER_INFO m_sConsoleInfo;	//Console Infomation ����̨��Ϣ


public:
	CPlumConsole();								//PlumConsole ���캯��
	virtual ~CPlumConsole();					//PlumConsole ��������

	//����
	HANDLE PlumConsoleGetHandle(void) const;	//PlumConsole ���ʿ���̨���

	//��
	void PlumConsoleSetConsoleTitle(LPCWSTR lpcszTitle);										//PlumConsole ���ÿ���̨����
	void PlumConsoleSetCursorPosition(COORD Coord);												//PlumConsole ���ù��λ��

	void PlumConsoleGetScreenBufferInfo(void);													//PlumConsole ��ȡ����̨��������Ϣ

	//��ʼ��
	virtual void PlumConsoleInit(LPCWSTR lpcszTitle = L"Console");								//PlumConsole Init~(��ʼ��Console)
	virtual void PlumConsoleInit(COORD Coord, LPCWSTR lpcszTitle = L"Console");					//PlumConsole Init~(��ʼ��Console)<Console����λ��/��С>
	virtual void PlumConsoleInit(int nWidth, int nHeight, LPCWSTR lpcszTitle = L"Console");		//PlumConsole Init~(��ʼ��Console)<Console����λ��/��С>

	//���
	virtual void PlumConsoleClear(void);														//PlumConsole Clear(���Console)<Console�������>
	virtual void PlumConsoleClearLine(int Y);													//PlumConsole Clear(���Console Line)<Console���һ��>

	//���
	virtual void PlumConsoleWrite(const void* lpcszStr);										//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWrite(const void* lpcszStr, int nSize);								//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWrite(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWrite(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PlumConsoleWriteLine(const void* lpcszStr);									//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLine(const void* lpcszStr, int nSize);							//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLine(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLine(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr);						//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize);				//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr);					//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize);			//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PlumConsoleWriteInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);								//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);							//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PlumConsoleWriteLineInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);								//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLineFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);							//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteLineDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PlumConsoleWriteNormal(LPCSTR lpcstr, ...);									//PlumConsole Write~(���Console)<����ı�������̨><��׼ģʽ>
	virtual void PlumConsoleWriteLineNormal(LPCSTR lpcstr, ...);								//PlumConsole Write~(���Console)<����ı�������̨><��׼ģʽ>
	virtual void PlumConsoleWriteRepeat(int Y, LPCSTR lpcstr, ...);								//PlumConsole Write~(���Console)<����ı�������̨><�ظ�ģʽ>
	virtual void PlumConsoleWriteLineRepeat(int Y, LPCSTR lpcstr, ...);							//PlumConsole Write~(���Console)<����ı�������̨><�ظ�ģʽ>

	virtual void PlumConsoleWriteA(const void* lpcszStr);										//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteA(const void* lpcszStr, int nSize);							//PlumConsole Write~(���Console)<����ı�������̨>

	virtual void PlumConsoleWriteW(const void* lpcszStr);										//PlumConsole Write~(���Console)<����ı�������̨>
	virtual void PlumConsoleWriteW(const void* lpcszStr, int nSize);							//PlumConsole Write~(���Console)<����ı�������̨>

};

#endif