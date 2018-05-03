/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		PlumConsole.h
* @brief	This Program is PlumConsole DLL Project.
* @notes	Console控制台调试
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
	HANDLE m_hConsole;							//Console Handle 控制台句柄
	CONSOLE_SCREEN_BUFFER_INFO m_sConsoleInfo;	//Console Infomation 控制台信息


public:
	CPlumConsole();								//PlumConsole 构造函数
	virtual ~CPlumConsole();					//PlumConsole 析构函数

	//访问
	HANDLE PlumConsoleGetHandle(void) const;	//PlumConsole 访问控制台句柄

	//简单
	void PlumConsoleSetConsoleTitle(LPCWSTR lpcszTitle);										//PlumConsole 设置控制台标题
	void PlumConsoleSetCursorPosition(COORD Coord);												//PlumConsole 设置光标位置

	void PlumConsoleGetScreenBufferInfo(void);													//PlumConsole 获取控制台缓冲区信息

	//初始化
	virtual void PlumConsoleInit(LPCWSTR lpcszTitle = L"Console");								//PlumConsole Init~(初始化Console)
	virtual void PlumConsoleInit(COORD Coord, LPCWSTR lpcszTitle = L"Console");					//PlumConsole Init~(初始化Console)<Console窗口位置/大小>
	virtual void PlumConsoleInit(int nWidth, int nHeight, LPCWSTR lpcszTitle = L"Console");		//PlumConsole Init~(初始化Console)<Console窗口位置/大小>

	//清空
	virtual void PlumConsoleClear(void);														//PlumConsole Clear(清空Console)<Console窗口清空>
	virtual void PlumConsoleClearLine(int Y);													//PlumConsole Clear(清空Console Line)<Console清空一行>

	//输出
	virtual void PlumConsoleWrite(const void* lpcszStr);										//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWrite(const void* lpcszStr, int nSize);								//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWrite(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWrite(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PlumConsoleWriteLine(const void* lpcszStr);									//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLine(const void* lpcszStr, int nSize);							//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLine(const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLine(const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr);						//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize);				//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);				//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr);					//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize);			//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, WORD wTextColor, bool bIsUnderLine = false);					//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLineEx(int X, int Y, const void* lpcszStr, int nSize, WORD wTextColor, bool bIsUnderLine = false);			//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PlumConsoleWriteInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);								//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);							//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PlumConsoleWriteLineInt(int nNumber, WORD wTextColor, bool bIsUnderLine = false);								//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLineFloat(float fNumber, WORD wTextColor, bool bIsUnderLine = false);							//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteLineDouble(double dNumber, WORD wTextColor, bool bIsUnderLine = false);						//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PlumConsoleWriteNormal(LPCSTR lpcstr, ...);									//PlumConsole Write~(输出Console)<输出文本到控制台><标准模式>
	virtual void PlumConsoleWriteLineNormal(LPCSTR lpcstr, ...);								//PlumConsole Write~(输出Console)<输出文本到控制台><标准模式>
	virtual void PlumConsoleWriteRepeat(int Y, LPCSTR lpcstr, ...);								//PlumConsole Write~(输出Console)<输出文本到控制台><重复模式>
	virtual void PlumConsoleWriteLineRepeat(int Y, LPCSTR lpcstr, ...);							//PlumConsole Write~(输出Console)<输出文本到控制台><重复模式>

	virtual void PlumConsoleWriteA(const void* lpcszStr);										//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteA(const void* lpcszStr, int nSize);							//PlumConsole Write~(输出Console)<输出文本到控制台>

	virtual void PlumConsoleWriteW(const void* lpcszStr);										//PlumConsole Write~(输出Console)<输出文本到控制台>
	virtual void PlumConsoleWriteW(const void* lpcszStr, int nSize);							//PlumConsole Write~(输出Console)<输出文本到控制台>

};

#endif