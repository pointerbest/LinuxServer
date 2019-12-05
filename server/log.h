#ifndef __LOGGER__
#define __LOGGER__

#include<string>
#include<stdint.h>
#include<memory>
#include<list>

namespace sylar
{

class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
private:
    const char* m_file = nullptr;
    int32_t m_line = 0;
    uint32_t m_elapse = 0;//程序启动到现在的毫米数
    uint32_t m_fiberId = 0;
    uint32_t m_threadId = 0;
    uint64_t m_time;
    std::string m_content;

};

class LogLevel
{
public:
    enum Level
    {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
}

class LogFormatter
{
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    std::string format(LogEvent::ptr event);
}
//日志输出地
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}
    void Log(LogLevel::Level level, LogEvent::ptr event);
private:
    LogLevel::Level m_level;
}

//日志器
class Logger
{
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger(const std::string& name = "root");
    void log(LogLevel::Level le, LogEvent::ptr event);
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);
    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const { return m_level };
    void setLevel(LogLevel::Level val) { m_level = val };
private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;
};  

class StdoutLogAppender : public LogAppender
{

};
	
class FileLogAppender : public LogAppender
{

};

}



#endif
