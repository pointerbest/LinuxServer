#include<iostream>
#include"../server/log.h"
#include"../server/util.h"

int main()
{
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
    sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("./log.txt"));
    sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(sylar::LogLevel::ERROR);
    logger->addAppender(file_appender);

    SYLAR_LOG_INFO(logger) << "test macro";
    SYLAR_LOG_FMT_ERROR(logger, "test macro fmt error %s", "abc");

    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xx");
    SYLAR_LOG_INFO(l) << "xxx";
    return 0;
}
