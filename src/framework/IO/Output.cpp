//
//  Output.cpp
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
#include "G/io/Output.hpp"

using namespace G;

void Output::callback(union sigval outHandle)
{
    ((Output*)(outHandle.sival_ptr))->sent();
}

Output* Output::init(Output* outHandle, IOEvents* outEvents)
{
    memset(&(outHandle->wr_acb), 0, sizeof(struct aiocb));
    outHandle->wr_acb.aio_sigevent.sigev_notify = SIGEV_THREAD; // Notification method
    outHandle->wr_acb.aio_sigevent.sigev_value.sival_ptr = outHandle;    // Data passed with notification
    outHandle->wr_acb.aio_lio_opcode = LIO_WRITE;
    outHandle->wr_acb.aio_sigevent.sigev_notify_function = Output::callback;    // Function used for thread notification (SIGEV_THREAD)
    outHandle->outEvents = outEvents;
    return outHandle;
}

