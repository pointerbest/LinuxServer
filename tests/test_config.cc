#include"../server/log.h"
#include"../server/config.h"

sylar::ConfigVar<int>::ptr g_int = sylar::Config::Lookup("system.port", 8080, "system port");

int main()
{
    SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << g_int->getValue();
    SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << g_int->toString();

    return 0;
}
