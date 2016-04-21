#ifndef __ZLOG_H__
#define __ZLOG_H__

#include <stdio.h>


int DEBUG_LEVEL = 0;

#define DBG_FROMAT  "[%s %04d-%02d-%02d %02d:%02d:%02d %s:%d] "

enum DEBUG_LEVEL_ENUM{
    DEBUG_NONE = 0,
    DEBUG_ERR,
    DEBUG_WARN,
    DEBUG_INFO,
    DEBUG_NOTICE,
    DEBUG_DEBUG,
    DEBUG_MAX,
};

#define SET_DEBUG(level) do{DEBUG_LEVEL = level; } while(0)
#define INIT_DEBUG()     do{DEBUG_LEVEL = DEBUG_NONE; } while(0)

#define ZLOG_ERROR(fmt, arg...)     do { if (DEBUG_ERR <= DEBUG_LEVEL) {\
												time_t nowtime;\
												struct tm *timeinfo;\
												time( &nowtime );\
												timeinfo = localtime( &nowtime );\
												fprintf(stderr, DBG_FROMAT fmt "\n", "E", \
														timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,\
														__FUNCTION__, __LINE__, ##arg);}} while(0)

#define ZLOG_WARN(fmt, arg...)       do { if (DEBUG_WARN <= DEBUG_LEVEL) {\
												time_t nowtime;\
												struct tm *timeinfo;\
												time( &nowtime );\
												timeinfo = localtime( &nowtime );\
												fprintf(stderr, DBG_FROMAT fmt "\n", "W", \
														timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,\
														__FUNCTION__, __LINE__, ##arg);}} while(0)

#define ZLOG_INFO(fmt, arg...)       do { if (DEBUG_INFO <= DEBUG_LEVEL) {\
												time_t nowtime;\
												struct tm *timeinfo;\
												time( &nowtime );\
												timeinfo = localtime( &nowtime );\
												fprintf(stderr, DBG_FROMAT fmt "\n", "I", \
														timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,\
														__FUNCTION__, __LINE__, ##arg);}} while(0)

#define ZLOG_NOTICE(fmt, arg...)       do { if (DEBUG_NOTICE <= DEBUG_LEVEL) {\
												time_t nowtime;\
												struct tm *timeinfo;\
												time( &nowtime );\
												timeinfo = localtime( &nowtime );\
												fprintf(stderr, DBG_FROMAT fmt "\n", "N", \
														timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,\
														__FUNCTION__, __LINE__, ##arg);}} while(0)

#define ZLOG_DEBUG(fmt, arg...)       do { if (DEBUG_DEBUG <= DEBUG_LEVEL) {\
												time_t nowtime;\
												struct tm *timeinfo;\
												time( &nowtime );\
												timeinfo = localtime( &nowtime );\
												fprintf(stderr, DBG_FROMAT fmt "\n", "D", \
														timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,\
														__FUNCTION__, __LINE__, ##arg);}} while(0)

#define ZLOG(dst, fmt, arg...)       do { if (DEBUG_DEBUG <= DEBUG_LEVEL) {\
												time_t nowtime;\
												struct tm *timeinfo;\
												time( &nowtime );\
												timeinfo = localtime( &nowtime );\
												fprintf(dst, DBG_FROMAT fmt "\n", "A", \
														timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,\
														__FUNCTION__, __LINE__, ##arg);}} while(0)


#endif
