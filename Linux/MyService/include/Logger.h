//
// Created by wlb on 2021/9/17.
//

#ifndef MYSERVICE_LOGGER_H
#define MYSERVICE_LOGGER_H

#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <mutex>
#include <memory>

#define ERROR "ERROR"
#define INFO  "INFO"
#define DEBUG "DEBUG"

int IsFileExist(const char* path);

namespace wlb
{

    class LogHelper;

    using LogHelper_ptr = std::shared_ptr<LogHelper>;

    class Logger
    {
        // Singleton
    public:
        static Logger* getInstance();
        void operator=(Logger*) = delete;
        Logger(const Logger&) = delete;
    private:
        Logger();
        ~Logger();
        static Logger* s_Instance;


        // Logger
    public:
        LogHelper_ptr   Write(const char* level,
                              const char* file,
                              int           lineNo,
                              const char* date,
                              const char* _time,
                              const char* _func);
        std::ofstream& GetStream() { return m_oStream; }
        void            commit();

    private:
        void            initFilePath();
        int             getFileSize() { return m_oStream.tellp(); }

    private:
        const int       m_maxFileSize = 10 * 1024 * 1024;  // 10MB
        const int       m_iCheckTimes = 10;
        int             m_iTimes{ 0 };

        std::ofstream   m_oStream;
        std::mutex      m_mMutex;

    };

    class LogHelper
    {
    public:
        LogHelper(Logger* log) { _log = log; }
        ~LogHelper() { _log->commit(); }
        std::ofstream& Get() { return _log->GetStream(); };
    private:
        Logger* _log;
    };

#define LOG(level) \
    Logger::getInstance()->Write(level, __FILE__, __LINE__, \
                        __DATE__, __TIME__, __FUNCTION__)->Get()
}

/*WARNING !!!
* Cant use by this:
*
*    LOG(xxx) << func();
*
*    func() { LOG(xxx); }
*/
#endif //MYSERVICE_LOGGER_H
