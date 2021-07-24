//
//  ThreadPool.hpp
//  GHTTPd
//
//  Created by wangxingzhuo on 2016/10/26.
//  Copyright © 2016 watsserve. All rights reserved.
//

#ifndef _ThreadPool_HPP_
#define _ThreadPool_HPP_

extern "C"
{
    #include <fcntl.h>
    #include "event/event.h"
}

#include "Object.hpp"
#include "Number.hpp"
#include "MQ.hpp"

#ifdef __LINUX__

#include <pthread.h>

#endif

namespace G
{
    class ThreadPool : virtual public Object
    {
        int size;
        static void* thFunction(void *);
    protected:
        G::MQ<struct event_t> mq;
    public:
        ThreadPool();
        virtual ~ThreadPool() {};
        static int init(ThreadPool &, int);
        int call(const struct event_t &);
    };
}

#endif /* _ThreadPool_HPP_ */
