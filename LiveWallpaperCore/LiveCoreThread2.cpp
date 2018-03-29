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
#include "SDL2.h"

#include "WinUtilities.h"

#pragma warning (disable:4996)

#define MAX_AUDIO_FRAME_SIZE 192000

//Variable
static  Uint8  *audio_chunk;
static  Uint32  audio_len;
static  Uint8  *audio_pos;

//Function
void Audio_CallBack(void *udata, Uint8 *stream, int len);

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
	AVPacket        *packet;
	AVFrame         *pFrame; 
	uint8_t         *out_buffer;
	int				ret;
	uint32_t		len = 0;
	int				got_picture;
	int				index = 0;

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
		//MessageBox(g_hWnd, L"δ��ȡ����Ƶ��Ϣ!", L"����", MB_OK | MB_ICONERROR);
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

	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	av_init_packet(packet);

	//Out Audio Param  
	uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
	//nb_samples: AAC-1024 MP3-1152  
	int out_nb_samples = pCodecCtx->frame_size;
	AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
	int out_sample_rate = 44100;
	int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
	//Out Buffer Size  
	int out_buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 1);

	out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
	pFrame = av_frame_alloc();

	//��ʼ��SDL
	if (SDL_Init(SDL_INIT_AUDIO))
	{
		MessageBox(g_hWnd, L"SDL��ʼ��ʧ��!", L"����", MB_OK | MB_ICONERROR);
		return;
	}

	SDL_AudioSpec wanted_spec;

	wanted_spec.freq = pCodecCtx->sample_rate;	//����Ƶ��
	wanted_spec.format = AUDIO_S16SYS;			//������Ƶ���ݸ�ʽ
	wanted_spec.channels = pCodecCtx->channels;	//����ͨ��
	wanted_spec.silence = 0;					//��������ֵ
	wanted_spec.samples = 1024;					//������������С
	wanted_spec.callback = Audio_CallBack;		//��ƵCallBack
	wanted_spec.userdata = pCodecCtx;

	//SDL����Ƶ
	if (SDL_OpenAudio(&wanted_spec, NULL) < 0)
	{
		MessageBox(g_hWnd, L"�޷�����Ƶ!", L"����", MB_OK | MB_ICONERROR);
		return;
	}

	int64_t in_channel_layout;
	struct SwrContext *au_convert_ctx;

	in_channel_layout = av_get_default_channel_layout(pCodecCtx->channels);

	au_convert_ctx = swr_alloc();
	au_convert_ctx = swr_alloc_set_opts(au_convert_ctx, out_channel_layout, out_sample_fmt, out_sample_rate,
		in_channel_layout, pCodecCtx->sample_fmt, pCodecCtx->sample_rate, 0, NULL);
	swr_init(au_convert_ctx);

	//Play  
	SDL_PauseAudio(0);

	while (av_read_frame(pFormatCtx, packet) >= 0) 
	{
		if (packet->stream_index == AudioIndex)
		{
			ret = avcodec_decode_audio4(pCodecCtx, pFrame, &got_picture, packet);
			if (ret < 0) 
			{
				return;
			}
			if (got_picture > 0) 
			{
				swr_convert(au_convert_ctx, &out_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pFrame->data, pFrame->nb_samples);
				index++;
			}


			while (audio_len>0)//Wait until finish  
				SDL_Delay(1);

			//Set audio buffer (PCM data)  
			audio_chunk = (Uint8 *)out_buffer;
			//Audio buffer length  
			audio_len = out_buffer_size;
			audio_pos = audio_chunk; 
		}
		av_free_packet(packet);
	}

	swr_free(&au_convert_ctx);
 
	SDL_CloseAudio();//Close SDL  
	SDL_Quit();

	av_free(out_buffer);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}

//------------------------------------------------------------------
// @Function:	 Audio_CallBack()
// @Purpose: Audio_CallBack��Ƶ����ص�����
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void Audio_CallBack(void *udata, Uint8 *stream, int len) 
{
	SDL_memset(stream, 0, len);
	if (audio_len == 0)
		return;

	len = (len>audio_len ? audio_len : len);

	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;
}
