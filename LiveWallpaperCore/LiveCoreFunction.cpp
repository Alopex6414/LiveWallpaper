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
// @Purpose: LiveWallpaperCore���������ļ�
// @Since: v1.00a
// @Para: None
// @Return: None
//------------------------------------------------------------------
void AnalyzeConfigFile()
{
	char chFilePath[MAX_PATH] = { 0 };
	char* pTemp = NULL;

	// �����ļ�·��
	CPlumFile* pPlumFile = NULL;
	pPlumFile = new CPlumFile;
	pPlumFile->PlumFileGetModuleFileNameA(chFilePath, MAX_PATH);

	pTemp = strrchr(chFilePath, '\\');
	if (pTemp) *pTemp = '\0';
	strcat_s(chFilePath, "\\config\\LiveCore.cfg");

	char chArray[MAX_PATH] = { 0 };
	int nValue;

	// ����������Ϣ
	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREMODE", "LiveCore_Mode", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreMode = nValue;	// LiveCoreģʽ: 0~���ģʽ 1~����ģʽ

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_Graphics", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreShowGraphics = nValue;	// LiveCore��ʾ: 0~����ʾ�Կ��ͺ�(fps) 1~��ʾ�Կ��ͺ�(fps)

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORESHOW", "LiveCore_Show_GraphicsFont", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreShowGraphicsFont = nValue;	// LiveCore��ʾ�����С

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Mode", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreWallpaperMode = nValue;	// LiveCore��Ļ�ֱ���ģʽ: 0~��� 1~��Ӧ 2~���� 3~ƽ�� 4~����

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREWALLPAPERMODE", "LiveCore_Wallpaper_Audio", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreWallpaperAudioMode = nValue;	// LiveCore��Ƶ����ģʽ: 0~��������Ƶ 1~������Ƶ

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECORELOGMODE", "LiveCore_Log_Process", 0, chArray, MAX_PATH, chFilePath);
	nValue = atoi(chArray);
	g_nLiveCoreLogProcess = nValue;	// LiveCore��־��¼: 0~����¼���� 1~��¼����

	memset(chArray, 0, MAX_PATH);
	GetPrivateProfileStringA("LIVECOREVIDEOADDRESS", "LiveCore_Video_Address", 0, chArray, MAX_PATH, chFilePath);
	memcpy_s(g_chLiveCoreVideoAddress, MAX_PATH, chArray, MAX_PATH);	// LiveCore��̬��ֽ��Ƶ��ַ


	SAFE_DELETE(pPlumFile);
}

//----------------------------------------------------------------------------------------------
// @Function:	 AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight)
// @Purpose: LiveWallpaperCore������Ƶ��Ϣ
// @Since: v1.00a
// @Para: HWND hWnd					// ���ھ��
// @Para: const char* pVideoPath	// ��Ƶ·����ַ
// @Return: BOOL
//----------------------------------------------------------------------------------------------
BOOL AnalyzeVideoInfo(HWND hWnd, const char* pVideoPath, int* pWidth, int* pHeight)
{
	AVFormatContext *pFormatCtx;
	AVCodecContext  *pCodecCtx;
	AVCodec         *pCodec;

	av_register_all();//ע���������
	pFormatCtx = avformat_alloc_context();//��ʼ��һ��AVFormatContext

	// ���������Ƶ�ļ�
	if (avformat_open_input(&pFormatCtx, pVideoPath, NULL, NULL) != 0)
	{
		MessageBox(hWnd, L"���ļ�ʧ��!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	// ��ȡ��Ƶ�ļ���Ϣ
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		MessageBox(hWnd, L"�޷���ȡ�ļ���Ϣ!", L"����", MB_OK | MB_ICONERROR);
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
		MessageBox(hWnd, L"δ��ȡ����Ƶ��Ϣ!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	pCodecCtx = pFormatCtx->streams[VideoIndex]->codec;

	//���ҽ�����
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		MessageBox(hWnd, L"δ���ҵ�������!", L"����", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//�򿪽�����
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		MessageBox(hWnd, L"�޷��򿪽�����!", L"����", MB_OK | MB_ICONERROR);
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
// @Purpose: LiveWallpaperCore���з����������
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

	// �����ļ�·��
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
// @Purpose: LiveWallpaperCore�������Ƿ����
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
// @Purpose: LiveCoreReStart��������
// @Since: v1.00a
// @Para: const char* pStrArr	//��������
// @Return: BOOL (TRUE:�ɹ�, FALSE:ʧ��)
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