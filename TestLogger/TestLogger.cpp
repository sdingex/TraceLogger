// TestLogger.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "..\\inc\\ITraceLogger.h"
#include<string>


#pragma comment(lib,"..\\bin\\TraceLogger.lib")

ITraceLogger *g_plogger = NULL;

bool InitLogger()
{
	UINT nLogLevel = 0;
	char szLogCfg[260] = { 0 };
	char szPath[260] = { 0 };
	char szDrive[12] = { 0 };
	char szDir[260] = { 0 };
	char szAppPath[MAX_PATH] = { 0 };
	char szAppName[64] = { 0 };
	char szLogName[128] = { 0 };

	if (g_plogger == NULL)
	{
		GetModuleFileName(NULL, szPath, 260);
		_splitpath_s(szPath, szDrive, 12, szDir, 260, szAppName, 64, NULL, 0);
		memset(szPath, 0, sizeof(szPath));
		sprintf_s(szLogCfg, "%s%slogconfig.ini", szDrive, szDir);
		sprintf_s(szLogName, "%s", szAppName);

		if (!CreateLogger(szLogName, szLogCfg, &g_plogger))
		{
			g_plogger = NULL;
			return false;
		}
		g_plogger->StartLogger();
	}
	else
	{
		return false;
	}
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{

	InitLogger();

	LOGFMT_TRACE(g_plogger, "start trace %s", "11111111");
	LOGFMT_DEBUG(g_plogger, "start debug %s", "11111111");

	system("pause");

	return 0;
}

