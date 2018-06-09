#include "stdafx.h"
#include "CLogFactory.h"
#include "CLog4zLogger.h"

ITraceLogger* CLogFactory::CreateLogger(const std::string strLogMode, const std::string strLogName, const std::string strLogPath, const std::string strLogLevel, const int nLogSize)
{
	ITraceLogger* pLogger = NULL;
	if (strLogMode == "LOG4CPLUS")
	{
		//其他的实现方式创建其他的对象
	}
	else
	{
		pLogger = new CLog4zLogger(strLogPath,strLogName, strLogLevel, nLogSize);
	}
	return pLogger;
}