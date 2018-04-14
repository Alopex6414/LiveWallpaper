/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreUnpackThread.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-4-12
*/
#include "LiveCore.h"
#include "LiveCoreUnpackThread.h"

#include "PlumCipherA.h"
#include "PlumCrypt.h"
#include "PlumPack.h"

//------------------------------------------------------------------
// @Function:	 CLiveCoreUnpackThread()
// @Purpose: CLiveCoreUnpackThread构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreUnpackThread::CLiveCoreUnpackThread()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreUnpackThread()
// @Purpose: CLiveCoreUnpackThread析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreUnpackThread::~CLiveCoreUnpackThread()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThreadRun视频解包线程
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CLiveCoreUnpackThread::PlumThreadRun()
{
	CPlumPack* pUnPacker = new CPlumPack;

	int nUnpackSize = 0;
	int nUnpackCount = 0;

	pUnPacker->PlumUnPackFilePackerA((const char*)g_chDefaultVideoAddress, (const char*)g_chDefaultVideoDirector, &nUnpackSize, &nUnpackCount, g_chDefaultVideoUnpack, MAX_PATH);

	delete pUnPacker;
}