/**
 * @Author: Xia Yunkai
 * @Date:   2024-03-23 21:16:13
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-04-27 22:32:38
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <ctime>
#include <cstdio>
#include <string>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>

static const std::string GetCurTimeStr()
{
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(tp);
    struct tm now_time;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    localtime_s(&now_time, &tt);
#else
    now_time = *std::localtime(&tt);
#endif
    std::ostringstream oss;
    oss << std::put_time(&now_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

#if (_WIN32 || WIN64)
#define MYFILE(x) strrchr(x, '\\') ? strrchr(x, '\\') + 1 : x
#else
#define MYFILE(x) strrchr(x, '/') ? strrchr(x, '/') + 1 : x
#endif

#define LOG_COLOR_NONE "\033[m"
#define LOG_COLOR_RED "\033[0;32;31m"
#define LOG_COLOR_GREEN "\033[0;32;32m"
#define LOG_COLOR_LIGHT_GREEN "\033[1;32m"
#define LOG_COLOR_BLUE "\033[0;32;34m"
#define LOG_COLOR_LIGHT_BLUE "\033[1;34m"
#define LOG_COLOR_DARY_GRAY "\033[1;30m"
#define LOG_COLOR_CYAN "\033[0;36m"
#define LOG_COLOR_LIGHT_CYAN "\033[1;36m"
#define LOG_COLOR_PURPLE "\033[0;35m"
#define LOG_COLOR_LIGHT_PURPLE "\033[1;35m"
#define LOG_COLOR_BROWN "\033[0;33m"
#define LOG_COLOR_YELLOW "\033[1;33m"
#define LOG_COLOR_LIGHT_GRAY "\033[0;37m"
#define LOG_COLOR_WHITE "\033[1;37m"

#define LOG_FATAL(fmt, ...) printf(LOG_COLOR_RED "[%s] [FATAL] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) printf(LOG_COLOR_PURPLE "[%s] [ERROR] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) printf(LOG_COLOR_YELLOW "[%s] [WARN] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...) printf(LOG_COLOR_LIGHT_GREEN "[%s] [NOTICE] [%s:%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) printf(LOG_COLOR_GREEN "[%s] [INFO] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) printf(LOG_COLOR_LIGHT_BLUE "[%s] [DEBUG] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...) printf(LOG_COLOR_CYAN "[%s] [TRACE] [%s:%d]: " fmt "\n" LOG_COLOR_NONE, GetCurTimeStr().data(), MYFILE(__FILE__), __LINE__, ##__VA_ARGS__)

#endif /* __LOGGER_H__ */
