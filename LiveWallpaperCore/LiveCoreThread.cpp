/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreThread.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2017-11-29
*/
#include "LiveCore.h"
#include "LiveCoreThread.h"
#include "LiveCoreFunction.h"

#include "FFMpeg.h"

#include "WinUtilities.h"

#pragma warning (disable:4996)

//------------------------------------------------------------------
// @Function:	 CLiveCoreThread()
// @Purpose: CLiveCoreThread���캯��
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread::CLiveCoreThread()
{
}

//------------------------------------------------------------------
// @Function:	 ~CLiveCoreThread()
// @Purpose: CLiveCoreThread��������
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
CLiveCoreThread::~CLiveCoreThread()
{
}

//------------------------------------------------------------------
// @Function:	 PlumThreadRun()
// @Purpose: PlumThreadRun��Ƶ�����߳�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void WINAPI CLiveCoreThread::PlumThreadRun()
{
	AVFormatContext *pFormatCtx;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;
	AVFrame			*pFrame;
	AVFrame			*pFrameYUV;

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

	int VideoIndex = -1;

	for (int i = 0; i < pFormatCtx->nb_streams; i++)
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			VideoIndex = i;
			break;
		}
	}

	if (VideoIndex == -1)
	{
		MessageBox(g_hWnd, L"δ��ȡ����Ƶ��Ϣ!", L"����", MB_OK | MB_ICONERROR);
		return;
	}

	pCodecCtx = pFormatCtx->streams[VideoIndex]->codec;

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

	uint8_t *OutBuffer;
	AVPacket *Packet;

	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

	OutBuffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
	avpicture_fill((AVPicture *)pFrameYUV, OutBuffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
	Packet = (AVPacket *)av_malloc(sizeof(AVPacket));

	int nSize = pCodecCtx->width * pCodecCtx->height;

	g_nVideoWidth = pCodecCtx->width;
	g_nVideoHeight = pCodecCtx->height;

	g_pArrayY = new unsigned char[nSize];
	g_pArrayU = new unsigned char[nSize];
	g_pArrayV = new unsigned char[nSize];
	memset(g_pArrayY, 0, nSize);
	memset(g_pArrayU, 0, nSize);
	memset(g_pArrayV, 0, nSize);

	av_dump_format(pFormatCtx, 0, g_chLiveCoreVideoAddress, 0);

	//��ȡһ֡ѹ������
	int ret;
	int got_picture;
	int y_size;
	struct SwsContext *img_convert_ctx;

	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	while (true)
	{

		while (av_read_frame(pFormatCtx, Packet) >= 0)
		{
			if (Packet->stream_index == VideoIndex)
			{
				ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, Packet);//����һ֡ѹ������
				if (ret < 0)
				{
					return;
				}
				if (got_picture)
				{
					sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
					y_size = pCodecCtx->width*pCodecCtx->height;

					EnterCriticalSection(&g_csDecode);
					memset(g_pArrayY, 0, nSize);
					memset(g_pArrayU, 0, nSize);
					memset(g_pArrayV, 0, nSize);
					memcpy_s(g_pArrayY, nSize, pFrameYUV->data[0], y_size);
					memcpy_s(g_pArrayU, nSize, pFrameYUV->data[1], y_size / 4);
					memcpy_s(g_pArrayV, nSize, pFrameYUV->data[2], y_size / 4);
					g_bDecodeFlag = true;
					LeaveCriticalSection(&g_csDecode);
				}
			}
			av_free_packet(Packet);
		}

		while (true)
		{
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, Packet);
			if (ret < 0)
			{
				break;
			}

			if (!got_picture)
			{
				break;
			}

			sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
			y_size = pCodecCtx->width*pCodecCtx->height;

			EnterCriticalSection(&g_csDecode);
			memset(g_pArrayY, 0, nSize);
			memset(g_pArrayU, 0, nSize);
			memset(g_pArrayV, 0, nSize);
			memcpy_s(g_pArrayY, nSize, pFrameYUV->data[0], y_size);
			memcpy_s(g_pArrayU, nSize, pFrameYUV->data[1], y_size / 4);
			memcpy_s(g_pArrayV, nSize, pFrameYUV->data[2], y_size / 4);
			g_bDecodeFlag = true;
			LeaveCriticalSection(&g_csDecode);
		}

		ret = av_seek_frame(pFormatCtx, VideoIndex, pFormatCtx->streams[VideoIndex]->start_time, 0);
		if (ret < 0)
		{
			break;
		}

		avcodec_flush_buffers(pFormatCtx->streams[VideoIndex]->codec);
	}

	sws_freeContext(img_convert_ctx);

	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}