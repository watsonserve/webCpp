//
//  ThreadPool.hpp
//  GHTTPd
//
//  Created by wangxingzhuo on 2016/10/26.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _ThreadPool_HPP_
#define _ThreadPool_HPP_

extern "C"
{
    #include <fcntl.h>
    #include "G/Event.h"
}

#include "G/Object.hpp"
#include "G/Number.hpp"
#include "G/MQ.hpp"
#ifdef __LINUX__
#include <pthread.h>
#endif

namespace G {

    class ThreadPool : public Object
    {
        int size;
        static void* thFunction(void *);
    protected:
        MQ<G::event_data_t> mq;
    public:
        ThreadPool();
        virtual ~ThreadPool() {};
        static int init(ThreadPool &, int);
        int call(G::event_data_t &);
    };
}

#endif /* _ThreadPool_HPP_ */
