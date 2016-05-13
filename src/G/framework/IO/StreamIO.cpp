//
//  IO.cpp
//  GHTTPd
//
//  Created by JamesWatson on 16/4/14.
//  Copyright © 2016年 watsserve. All rights reserved.
//

extern "C" {
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <errno.h>
    #include <aio.h>
    #include <fcntl.h>
    #include <sys/socket.h>
}
#include <string>
#include "G/GUtil.hpp"
#include "G/StreamIO.hpp"

using namespace G;

void StreamIO::sent()
{
    if(NULL != onComplete)
        onComplete(this);
    return;
}

void StreamIO::recvd()
{
    ssize_t len;
    len = aio_return(&rd_acb);
    if(1 > len)
    {
        shutdown(rd_acb.aio_fildes, SHUT_RD);
        if(-1 == len)
        {
            inEvents->onError(this);
        }
        inEvents->onClose(this);
        if(0 == closed)
        {
            ::close(rd_acb.aio_fildes);
            closed = 1;
        }
        return;
    }
    cache.append((char*)(rd_acb.aio_buf), len); // 写入缓冲区
    inEvents->onData(this); // 通知用户
    if(0 == closed)
    {
        puts("aio read next");
        aio_read(&rd_acb); // 下一次读取
    }
    // 此三者顺序不可变动，如果先调用aio_read会导致多线程同时读写cache
    return;
}

StreamIO::StreamIO()
{
    onComplete = NULL;
    return;
}

void StreamIO::setFd(int fd, HandleType type)
{
    rd_acb.aio_fildes = fd;
    wr_acb.aio_fildes = fd;
    this->type = type;
    closed ^= closed;
    return;
}

int StreamIO::getFd()
{
    return rd_acb.aio_fildes;
}

void StreamIO::close()
{
    if(EINPROGRESS == aio_error(&rd_acb))
        aio_cancel(rd_acb.aio_fildes, &rd_acb);
    ::close(rd_acb.aio_fildes);
    closed = 1;
    puts("streamIO closed");
    return;
}

StreamIO* StreamIO::init(StreamIO *ioHandle, G::IOEvents *ioEvents, void* mem, size_t memLen)
{
    Input::init(ioHandle, ioEvents, mem, memLen);
    Output::init(ioHandle, ioEvents);
    return ioHandle;
}

void StreamIO::cleanCache()
{
    cache.clear();
}

std::string StreamIO::gets()
{
    ssize_t off;
    std::string ret;

    if(cache.empty())
        return cache;
    off = cache.find("\r\n");
    if(-1 == off)
        off = cache.length();
    ret = cache.substr(0, off);
    cache.erase(0, off);
    return ret;
}

void StreamIO::write(std::string &data, OutBack callback)
{
    this->write(data.c_str(), data.length(), callback);
    return;
}

void StreamIO::write(const char *buf, ssize_t len, OutBack callback)
{
    int err;

    wr_acb.aio_buf = (void*)buf;
    wr_acb.aio_nbytes = len;
    onComplete = callback;
    if( 0 != aio_write(&wr_acb)) {
        err = errno;
        this->close();
        printf("ERROR aio write %X: %s\n", err, strerror(err));
    }
    return;
}


