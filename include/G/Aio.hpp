//
//  Aio.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef Aio_h
#define Aio_h

extern "C" {
    #include <aio.h>
}
#include "G/Object.hpp"

#if !defined (__linux__) && !defined(__linux)
struct aioinit
{
    int aio_threads;   // Maximum number of threads
    int aio_num;       // Number of expected simultaneous requests
    int aio_idle_time;
};
#include "MQ.hpp"
#else
// on linux
#endif

#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <semaphore.h>

typedef struct aio_back
{
    ssize_t readyDataLen;
    int error;
} AioBack;

#endif

namespace G {
    class Aio : public Object {
        
    public:
#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
        static int kq;
        static struct kevent *eventList;
        static AioBack *abList;
        static aioinit conf;
        static sem_t * pEventSem;
        static void* listenEvnt(void *);
        static void* eventCallback(void *);
        static MQ mq;
#endif
        static int aioInit(struct aioinit *);
        static int aioRead(struct aiocb *);
        static int aioWrite(struct aiocb *);
        static ssize_t aioReturn(struct aiocb *);
        static int aioError(const struct aiocb *);
        static int aioCancel(int, struct aiocb *);
    };
}

#endif /* Aio_h */
