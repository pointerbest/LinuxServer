#include"log.h"

namespace sylar
{

Logger::Logger(const std::string& name): m_name(name)
{

}
void Logger::log(LogLevel::Level le, LogEvent::ptr event)
{
    if (le >= m_level)
    {
        for (auto& it : m_appenders)
        {
            it->Log(le, event);
        }   
    }
}
void Logger::debug(LogEvent::ptr event)
{
    log(LogLevel::DEBUG, event);
}
void Logger::info(LogEvent::ptr event)
{
    log(LogLevel::INFO, event);
}
void Logger::warn(LogEvent::ptr event)
{
    log(LogLevel::WARN, event);
}
void Logger::error(LogEvent::ptr event)
{
    log(LogLevel::ERROR, event);
}
void Logger::fatal(LogEvent::ptr event)
{
    log(LogLevel::FATAL, event);
}
void Logger::addAppender(LogAppender::ptr appender)
{
    m_appenders.push(appender);

}
void Logger::delAppender(LogAppender::ptr appender)
{
    for (auto it = m_appenders.begin(); 
            it != m_appenders.end(); ++it)
    {
        if (*it == appender)
        {
            m_appenders.erase(it);
            break;
        }
    }
}

void LogAppender::setFormatter(LogFormatter::ptr val)
{
    m_formatter = val;
}
LogFormatter::ptr LogAppender::getFormatter()
{
    return m_formatter;
}
LogLevel::Level LogAppender::getLevel()
{
    return m_level;
}
void LogAppender::setLevel(LogLevel::Level val)
{
    m_level = val;
}

FileLogAppender::FileLogAppender(const std::string filename)
{
    m_filename = filename;
}
void FileLogAppender::Log(LogLevel::Level level,  
            LogEvent::ptr event)
{
    if (level >= m_level)
    {
        m_filestream << m_formatter->format(event);
    }
}
bool FileLogAppender::reopen()
{
    if (m_filestream)
    {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return m_filestream;
}

void StdoutLogAppender::Log(LogLevel::Level level,
        LogEvent::ptr event)
{
    if (level >= m_level)
    {
        std::cout << m_formatter->format(event);
    }
}
LogFormatter::LogFormatter(const std::string &pattern) : m_pattern(pattern)
{
    init();
}

std::string LogFormatter::format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    std::stringstream ss;
    for(auto& i : m_items) {
        i->format(ss, logger, level, event);
    }
    return ss.str();
}

std::ostream& LogFormatter::format(std::ostream& ofs, std::shared_ptr<Logger> logger,
        LogLevel::Level level, LogEvent::ptr event) {
    for(auto& i : m_items) {
        i->format(ofs, logger, level, event);
    }
    return ofs;
}


}
