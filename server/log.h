#ifndef __LOGGER__
#define __LOGGER__

#include<string>
#include<stdint.h>
#include<memory>
#include<list>
#include<stringstream>
#include<filestream>

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

class LogFormatter
{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);
    std::string format(LogEvent::ptr event);
    const std::string getPattern() const { return m_pattern; };
    void init();
    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
public:
    class FormatItem
    {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem() {};
        virtual void format(std::ostream &os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };
private:
    std::string m_pattern;
    //日志解析后的格式
    std::vector<FormatItem::ptr> m_items;
}
//日志输出地
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}
    virtual void Log(LogLevel::Level level, 
            LogEvent::ptr event) = 0;
    void setFormatter(LogFormatter::ptr val);
    LogFormatter::ptr getFormatter() const;
    LogLevel::Level getLevel() const;
    void setLevel(LogLevel::Level val);
protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
}
class StdoutLogAppender : public LogAppender
{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void Log(LogLevel::Level level,  
            LogEvent::ptr event) override;
};
	
class FileLogAppender : public LogAppender
{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string filename);
    void Log(LogLevel::Level level,  
            LogEvent::ptr event) override;
    bool reopen();//重新打开日志文件
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

}



#endif
