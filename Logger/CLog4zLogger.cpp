#include "stdafx.h"
#include "CLog4zLogger.h"



zsummer::log4z::ILog4zManager *CLog4zLogger::m_lpLog4zMgr=NULL;
bool CLog4zLogger::m_bInitialize=false;

CLog4zLogger::CLog4zLogger()
{

}

CLog4zLogger::CLog4zLogger(std::string strPath, std::string strName, std::string strLevel, int nLimitSize)
{
	if (!m_bInitialize)
	{
		m_lpLog4zMgr = zsummer::log4z::ILog4zManager::GetInstance();
		m_lpLog4zMgr->Start();
		m_bInitialize = true;
	}

	if (m_lpLog4zMgr != NULL)
	{
		m_strLogName = strName;
		m_strLogPath = strPath;
		m_strLogLevel = strLevel;
		m_nLogLimitSize = nLimitSize;

		if (m_strLogLevel == "TRACE")
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_TRACE);
		}
		else if (m_strLogLevel == "DEBUG")
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_DEBUG);
		}
		else if (m_strLogLevel == "INFO")
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_INFO);
		}
		else if (m_strLogLevel == "WARNING")
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_WARN);
		}
		else if (m_strLogLevel == "ERROR")
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_ERROR);
		}
		else if (m_strLogLevel == "ALARM")
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_ALARM);
		}
		else if (m_strLogLevel == "FATAL")
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_FATAL);
		}
		else//默认为INFO级别
		{
			m_loggerID = m_lpLog4zMgr->CreateLogger(m_strLogName.c_str(), m_strLogPath.c_str(), LOG_LEVEL_INFO);
		}

		m_lpLog4zMgr->SetLoggerLimitSize(m_loggerID, m_nLogLimitSize);
	}
}
	

CLog4zLogger::~CLog4zLogger()
{}

bool CLog4zLogger::StartLogger()
{
	return true;
}

bool CLog4zLogger::StopLogger()
{
	if (m_lpLog4zMgr != NULL)
	{
		m_lpLog4zMgr->CloseLogger(m_loggerID);
	}	
	return true;
}

bool CLog4zLogger::ReleaseLogger()
{
	return true;
}

bool CLog4zLogger::WriteLog(LOGLEVEL iLevel, const char * lpFileName, const int nFileLine, const char *lpszLog)
{
	const int BUFFER_SIZE = 1024;
	char szPrefixLogBuffer[BUFFER_SIZE] = { 0 };
	sprintf_s(szPrefixLogBuffer, (BUFFER_SIZE - 1), "|%s:%d| %s", lpFileName, nFileLine, lpszLog);

	LOG_FORMAT(m_loggerID, iLevel, lpFileName, nFileLine, szPrefixLogBuffer);
	return true;
}

bool CLog4zLogger::WriteFmtLog(LOGLEVEL iLevel, const char * lpFileName, const int nFileLine, const char* lpszFmt, ...)
{
	const int BUFFER_SIZE = 1024;
	const int PREFIX_SIZE = 50;
	char szLogBuffer[BUFFER_SIZE] = { 0 };
	va_list argList;
	va_start(argList, lpszFmt);
	//_snprintf_s(szLogBuffer, BUFFER_SIZE, lpszFmt, argList);
	_vsnprintf_s(szLogBuffer, (BUFFER_SIZE- PREFIX_SIZE), lpszFmt, argList);
	va_end(argList);


	char szPrefixLogBuffer[BUFFER_SIZE] = { 0 };
	sprintf_s(szPrefixLogBuffer, (BUFFER_SIZE-1), "|%s:%d| %s", lpFileName, nFileLine, szLogBuffer);

	LOG_FORMAT(m_loggerID, iLevel, lpFileName, nFileLine, szPrefixLogBuffer);
	return true;
}


