#pragma once
#ifndef __LOG4ZLOGGER_H__
#define __LOG4ZLOGGER_H__

#include "log4z.h"
#include "ITraceLogger.h"

class CLog4zLogger: public ITraceLogger
{
public:
	CLog4zLogger();
	CLog4zLogger(std::string, std::string, std::string, int);
	virtual ~CLog4zLogger();

	virtual bool	StartLogger();
	virtual bool	StopLogger();
	virtual bool	ReleaseLogger();

	virtual bool	WriteLog(LOGLEVEL iLevel, const char * lpFileName, const int nFileLine, const char *lpszLog);
	virtual bool __cdecl WriteFmtLog(LOGLEVEL iLevel, const char * lpFileName, const int nFileLine, const char* lpszFmt, ...);

private:
	LoggerId	m_loggerID;
	std::string m_strLogPath;
	std::string m_strLogName;
	std::string	m_strLogLevel;
	int			m_nLogLimitSize;

	static zsummer::log4z::ILog4zManager *m_lpLog4zMgr;
	static bool m_bInitialize;

};

#endif