//
//  Input.cpp
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
}
#include <string>
#include "G/io/StreamIO.hpp"

using namespace G;

size_t Input::bufSize = BUFSIZ;

Input* Input::init(Input *inHandle, G::IOEvents *ioEvents, void* mem, size_t memLen)
{
    memset(&(inHandle->rd_acb), 0, sizeof(struct aiocb));
    inHandle->rd_acb.aio_sigevent.sigev_notify = SIGEV_THREAD; // Notification method
    inHandle->rd_acb.aio_sigevent.sigev_value.sival_ptr = inHandle;    // Data passed with notification
    inHandle->rd_acb.aio_lio_opcode = LIO_READ;
    inHandle->rd_acb.aio_sigevent.sigev_notify_function = Input::callback;    // Function used for thread notification (SIGEV_THREAD)

    inHandle->inEvents = ioEvents;
    if(0 == memLen)
    {
        if(nullptr != mem)  // 分配未知内存
            return nullptr;

        // nullptr == mem 未分配内存 使用默认缓冲尺寸
        memLen = StreamIO::bufSize;
    }
    inHandle->rd_acb.aio_nbytes = memLen;
    if(nullptr == mem) // 未分配内存
    {
        mem = malloc(inHandle->rd_acb.aio_nbytes);
        if(nullptr == mem)
            return nullptr;
    }
    inHandle->rd_acb.aio_buf = mem;
    return inHandle;
}

Input::Input(int fd, InputHandler &handler) : IO(fd) {
    this->handler = handler;
}

void Input::callback(union sigval inHandle)
{
    ((StreamIO *)(inHandle.sival_ptr))->recvd();
}

void Input::listen()
{
    int err;

    // this->ioEvents->onConnect(this);
    if(0 != Aio::aioRead(&rd_acb)) {
        err = errno;
        ::close(rd_acb.aio_fildes);
#ifdef debug
        printf("aio %s\n", strerror(err));
#endif
        errno = err;
    }
}
