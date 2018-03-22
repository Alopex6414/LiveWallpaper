/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		LiveCoreFunction.cpp
* @brief	This Program is LiveWallpaperCore Project.
* @author	alopex
* @version	v1.00a
* @date		2018-3-10
*/
#include "LiveCoreFunction.h"

#include "PlumFile.h"
#include "PlumIni.h"

#include "FFMpeg.h"

#pragma warning (disable:4996)

// Variable Definition
int g_nLiveCoreMode = 0;
int g_nLiveCoreShowGraphics = 0;
int g_nLiveCoreShowGraphicsFont = 0;
int g_nLiveCoreWallpaperMode = 0;
int g_nLiveCoreWallpaperAudioMode = 0;
int g_nLiveCoreLogProcess = 0;
char g_chLiveCoreVideoAddress[MAX_PATH] = { 0 };

//------------------------------------------------------------------
// @Function:	 AnalyzeConfigFile()
// @Purpose: LiveWallpaperCore分析配置文件
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void AnalyzeConfigFile()
{
	char chFilePath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// 分析文件路径
	CPlumFile* pPlumFile = NULL;
	pPlumFile = new CPlumFile;
	pPlumFile->PlumFileGetModuleFileNameA(chFilePath, MAX_PATH);

	pTemp = strrchr(chFilePath, '\\');
	if (pTemp) *pTemp = '\0';
	strcat_s(chFilePath, "\\config\\LiveCore.cfg");

	char chArray[MAX_PATH] = { 0 };
	int nValue;

	// 分析配置信息
	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREMODE", "LiveCore_Mode", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreMode = nValue;	// LiveCore模式: 0~组合模式 1~分离模式

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreShowGraphics = nValue;	// LiveCore显示: 0~不显示显卡型号(fps) 1~显示显卡型号(fps)

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_GraphicsFont", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreShowGraphicsFont = nValue;	// LiveCore显示字体大小

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreWallpaperMode = nValue;	// LiveCore屏幕分辨率模式: 0~填充 1~适应 2~拉伸 3~平铺 4~居中

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreWallpaperAudioMode = nValue;	// LiveCore音频播放模式: 0~不播放音频 1~播放音频

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreLogProcess = nValue;	// LiveCore日志记录: 0~不记录过程 1~记录过程

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", 0, chArray, MAX_PATH, chFilePath);
	memcpy_s(g_chLiveCoreVideoAddress, MAX_PATH, chArray, MAX_PATH);	// LiveCore动态壁纸视频地址


	SAFE_DELETE(pPlumFile);
}

//----------------------------------------------------------------------------------------------
// @Function:	 AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight)
// @Purpose: LiveWallpaperCore分析视频信息
// @Since: v1.00a
// @Para: HWND hWnd					// 窗口句柄
// @Para: const char* pVideoPath	// 视频路径地址
// @Return: BOOL
//----------------------------------------------------------------------------------------------
BOOL AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight)
{
	AVFormatContext *pFormatCtx;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;

	av_register_all();//注册所有组件
	pFormatCtx = avformat_alloc_context();//初始化一个AVFormatContext

	// 打开输入的视频文件
	if (avformat_open_input(&pFormatCtx, pVideoPath, NULL, NULL) != 0)
	{
		MessageBox(hWnd, L"打开文件失败!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// 获取视频文件信息
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		MessageBox(hWnd, L"无法读取文件信息!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
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
		MessageBox(hWnd, L"未读取到视频信息!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	pCodecCtx = pFormatCtx->streams[VideoIndex]->codec;

	//查找解码器
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		MessageBox(hWnd, L"未查找到解码器!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//打开解码器
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		MessageBox(hWnd, L"无法打开解码器!", L"错误", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	*pWidth = pCodecCtx->width;
	*pHeight = pCodecCtx->height;

	avcodec_close(pCodecCtx);
	avformat_free_context(pFormatCtx);

	return TRUE;
}

//------------------------------------------------------------------
// @Function:	 LiveRunPreProcess()
// @Purpose: LiveWallpaperCore运行分离桌面进程
// @Since: v1.00a
// @Para: None
// @Return: BOOL
//------------------------------------------------------------------
BOOL LiveRunPreProcess()
{
	BOOL bRet;

	STARTUPINFOA si = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFOA);
	GetStartupInfoA(&si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	char chFilePath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// 分析文件路径
	CPlumFile* pPlumFile = NULL;
	pPlumFile = new CPlumFile;
	pPlumFile->PlumFileGetModuleFileNameA(chFilePath, MAX_PATH);

	pTemp = strrchr(chFilePath, '\\');
	if (pTemp) *pTemp = '\0';
	strcat_s(chFilePath, "\\LiveWallpaperPre.dll");

	bRet = CreateProcessA(chFilePath, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	if (bRet)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	SAFE_DELETE(pPlumFile);

	return bRet;
}

//------------------------------------------------------------------
// @Function:	 IsProcessExist()
// @Purpose: LiveWallpaperCore检测进程是否存在
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
BOOL IsProcessExist(const WCHAR* strFilename)
{
	BOOL bRet = FALSE;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32)) {
		do {
			if (_wcsicmp(pe32.szExeFile, strFilename) == 0) {
				bRet = TRUE;
				break;
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}
	else {
		bRet = FALSE;
	}
	CloseHandle(hProcessSnap);
	return bRet;
}

//------------------------------------------------------------------
// @Function:	 LiveCoreReStartProcess()
// @Purpose: LiveCoreReStart启动进程
// @Since: v1.00a
// @Para: const char* pStrArr	//进程名称
// @Return: BOOL (TRUE:成功, FALSE:失败)
//------------------------------------------------------------------
BOOL LiveCoreReStartProcess(const char* pStrArr)
{
	BOOL bResult;

	STARTUPINFOA si = { 0 };
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(STARTUPINFOA);
	GetStartupInfoA(&si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi = { 0 };
	ZeroMemory(&pi, sizeof(pi));

	char chProcessPath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	GetModuleFileNameA(NULL, chProcessPath, MAX_PATH);
	pTemp = strrchr(chProcessPath, '\\');
	if (pTemp) *pTemp = '\0';
	strcat_s(chProcessPath, "\\");
	strcat_s(chProcessPath, pStrArr);

	CHAR chCmdLine[MAX_PATH] = { 0 };
	strcat_s(chCmdLine, chProcessPath);
	strcat_s(chCmdLine, " LiveWallpaperReStart.exe");

	bResult = CreateProcessA(chProcessPath, chCmdLine, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);

	if (bResult)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	return bResult;
}