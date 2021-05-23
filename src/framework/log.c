#include "G/log.h"

static int log_out_stream = 1;
static int log_error_stream = 2;
static size_t TIME_LEN = 32;
static char TIME_FMT[BUFSIZ] = "%4d%02d%02d-%02d:%02d:%02d.%03d-UTC";

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

void log_set_time_fmt(const char *fmt, size_t len)
{
    assert(len + 1 < BUFSIZ);
    memcpy(TIME_FMT, fmt, len);
    TIME_FMT[len] = 0;
    TIME_LEN = len;
}

char * str_utc_time(char *buf, const char *fmt, size_t len)
{
    int millisecond;
    struct timeval tm;
    struct tm gm;

    gettimeofday(&tm, NULL);
    millisecond = tm.tv_usec / 1000;
    gmtime_r(&tm.tv_sec, &gm);

    snprintf(buf, len, fmt, 1900 + gm.tm_year, 1 + gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec, millisecond);
    return buf;
}


#define LOG(_LOG_FMT_) \
    do { \
        va_list args; \
        const size_t len = TIME_LEN + 16 + strlen(fmt); \
        char buf[len], str_now[TIME_LEN]; \
        str_utc_time(str_now, TIME_FMT, TIME_LEN); \
        snprintf(buf, len, _LOG_FMT_, str_now, fmt); \
        va_start(args, fmt); \
        int ret = vprintf(buf, args); \
        va_end(args); \
        return ret; \
    } while(0)

int log_print(int lev, const char *fmt, ...)
{
    va_list args;
    const size_t len = TIME_LEN + 16 + strlen(fmt);
    char buf[len], str_now[TIME_LEN];
    str_utc_time(str_now, TIME_FMT, TIME_LEN);
    snprintf(buf, len, "[%s] lev=%d %s\n", str_now, lev, fmt);
    va_start(args, fmt);
    int ret = vprintf(buf, args);
    va_end(args);
    return ret;
}

int log_warn(const char *fmt, ...)
{
    LOG("[%s] WARN: %s\n");
}

int log_error(const char *fmt, ...)
{
    LOG("[%s] ERROR: %s\n");
}
