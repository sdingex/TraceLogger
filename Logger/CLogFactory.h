#pragma once 
#ifndef __LOGFACOTRY_H__
#define __LOGFACOTRY_H__

#include "ITraceLogger.h"

class CLogFactory
{
public:
	static ITraceLogger* CreateLogger(const std::string strLogMode,const std::string strLogName,const std::string strLogPath,const std::string strLogLevel,const int nLogSize);
	
};

#endif