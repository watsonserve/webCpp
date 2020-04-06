#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>

typedef enum fd_type
{
    FD_FILE,
    FD_SOCKET,
} FdType;

inline ssize_t putin(int fd, FdType type, char *buf, ssize_t len)
{
    switch (type)
    {
        case FD_SOCKET:
            return recv(fd, buf, len, 0);
        default:
            return read(fd, buf, len);
    }
}

inline ssize_t putout(int fd, FdType type, const char *buf, ssize_t len)
{
    switch (type)
    {
        case FD_SOCKET:
            return send(fd, buf, len, 0);
        default:
            return write(fd, buf, len);
    }
}

inline ssize_t block_read(int fd, FdType type, char *buf, ssize_t space_siz)
{
    ssize_t len;
    do
    {
        len = putin(fd, type, buf, space_siz);
        if (-1 != len) break;
    } while (EAGAIN == errno);
    return len;
}

inline int min(int foo, int bar)
{
    return foo < bar ? foo : bar;
}

#endif
