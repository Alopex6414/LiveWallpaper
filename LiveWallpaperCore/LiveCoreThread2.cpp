/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreThread2.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-3-11
*/
#include "LiveCore.h"
#include "LiveCoreThread2.h"
#include "LiveCoreFunction.h"

#include "FFMpeg.h"

#include "WinUtilities.h"

#pragma warning (disable:4996)

//------------------------------------------------------------------
// @Function:	 CLiveCoreThread2()
// @Purpose: CLiveCoreThread2构造函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread2::CLiveCoreThread2()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreThread2()
// @Purpose: CLiveCoreThread2析构函数
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread2::~CLiveCoreThread2()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThreadRun音频解码线程
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CLiveCoreThread2::PlumThreadRun()
{
	AVFormatContext *pFormatCtx;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;

	av_register_all();//注册所有组件
	pFormatCtx = avformat_alloc_context();//初始化一个AVFormatContext

	//打开输入的视频文件
	if (avformat_open_input(&pFormatCtx, g_chLiveCoreVideoAddress, NULL, NULL) != 0)
	{
		MessageBox(g_hWnd, L"打开文件失败!", L"错误", MB_OK | MB_ICONERROR);
		return;
	}

	//获取视频文件信息
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		MessageBox(g_hWnd, L"无法读取文件信息!", L"错误", MB_OK | MB_ICONERROR);
		return;
	}

	int AudioIndex = -1;

	for (int i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			AudioIndex = i;
			break;
		}
	}

	if (AudioIndex == -1)
	{
		MessageBox(g_hWnd, L"未读取到音频信息!", L"错误", MB_OK | MB_ICONERROR);
		return;
	}

	pCodecCtx = pFormatCtx->streams[AudioIndex]->codec;

	//查找解码器
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		MessageBox(g_hWnd, L"未查找到解码器!", L"错误", MB_OK | MB_ICONERROR);
		return;
	}

	//打开解码器
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		MessageBox(g_hWnd, L"无法打开解码器!", L"错误", MB_OK | MB_ICONERROR);
		return;
	}

}