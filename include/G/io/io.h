#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>

typedef enum fd_type
{
    FD_FILE,
    FD_SOCKET,
} FdType;

inline ssize_t putin(int, FdType, char *, ssize_t);

inline ssize_t putout(int, FdType, const char *, ssize_t);

inline ssize_t block_read(int, FdType, char *, ssize_t);

inline int min(int, int);

#endif
