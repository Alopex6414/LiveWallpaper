/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, alopex
*     All rights reserved.
*
* @file		FFMpeg.h
* @brief	This Program is FFMpeg Library.
* @author	alopex
* @version	v1.00a
* @date		2017-11-29
*/
#pragma once

extern "C"
{
#include "libavcodec\avcodec.h"  
#include "libavformat\avformat.h"  
#include "libavutil\channel_layout.h"  
#include "libavutil\common.h"  
#include "libavutil\imgutils.h"  
#include "libswscale\swscale.h"   
#include "libavutil\imgutils.h"      
#include "libavutil\opt.h"         
#include "libavutil\mathematics.h"      
#include "libavutil\samplefmt.h"   
#include "libswresample/swresample.h"
};
#pragma comment(lib, "avcodec.lib")  
#pragma comment(lib, "avformat.lib")  
#pragma comment(lib, "avdevice.lib")  
#pragma comment(lib, "avfilter.lib")  
#pragma comment(lib, "avutil.lib")  
#pragma comment(lib, "postproc.lib")  
#pragma comment(lib, "swresample.lib")  
#pragma comment(lib, "swscale.lib") 
