//
//  ThreadPool.hpp
//  GHTTPd
//
//  Created by wangxingzhuo on 2016/10/26.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef ThreadPool_h
#define ThreadPool_h

extern "C"
{
    #include <fcntl.h>
    #include "sem.h"
}

#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)

#else
#include <pthread.h>
#endif

#include "G/Object.hpp"
#include "G/Number.hpp"
#include "G/MQ.hpp"

namespace G {

    class ThreadPool : public Object
    {
    public:
        typedef void* (*Func)(void *);

        typedef struct message
        {
            void * args;
            Func function;
        } Message;

        ThreadPool();
        virtual ~ThreadPool() {};
        static int init(ThreadPool *, int);
        static int init(ThreadPool *, int, Func);
        int call(void *);
        int call(void *, Func);
    private:
        int size;
        static void* thFunction(void *);
    protected:
        MQ<Message> mq;
        sem_t pSem;
    };
}

#endif /* ThreadPool_h */
