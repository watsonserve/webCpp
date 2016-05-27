//
//  ThreadPool.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/5/21.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include "G/Object.hpp"

namespace G
{
    typedef void (*ThreadFunction)(void*);

    class ThreadPool :public Object
    {
        std::thread **pool;
        size_t max;
        ThreadFunction runner;
        static void threadFunc(ThreadPool *tPool);
    public:
        static int init(ThreadPool *tPool, size_t max, ThreadFunction runner);
        ThreadPool();
        virtual ~ThreadPool();
        virtual void call();
    };
}

#endif /* ThreadPool_hpp */
