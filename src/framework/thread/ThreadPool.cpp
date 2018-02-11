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

ThreadPool::ThreadPool()
{
    this->isA = "ThreadPool";
}

// 默认线程
void* ThreadPool::thFunction(void* args)
{
    message_t message;
    MQ<message_t> *mq;
    ThreadPool *self;

    self = (ThreadPool *)args;
    mq = &(self->mq);

    while (1)
    {

        // 读消息队列
        message = (message_t)(mq->front());
        if(NULL == message.function) {
            continue;
        }

        // 调用业务函数
        message.function(message.args);
    }

    return NULL;
}

// 初始化
int ThreadPool::init(ThreadPool * self, int max, Func function)
{
    int i;
    pthread_t tid;

    self->size = max;

    // 初始化消息队列
    if (0 != MQ<message_t>::init(&(self->mq))) {
        perror("init message queue faild");
        return -1;
    }

    // 创建线程
    for(i = 0; i < max; i++)
    {
#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
        tid = NULL;
#else
        tid ^= tid;
#endif
        if(0 != pthread_create(&tid, NULL, function, self)) {
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

// 默认线程池
int ThreadPool::init(ThreadPool * self, int max)
{
    return ThreadPool::init(self, max, self->thFunction);
}

// 向线程池委托任务，调起默认
int ThreadPool::call(void * args)
{
    return this->call(args, NULL);
}

// 向线程池委托任务
int ThreadPool::call(void * args, Func function)
{
    message_t message;

    message.args = args;
    message.function = function;

     // 写消息队列
    return this->mq.push(message);
}
