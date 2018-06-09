#ifndef _XHYLOGGR_H_
#define	_XHYLOGGR_H_

#include <windows.h>

#define LOGGEREXPROT extern "C"  __declspec(dllexport)

#define LOGFMT_TRACE(logger,fmt,...)	{if(logger!=NULL) logger->WriteFmtLog(LOGLEVEL_TRACE,__FILE__,__LINE__,fmt,##__VA_ARGS__);}
#define LOGFMT_DEBUG(logger,fmt,...)	{if(logger!=NULL) logger->WriteFmtLog(LOGLEVEL_DEBUG,__FILE__,__LINE__,fmt,##__VA_ARGS__);}
#define LOGFMT_INFO(logger,fmt,...)		{if(logger!=NULL) logger->WriteFmtLog(LOGLEVEL_INFO,__FILE__,__LINE__,fmt,##__VA_ARGS__);}
#define LOGFMT_WARN(logger,fmt,...)		{if(logger!=NULL) logger->WriteFmtLog(LOGLEVEL_WARN,__FILE__,__LINE__,fmt,##__VA_ARGS__);}
#define LOGFMT_ERROR(logger,fmt,...)	{if(logger!=NULL) logger->WriteFmtLog(LOGLEVEL_ERROR,__FILE__,__LINE__,fmt,##__VA_ARGS__);}
#define LOGFMT_ALARM(logger,fmt,...)	{if(logger!=NULL) logger->WriteFmtLog(LOGLEVEL_ALARM,__FILE__,__LINE__,fmt,##__VA_ARGS__);}
#define LOGFMT_FATAL(logger,fmt,...)	{if(logger!=NULL) logger->WriteFmtLog(LOGLEVEL_FATAL,__FILE__,__LINE__,fmt,##__VA_ARGS__);}

#define LOG_TRACE(logger,log)	{if(logger!=NULL) logger->WriteLog(LOGLEVEL_TRACE,__FILE__,__LINE__,log);}
#define LOG_DEBUG(logger,log)	{if(logger!=NULL) logger->WriteLog(LOGLEVEL_DEBUG,__FILE__,__LINE__,log);}
#define LOG_INFO(logger,log)	{if(logger!=NULL) logger->WriteLog(LOGLEVEL_INFO,__FILE__,__LINE__,log);}
#define LOG_WARN(logger,log)	{if(logger!=NULL) logger->WriteLog(LOGLEVEL_WARN,__FILE__,__LINE__,log);}
#define LOG_ERROR(logger,log)	{if(logger!=NULL) logger->WriteLog(LOGLEVEL_ERROR,__FILE__,__LINE__,log);}
#define LOG_ALARM(logger,log)	{if(logger!=NULL) logger->WriteLog(LOGLEVEL_ALARM,__FILE__,__LINE__,log);}
#define LOG_FATAL(logger,log)	{if(logger!=NULL) logger->WriteLog(LOGLEVEL_FATAL,__FILE__,__LINE__,log);}


//日志级别(级别越低,记录的日志越详细)
enum LOGLEVEL
{
	LOGLEVEL_TRACE = 0,  //最低级别
	LOGLEVEL_DEBUG,		//DEBUG日志		
	LOGLEVEL_INFO,		//一般日志
	LOGLEVEL_WARN,		//警告日志
	LOGLEVEL_ERROR,		//错误日志
	LOGLEVEL_ALARM,		//报警日志
	LOGLEVEL_FATAL,		//严重错误日志
};


class ITraceLogger
{
public:
	virtual ~ITraceLogger(){}
public:
	virtual bool	StartLogger() = 0;
	virtual bool	StopLogger() = 0;
	virtual bool	ReleaseLogger() = 0;

	
	//**********************************************************************
	// Method:    WriteLog
	// FullName:  IHYLogger::WriteLog
	// Returns:   bool
	// Parameter: HYLOGLEVEL iLevel			所写日志的等级
	// Parameter: const char * lpFileName	所写日志的文件名
	// Parameter: const int nFileLine		所写日志的文件行号
	// Parameter: const char * lpszLog		所写日志的内容
	// Remark:	  
	//**********************************************************************
	virtual bool	WriteLog(LOGLEVEL iLevel, const char * lpFileName,const int nFileLine,const char *lpszLog) = 0;
	//**********************************************************************
	// Method:    WriteFmtLog
	// FullName:  IHYLogger::WriteFmtLog
	// Returns:   bool __cdecl
	// Parameter: HYLOGLEVEL iLevel			所写日志的等级
	// Parameter: const char * lpFileName	所写日志的文件名
	// Parameter: const int nFileLine		所写日志的文件行号
	// Parameter: const char * lpszFmt		所写日志的内容
	// Parameter: ...						不定参数
	// Remark:	不定参数写日志的方法
	//**********************************************************************
	virtual bool __cdecl WriteFmtLog(LOGLEVEL iLevel, const char * lpFileName, const int nFileLine, const char* lpszFmt, ...) = 0;
};


//**********************************************************************
// Method:    CreateLogger
// FullName:  CreateLogger
// Returns:   bool
// Parameter: const char * lpszLogName		此参数用于输入,指定此日志文件的名称
// Parameter: const char * lpszCfg			此参数用于输入,指定日志配置文件的路径,要求全路径,不支持相对路径
// Parameter: IHYLogger * * lpLogger		此参数用于输入输出,传入的时候要求传入一个 IHYLogger* 的对象地址,此参数会传出IHYLogger对象的地址.
// Remark:	此函数用来创建一个日志对象，用此对象的成员方法可以写日志
//**********************************************************************
LOGGEREXPROT bool CreateLogger( const char* lpszLogName, const char *lpszCfg, ITraceLogger** lpLogger);

#endif