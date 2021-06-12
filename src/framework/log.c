#include "G/log.h"

#ifndef TIME_FMT

#define YEAR 1900 + gm.tm_year
#define MON 1 + gm.tm_mon
#define MDAY gm.tm_mday
#define HOUR gm.tm_hour
#define MIN gm.tm_min
#define SEC gm.tm_sec
#define MSEC msec

#define TIME_LEN 32
#define TIME_FMT "%4d%02d%02d-%02d:%02d:%02d.%03d-UTC", YEAR, MON, MDAY, HOUR, MIN, SEC, MSEC

#endif

#ifndef _FUNC_LOG__LOG_FMT__
#define _FUNC_LOG__LOG_FMT__
#define LOG(_LOG_FMT_, fmt) \
    do { \
        va_list args; \
        const size_t len = TIME_LEN + 16 + strlen(fmt); \
        char buf[len], str_now[TIME_LEN]; \
        str_utc_time(str_now, TIME_LEN); \
        snprintf(buf, len, _LOG_FMT_, str_now, fmt); \
        va_start(args, fmt); \
        int ret = vprintf(buf, args); \
        va_end(args); \
        return ret; \
    } while(0)
#endif

static int log_out_stream = 1;
static int log_error_stream = 2;


void log_set_fd(int stream, int fd)
{
    switch (stream)
    {
        case 1:
            log_out_stream = fd;
            break;
        case 2:
            log_error_stream = fd;
            break;
        default:
            break;
    }
}

char * str_utc_time(char *buf, size_t len)
{
    int msec;
    struct timeval tm;
    struct tm gm;

    gettimeofday(&tm, NULL);
    msec = tm.tv_usec / 1000;
    gmtime_r(&tm.tv_sec, &gm);

    snprintf(buf, len, TIME_FMT);
    return buf;
}

int log_print(int lev, const char *fmt, ...)
{
    va_list args;
    const size_t len = TIME_LEN + 16 + strlen(fmt);
    char buf[len], str_now[TIME_LEN];
    str_utc_time(str_now, TIME_LEN);
    snprintf(buf, len, "[%s] lev=%d %s\n", str_now, lev, fmt);
    va_start(args, fmt);
    int ret = vprintf(buf, args);
    va_end(args);
    return ret;
}

int log_warn(const char *fmt, ...)
{
    LOG("[%s] WARN: %s\n", fmt);
}

int log_error(const char *fmt, ...)
{
    LOG("[%s] ERROR: %s\n", fmt);
}
