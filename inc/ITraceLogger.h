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


//��־����(����Խ��,��¼����־Խ��ϸ)
enum LOGLEVEL
{
	LOGLEVEL_TRACE = 0,  //��ͼ���
	LOGLEVEL_DEBUG,		//DEBUG��־		
	LOGLEVEL_INFO,		//һ����־
	LOGLEVEL_WARN,		//������־
	LOGLEVEL_ERROR,		//������־
	LOGLEVEL_ALARM,		//������־
	LOGLEVEL_FATAL,		//���ش�����־
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
	// Parameter: HYLOGLEVEL iLevel			��д��־�ĵȼ�
	// Parameter: const char * lpFileName	��д��־���ļ���
	// Parameter: const int nFileLine		��д��־���ļ��к�
	// Parameter: const char * lpszLog		��д��־������
	// Remark:	  
	//**********************************************************************
	virtual bool	WriteLog(LOGLEVEL iLevel, const char * lpFileName,const int nFileLine,const char *lpszLog) = 0;
	//**********************************************************************
	// Method:    WriteFmtLog
	// FullName:  IHYLogger::WriteFmtLog
	// Returns:   bool __cdecl
	// Parameter: HYLOGLEVEL iLevel			��д��־�ĵȼ�
	// Parameter: const char * lpFileName	��д��־���ļ���
	// Parameter: const int nFileLine		��д��־���ļ��к�
	// Parameter: const char * lpszFmt		��д��־������
	// Parameter: ...						��������
	// Remark:	��������д��־�ķ���
	//**********************************************************************
	virtual bool __cdecl WriteFmtLog(LOGLEVEL iLevel, const char * lpFileName, const int nFileLine, const char* lpszFmt, ...) = 0;
};


//**********************************************************************
// Method:    CreateLogger
// FullName:  CreateLogger
// Returns:   bool
// Parameter: const char * lpszLogName		�˲�����������,ָ������־�ļ�������
// Parameter: const char * lpszCfg			�˲�����������,ָ����־�����ļ���·��,Ҫ��ȫ·��,��֧�����·��
// Parameter: IHYLogger * * lpLogger		�˲��������������,�����ʱ��Ҫ����һ�� IHYLogger* �Ķ����ַ,�˲����ᴫ��IHYLogger����ĵ�ַ.
// Remark:	�˺�����������һ����־�����ô˶���ĳ�Ա��������д��־
//**********************************************************************
LOGGEREXPROT bool CreateLogger( const char* lpszLogName, const char *lpszCfg, ITraceLogger** lpLogger);

#endif