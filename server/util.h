#ifndef __SERVER_UTIL_H__
#define __SERVER_UTIL_H__

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

namespace sylar{

/**
 *  * @brief 返回当前线程的ID
 *   */
pid_t GetThreadId();

/**
 *  * @brief 返回当前协程的ID
 *   */
uint32_t GetFiberId();

}
#endif
