// Logger.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ITraceLogger.h"
#include "CLogFactory.h"
#include <process.h>

HANDLE hDll = NULL;
HANDLE hTimer = NULL;
int	   g_nSaveLogDay = 7;//日志默认保存7天

unsigned __stdcall DeleteLogFileFunc(void* pArg)
{
	char szDllPath[MAX_PATH] = { 0 };
	char szDrive[10] = { 0 };
	char szDir[MAX_PATH] = { 0 };
	char szFileName[MAX_PATH] = { 0 };
	if (GetModuleFileName((HMODULE)hDll, szDllPath, MAX_PATH) != 0)
	{
		_splitpath_s(szDllPath, szDrive, 10, szDir, MAX_PATH, NULL, 0, NULL, 0);
		_snprintf_s(szFileName, MAX_PATH, "%s%slog\\*.*", szDrive, szDir);
	}

	LONGLONG nSaveTotalTime = (LONGLONG)g_nSaveLogDay * 24 * 60 * 60 * 10000000;//100-nanosecond unit

	while (true)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(hTimer, INFINITE))
		{
			WIN32_FIND_DATAA FindFileData;
			ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
			HANDLE hFile = FindFirstFileA(szFileName, &FindFileData);
			BOOL IsFinded = TRUE;
			while (IsFinded)
			{
				if (strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..")) //如果不是"." ".."目录
				{			
					SYSTEMTIME stUTC;
					FILETIME ftUTC;
					GetSystemTime(&stUTC);
					SystemTimeToFileTime(&stUTC, &ftUTC);

					LARGE_INTEGER liNow, liFile;
					liNow.LowPart = ftUTC.dwLowDateTime;
					liNow.HighPart = ftUTC.dwHighDateTime;
					liFile.LowPart = FindFileData.ftLastWriteTime.dwLowDateTime;
					liFile.HighPart = FindFileData.ftLastWriteTime.dwHighDateTime;

					if (liNow.QuadPart - liFile.QuadPart >= nSaveTotalTime)
					{
						std::string strFileName = "";
						strFileName = strFileName + szDrive + szDir + "log\\" + FindFileData.cFileName;
						DeleteFileA(strFileName.c_str());
					}					
				}

				IsFinded = FindNextFileA(hFile, &FindFileData);    //递归搜索其他的文件
			}
			FindClose(hFile);

		}
	}
	return 0;
}

bool CreateLogger(const char* lpszLogName, const char *lpszCfg, ITraceLogger** lpLogger)
{
	bool bRet = false;
	if (lpszLogName != NULL && lpszCfg != NULL && lpLogger != NULL)
	{
		char szMode[MAX_PATH] = { 0 };
		char szLogPath[MAX_PATH] = { 0 };
		char szLevel[MAX_PATH] = { 0 };
		int	nLogLimitSize = 0;
		char szDllPath[MAX_PATH] = { 0 };
		char szDrive[10] = { 0 };
		char szDir[MAX_PATH] = { 0 };
		if (GetModuleFileName((HMODULE)hDll, szDllPath, MAX_PATH) != 0)
		{
			_splitpath_s(szDllPath, szDrive, 10, szDir, MAX_PATH, NULL, 0, NULL, 0);
			memset(szDllPath, 0, MAX_PATH);
			_snprintf_s(szDllPath, MAX_PATH, "%s%slog", szDrive, szDir);

			GetPrivateProfileString("LOGGERCFG", "MODE", "LOG4Z", szMode, MAX_PATH, lpszCfg);
			GetPrivateProfileString("LOGGERCFG", "LOGPATH", szDllPath, szLogPath, MAX_PATH, lpszCfg);
			if (strcmp(szLogPath, "") == 0)
			{
				strncpy_s(szLogPath, sizeof(szLogPath), szDllPath, strlen(szDllPath));
			}
			GetPrivateProfileString("LOGGERCFG", "LEVEL", "TRACE", szLevel, MAX_PATH, lpszCfg);
			

			nLogLimitSize = GetPrivateProfileInt("LOGGERCFG", "LIMITSIZE", 10, lpszCfg);
			g_nSaveLogDay = GetPrivateProfileInt("LOGGERCFG", "SAVELOGDAY", 7, lpszCfg);

			*lpLogger = CLogFactory::CreateLogger(szMode, lpszLogName, szLogPath, szLevel, nLogLimitSize);

			if (*lpLogger != NULL)
			{
				hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
				if (hTimer != NULL)
				{
					SYSTEMTIME st;
					FILETIME ftLocal, ftUTC;
					GetLocalTime(&st);
					st.wHour = 0;
					st.wMinute = 0;
					st.wSecond = 0;
					st.wMilliseconds = 0;

					/*st.wYear = 2017;
					st.wMonth = 1;
					st.wDay = 17;
					st.wHour = 2;
					st.wMinute = 10;
					st.wSecond = 0;
					st.wMilliseconds = 0;*/

					SystemTimeToFileTime(&st, &ftLocal);
					LocalFileTimeToFileTime(&ftLocal, &ftUTC);
					LARGE_INTEGER li;
					li.LowPart = ftUTC.dwLowDateTime;
					li.HighPart = ftUTC.dwHighDateTime;

					int nTimePeriod = 24 * 60 * 60 * 1000;//一天执行一次
					//int nTimePeriod = 30 * 1000;

					if (0 != SetWaitableTimer(hTimer, &li, nTimePeriod, NULL, NULL, FALSE))
					{
						_beginthreadex(NULL, 0, &DeleteLogFileFunc, NULL, 0, NULL);
					}					
				}
				bRet = true;
			}
		}

			

	}
	return bRet;
}