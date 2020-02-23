#ifndef _G_STREAMCACHE_HPP_
#define _G_STREAMCACHE_HPP_

extern "C"
{
    #include <stdio.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/socket.h>
    #include "G/io/io.h"
}

namespace G
{
    class StreamCache
    {
        static const int CACHESIZ = 4096;
        int fd;
        enum fd_type type;
        char buf[CACHESIZ];
        ssize_t offset, length, unread_size;
    protected:
        void setCacheFd(int, enum fd_type);
        int in_cache(ssize_t);
    public:
        ssize_t read(char *, ssize_t);
    };
}

#endif
