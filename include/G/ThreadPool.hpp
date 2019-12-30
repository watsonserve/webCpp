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
}

#include "G/Object.hpp"
#include "G/Number.hpp"
#include "G/MQ.hpp"
#include "G/event/Event.hpp"
#ifdef __LINUX__
#include <pthread.h>
#endif

namespace G {

    class Exeable : virtual public Object
    {
        public:
            void *context;
            void (*function)(Exeable *);
            Exeable();
            virtual ~Exeable();
    };

    class ThreadPool : virtual public Object
    {
        int size;
        static void* thFunction(void *);
    protected:
        MQ<G::Exeable> mq;
    public:
        ThreadPool();
        virtual ~ThreadPool() {};
        static int init(ThreadPool &, int);
        int call(G::Exeable &);
    };
}

#endif /* _ThreadPool_HPP_ */
