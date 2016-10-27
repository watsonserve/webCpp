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
#include "G/Number.hpp"

// 默认线程
void* ThreadPool::thFunction(void* args)
{
    Message *message;
    sem_t *pSem;
    MQ<Message> *mq;
    ThreadPool *self;

    self = (ThreadPool *)args;
    pSem = self->pSem;
    mq = &(self->mq);

    while (1)
    {
        // 等待信号量
        if(0 != sem_wait(pSem)) {
            perror("wait a sem");
            exit(1);
        }
        // 读消息队列
        message = (Message*)(mq->front());
        if(NULL == message || NULL == message->function) {
            continue;
        }
        message->function(message->args);
    }

    return NULL;
}

// 初始化
int ThreadPool::init(ThreadPool * self, int max, Func function, const char *name)
{
    int i;
    pid_t pid;
    pthread_attr_t attr;
    pthread_t tid;
    std::string spid;

    self->size = max;
    // 初始化消息队列
    if (0 != MQ<Message>::init(&(self->mq))) {
        perror("init message queue faild");
        return -1;
    }
    // 初始化信号量
    pid = getpid();
    spid = "/tmp/";
    spid += Number::stringify((long long)pid) + "_";
    spid += name;
    spid += ".sem";
    self->pSem = sem_open(spid.c_str(), O_CREAT, 0777, 0);
    if(NULL == self->pSem) {
        perror("init named sem faild");
        return -1;
    }
    // 创建线程
    if(0 != pthread_attr_init(&attr)) {
        perror("init thread attr faild");
        return -1;
    }

    for(i = 0; i < max; i++)
    {
        if(0 != pthread_create(&tid, &attr, function, &self)) {
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

int ThreadPool::init(ThreadPool * self, int max, Func function, std::string &name)
{
    return init(self, max, function, name.c_str());
}

// 默认线程池
int ThreadPool::init(ThreadPool * self, int max, std::string &name)
{
    return ThreadPool::init(self, max, self->thFunction, name.c_str());
}

int ThreadPool::init(ThreadPool * self, int max, const char *name)
{
    return ThreadPool::init(self, max, self->thFunction, name);
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

    this->mq.push(message);     // 写消息队列
    return sem_post(pSem);
}





