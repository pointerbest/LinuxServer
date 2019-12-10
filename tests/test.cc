#include<iostream>
#include"../server/log.h"
#include"../server/util.h"

int main()
{
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
    SYLAR_LOG_INFO(logger) << "log info";
    return 0;
}
