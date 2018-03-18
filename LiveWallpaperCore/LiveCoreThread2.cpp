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
// @Purpose: CLiveCoreThread2���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread2::CLiveCoreThread2()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreThread2()
// @Purpose: CLiveCoreThread2��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread2::~CLiveCoreThread2()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThreadRun��Ƶ�����߳�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CLiveCoreThread2::PlumThreadRun()
{
	AVFormatContext *pFormatCtx;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;

	av_register_all();//ע���������
	pFormatCtx = avformat_alloc_context();//��ʼ��һ��AVFormatContext

	//���������Ƶ�ļ�
	if (avformat_open_input(&pFormatCtx, g_chLiveCoreVideoAddress, NULL, NULL) != 0)
	{
		MessageBox(g_hWnd, L"���ļ�ʧ��!", L"����", MB_OK | MB_ICONERROR);
		return;
	}

	//��ȡ��Ƶ�ļ���Ϣ
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		MessageBox(g_hWnd, L"�޷���ȡ�ļ���Ϣ!", L"����", MB_OK | MB_ICONERROR);
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
		MessageBox(g_hWnd, L"δ��ȡ����Ƶ��Ϣ!", L"����", MB_OK | MB_ICONERROR);
		return;
	}

	pCodecCtx = pFormatCtx->streams[AudioIndex]->codec;

	//���ҽ�����
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		MessageBox(g_hWnd, L"δ���ҵ�������!", L"����", MB_OK | MB_ICONERROR);
		return;
	}

	//�򿪽�����
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		MessageBox(g_hWnd, L"�޷��򿪽�����!", L"����", MB_OK | MB_ICONERROR);
		return;
	}

}