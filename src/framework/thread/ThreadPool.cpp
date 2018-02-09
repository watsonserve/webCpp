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
    Message message;
    sem_t *pSem;
    MQ<Message> *mq;
    ThreadPool *self;

    self = (ThreadPool *)args;
    pSem = &(self->pSem);
    mq = &(self->mq);

    while (1)
    {
        // 等待信号量
        if(0 != wait_sem(pSem)) {
            perror("wait a sem");
            exit(1);
        }

        // 读消息队列
        message = (Message)(mq->front());
        if(NULL == message.function) {
            continue;
        }
        message.function(message.args);
    }

    return NULL;
}

// 初始化
int ThreadPool::init(ThreadPool * self, int max, Func function)
{
    int i;
    // pthread_attr_t attr;
    pthread_t tid;

    self->size = max;

    // 初始化消息队列
    if (0 != MQ<Message>::init(&(self->mq))) {
        perror("init message queue faild");
        return -1;
    }

    // 初始化信号量
    if (0 != init_sem(&(self->pSem), 0, 0)) {
        perror("init named sem faild");
        return -1;
    }

    // 创建线程
//    if(0 != pthread_attr_init(&attr)) {
//        perror("init thread attr faild");
//        return -1;
//    }

    for(i = 0; i < max; i++)
    {
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

// 向线程池委托任务
int ThreadPool::call(void * args)
{
    return this->call(args, NULL);
}

// 向线程池委托任务
int ThreadPool::call(void * args, Func function)
{
    Message message;

    message.args = args;
    message.function = function;

     // 写消息队列
    this->mq.push(message);
    return post_sem(&this->pSem);
}
