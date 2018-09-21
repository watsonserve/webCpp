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
        this->onComplete(this);
    return;
}

void StreamIO::recvd()
{
    ssize_t len;
    len = Aio::aioReturn(&rd_acb);
    if(1 > len)
    {
        shutdown(rd_acb.aio_fildes, SHUT_RD);
        if(-1 == len)
        {
            inEvents->onError(this);
        }
        inEvents->onClose(this);
        if(0 == this->closed)
        {
            ::close(rd_acb.aio_fildes);
            this->closed = 1;
        }
        return;
    }
    cache.append((char*)(rd_acb.aio_buf), len); // 写入缓冲区
#ifdef debug
    printf("cache-length: %lu\n", cache.length());
#endif
    inEvents->onData(this); // 通知用户
    if(0 == this->closed)
    {
#ifdef debug
        puts("aio read next");
#endif
        if (FILE == this->type) {
            rd_acb.aio_offset += len;
        }
#ifdef debug
        printf("file-offset: %llu\n", rd_acb.aio_offset);
#endif
        Aio::aioRead(&rd_acb); // 下一次读取
    }
    // 此三者顺序不可变动，如果先调用Aio::aioRead会导致多线程同时读写cache
    return;
}

StreamIO::StreamIO()
{
    this->onComplete = NULL;
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
    if(EINPROGRESS == Aio::aioError(&rd_acb))
        Aio::aioCancel(rd_acb.aio_fildes, &rd_acb);
    ::close(rd_acb.aio_fildes);
    closed = 1;
    // puts("streamIO closed");
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

int StreamIO::isEmpty()
{
	return cache.empty() ? 1: 0;
}

std::string & StreamIO::gets(std::string &dst, LineEndFlag lineEnd)
{
    ssize_t off, lineEndLength;

    if(cache.empty())
    {
        dst.erase();
        return dst;
    }
    lineEndLength = 1;
    switch (lineEnd) {
        case CR:
            off = cache.find("\r");
            break;
        case LF:
            off = cache.find("\n");
            break;
        case CRLF:
        default:
            lineEndLength <<= 1;
            off = cache.find("\r\n");
    }
    if(-1 == off)
    {
        dst = cache.substr(0, cache.length());
        cache.erase();
        return dst;
    }
    dst = cache.substr(0, off);
    cache.erase(0, off + lineEndLength);
    return dst;
}

std::string StreamIO::gets(LineEndFlag lineEnd)
{
    std::string ret;

    return this->gets(ret, lineEnd);
}

std::string StreamIO::load(size_t len = 0)
{
    std::string ret;

    if(cache.empty() || 1 > len)
        return cache;
    ret = cache.substr(0, len);
    cache.erase(0, len);
    return ret;
}

void StreamIO::write(std::string &data, Func callback)
{
    this->write(data.c_str(), data.length(), callback);
    return;
}

void StreamIO::write(const char *buf, ssize_t len, Func callback)
{
    int err;

    wr_acb.aio_buf = (void*)buf;
    wr_acb.aio_nbytes = len;
    this->onComplete = callback;
    if(0 != Aio::aioWrite(&wr_acb)) {
        err = errno;
        this->close();
        printf("ERROR aio write %X: %s\n", err, strerror(err));
    }
    return;
}


