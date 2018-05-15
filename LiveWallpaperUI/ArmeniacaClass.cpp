/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		ArmeniacaClass.cpp
* @brief	This Program is Armeniaca Dynamic Link Library Class Project.
* @author	alopex
* @version	v0.01a
* @date		2018-4-21	v0.01a	alopex	Create Project.
*/
#include "ArmeniacaClass.h"

//This Project is Class With Dynamic Load DLL.(Simple)

//------------------------------------------------------------------
// @Function:	 CArmeniacaExport()
// @Purpose: CArmeniacaExport构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CArmeniacaExport::CArmeniacaExport()
{
	m_hModule = NULL;

	Armeniaca_IsProcessExistA = NULL;
	Armeniaca_IsProcessExistW = NULL;
	Armeniaca_StartProcessA = NULL;
	Armeniaca_StartProcessW = NULL;
	Armeniaca_Convert_A2W_Safe = NULL;
	Armeniaca_Convert_W2A_Safe = NULL;
	Armeniaca_Convert_A2W_UnSafe = NULL;
	Armeniaca_Convert_W2A_UnSafe = NULL;
	Armeniaca_Convert_A2W_UnSafe2 = NULL;
	Armeniaca_Convert_W2A_UnSafe2 = NULL;
}

//------------------------------------------------------------------
// @Function:	 ~CArmeniacaExport()
// @Purpose: CArmeniacaExport析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CArmeniacaExport::~CArmeniacaExport()
{
	if (m_hModule)
	{
		FreeLibrary(m_hModule);
	}
}

//------------------------------------------------------------------
// @Function:	 ArmeniacaExportInit()
// @Purpose: CArmeniacaExport初始化
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL ARMENIACACLASS_CALLMODE CArmeniacaExport::ArmeniacaExportInit()
{
	m_hModule = LoadLibraryA("Armeniaca.dll");
	if (!m_hModule)
	{
		return FALSE;
	}

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 ArmeniacaImportFunctionAll()
// @Purpose: CArmeniacaExport导入函数(ALL)
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL ARMENIACACLASS_CALLMODE CArmeniacaExport::ArmeniacaImportFunctionAll()
{
	Armeniaca_IsProcessExistA = (ARMENIACA_ISPROCESSEXISTA)::GetProcAddress(m_hModule, "Armeniaca_Process_IsProcessExistA");
	if (!Armeniaca_IsProcessExistA)
	{
		return FALSE;
	}

	Armeniaca_IsProcessExistW = (ARMENIACA_ISPROCESSEXISTW)::GetProcAddress(m_hModule, "Armeniaca_Process_IsProcessExistW");
	if (!Armeniaca_IsProcessExistW)
	{
		return FALSE;
	}

	Armeniaca_StartProcessA = (ARMENIACA_STARTPROCESSA)::GetProcAddress(m_hModule, "Armeniaca_Process_StartProcessA");
	if (!Armeniaca_StartProcessA)
	{
		return FALSE;
	}

	Armeniaca_StartProcessW = (ARMENIACA_STARTPROCESSW)::GetProcAddress(m_hModule, "Armeniaca_Process_StartProcessW");
	if (!Armeniaca_StartProcessW)
	{
		return FALSE;
	}

	Armeniaca_Convert_A2W_Safe = (ARMENIACA_CONVERT_A2W_SAFE)::GetProcAddress(m_hModule, "Armeniaca_Convert_A2W_Safe");
	if (!Armeniaca_Convert_A2W_Safe)
	{
		return FALSE;
	}

	Armeniaca_Convert_W2A_Safe = (ARMENIACA_CONVERT_W2A_SAFE)::GetProcAddress(m_hModule, "Armeniaca_Convert_W2A_Safe");
	if (!Armeniaca_Convert_W2A_Safe)
	{
		return FALSE;
	}

	Armeniaca_Convert_A2W_UnSafe = (ARMENIACA_CONVERT_A2W_UNSAFE)::GetProcAddress(m_hModule, "Armeniaca_Convert_A2W_UnSafe");
	if (!Armeniaca_Convert_A2W_UnSafe)
	{
		return FALSE;
	}

	Armeniaca_Convert_W2A_UnSafe = (ARMENIACA_CONVERT_W2A_UNSAFE)::GetProcAddress(m_hModule, "Armeniaca_Convert_W2A_UnSafe");
	if (!Armeniaca_Convert_W2A_UnSafe)
	{
		return FALSE;
	}

	Armeniaca_Convert_A2W_UnSafe2 = (ARMENIACA_CONVERT_A2W_UNSAFE2)::GetProcAddress(m_hModule, "Armeniaca_Convert_A2W_UnSafe2");
	if (!Armeniaca_Convert_A2W_UnSafe2)
	{
		return FALSE;
	}

	Armeniaca_Convert_W2A_UnSafe2 = (ARMENIACA_CONVERT_W2A_UNSAFE2)::GetProcAddress(m_hModule, "Armeniaca_Convert_W2A_UnSafe2");
	if (!Armeniaca_Convert_W2A_UnSafe2)
	{
		return FALSE;
	}

	return TRUE;
}