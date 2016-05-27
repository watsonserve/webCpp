//
//  ThreadPool.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/5/21.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef Thread_hpp
#define Thread_hpp

#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include "G/Object.hpp"

namespace G {
    class ThreadPool :public Object {
        std::thread **pool;
        size_t max;
        static void threadFunc(ThreadPool &tPool) {
            tPool.threadCallback();
        }
        virtual void threadCallback() {
            
        }
    public:
        static int init(ThreadPool &tPool, size_t max) {
            tPool.max = max;
            tPool.pool = (std::thread**)malloc(sizeof(std::thread *) * max);
            if(NULL == tPool.pool)
                return -1;
            for(int i=0; i<max; i++) {
                tPool.pool[i] = new std::thread(threadFunc, tPool);
                if(NULL == tPool.pool[i])
                    exit(1);
                tPool.pool[i]->detach();
            }
            return 0;
        }
        ThreadPool() {};
        virtual ~ThreadPool() {
            for(int i=0; i<max; i++)
                delete pool[i];
            free(pool);
        };
    };
}

#endif /* Thread_hpp */
