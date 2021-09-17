//
// Created by wlb on 2021/9/17.
//

#include "Logger.h"


//检查文件(所有类型,包括目录和文件)是否存在
//返回1:存在 0:不存在
int IsFileExist(const char* path)
{
    return !access(path, F_OK);
}

namespace wlb
{

Logger* Logger::s_Instance = new Logger;

Logger *Logger::getInstance()
{
    return s_Instance;
}

Logger::Logger()
{
    initFilePath();
}

Logger::~Logger()
{
    if (m_oStream.is_open())
        m_oStream.close();
}

void Logger::initFilePath()
{
    if (m_oStream.is_open())
    {
        m_oStream.close();
    }
    
    char name[256];
    snprintf(name, 256,
             "log/%d.log",
             getpid()
             );
    
    if (!IsFileExist("log"))
    {
        mkdir("log", 477);
    }
    m_oStream.open(name, std::ios::out);
}

LogHelper_ptr Logger::Write(const char*   level,
                            const char*   file,
                            int           lineNo,
                            const char*   date,
                            const char*   _time,
                            const char*   _func)
{
    m_mMutex.lock();
    
    char head[256];
    snprintf(head, 256,
             "\n++ %s %s %s :: %d \n|| %s: %s : ",
             date,
             _time,
             file,
             lineNo,
             level,
             _func);
    
    m_oStream << head;
    return std::make_shared<LogHelper>(this);
}

void Logger::commit()
{
    m_oStream << "\n\n";
    
    m_oStream.flush();
    
    if ((++m_iTimes %= m_iCheckTimes) == 0)
    {
        if (getFileSize() >= m_maxFileSize)
            initFilePath();
    }
    
    
    m_mMutex.unlock();
}


}


