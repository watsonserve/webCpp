#ifndef _G_LOG_H_
#define _G_LOG_H_

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdarg.h>
#include <assert.h>

void log_set_fd(int stream, int fd);
void log_set_time_fmt(const char *fmt, size_t len);
int log_print(int lev, const char *fmt, ...);
int log_warn(const char *fmt, ...);
int log_error(const char *fmt, ...);

#endif
