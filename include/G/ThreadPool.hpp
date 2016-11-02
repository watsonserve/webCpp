//
//  ThreadPool.hpp
//  GHTTPd
//
//  Created by wangxingzhuo on 2016/10/26.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef ThreadPool_h
#define ThreadPool_h

#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#include <semaphore.h>
#else
#include <pthread.h>
#endif

#include "G/Object.hpp"
#include "G/Number.hpp"
#include "G/MQ.hpp"

namespace G {

    typedef void* (*Func)(void *);

    typedef struct message
    {
        void * args;
        Func function;
    } Message;

    class ThreadPool : public Object
    {
        int size;
        static void* thFunction(void *);
    protected:
        MQ<Message> mq;
        sem_t* pSem;
    public:
        ThreadPool() {};
        virtual ~ThreadPool() {};
        static int init(ThreadPool *, int, std::string &);
        static int init(ThreadPool *, int, Func, std::string &);
        static int init(ThreadPool *, int, const char *);
        static int init(ThreadPool *, int, Func, const char *);
        int call(void *);
        int call(void *, Func);
    };
}

#endif /* ThreadPool_h */
