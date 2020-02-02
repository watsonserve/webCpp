//
//  ThreadPool.cpp
//
//  Created by 王兴卓 on 16/10/26.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/ThreadPool.hpp"

using namespace G;

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

ThreadPool::ThreadPool() {}

// 默认线程
void* ThreadPool::thFunction(void* that)
{
    // G::Event &event;
    MQ<G::Event> &mq = ((ThreadPool *)that)->mq;

    while (1)
    {
        // 读消息队列
        G::Event event = mq.front();
        if(nullptr == event.function) {
            continue;
        }
        // 调用业务函数
        event.function(event);
    }

    return nullptr;
}

// 初始化
int ThreadPool::init(ThreadPool &self, int max)
{
    int i;
    pthread_t tid;

    self.size = max;

    // 初始化消息队列
    if (0 != MQ<G::Event>::init(&(self.mq))) {
        perror("init message queue faild");
        return -1;
    }

    // 创建线程
    for(i = 0; i < max; i++)
    {
        #ifdef __BSD__
            tid = nullptr;
        #else
            tid ^= tid;
        #endif
        if(0 != pthread_create(&tid, nullptr, ThreadPool::thFunction, &self)) {
            perror("create a work thread faild");
            return -1;
        }
        if(0 != pthread_detach(tid)) {
            perror("detach a work thread faild");
            return -1;
        }
    }
    return 0;
}

// 向线程池委托任务
int ThreadPool::call(const G::Event &msg)
{
    // 写消息队列
    return this->mq.push(msg);
}
