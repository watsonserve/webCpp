#include <errno.h>
#include "G/io/io.h"

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
