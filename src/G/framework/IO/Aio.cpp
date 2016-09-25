//
//  Aio.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/Aio.hpp"

using namespace G;

#if defined (__linux__) || defined(__linux)
void Aio::aioInit(struct aioinit * aip)
{
    aio_init(aip);
    return;
}

int Aio::aioRead(struct aiocb *aiocbp)
{
    return aio_read(aiocbp);
}

int Aio::aioWrite(struct aiocb *aiocbp)
{
    return aio_write(aiocbp);
}

ssize_t Aio::aioReturn(struct aiocb *aiocbp)
{
    return aio_return(aiocbp);
}

int Aio::aioError(const struct aiocb *aiocbp)
{
    return aio_error(aiocbp);
}

int Aio::aioCancel(int fd, struct aiocb *aiocbp)
{
    return aio_cancel(fd, aiocbp);
}

#else
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "G/Number.hpp"

int Aio::kq;
struct kevent * Aio::eventList;
AioBack * Aio::abList;
aioinit Aio::conf;
sem_t * Aio::pEventSem;
MQ Aio::mq;

void* Aio::listenEvnt(void * args)
{
    int i, nEvent;
    
    while (1)
    {
        nEvent = kevent(Aio::kq, NULL, 0, Aio::eventList, conf.aio_num, NULL);  // 获取可用事件
        for(i=0; i<nEvent; i++)
        {
            if (eventList[i].flags & EV_ERROR)  // 出错
            {
                close((int)(eventList[i].ident));
                continue;
            }
            mq.push(eventList[i].udata);        // 写消息队列
            if (-1 == sem_post(pEventSem)) { // 触发信号量
                perror("post sem");
                exit(1);
            }
        }
        
    }
    return NULL;
}

void* Aio::eventCallback(void* args)
{
    AioBack *abp;
    struct aiocb *cbp;

    while (1)
    {
        // 等待信号量
        if(0 != sem_wait(pEventSem)) {
            perror("wait a sem");
            exit(1);
        }
        // 读消息队列
        cbp = (struct aiocb *)mq.front();
        if(NULL == cbp) {
            continue;
        }

        abp = abList + cbp->aio_fildes;
        abp->readyDataLen = read(cbp->aio_fildes, (char*)cbp->aio_buf + cbp->aio_offset, cbp->aio_nbytes);
        if (1 > abp->readyDataLen) {
            abp->error = errno;
        }
        // 执行回调
        cbp->aio_sigevent.sigev_notify_function(cbp->aio_sigevent.sigev_value);
    }
    return NULL;
}

int Aio::aioInit(struct aioinit * aip)
{
    int i;
    pid_t pid;
    pthread_attr_t attr;
    pthread_t tid;
    std::string spid;

    conf = *aip;
    Aio::kq = kqueue();  // 准备注册内核事件
    if(-1 == Aio::kq) {
        perror("Can't create kqueue");
        return -1;
    }
    eventList = (struct kevent *)malloc(sizeof(struct kevent) * aip->aio_num);  // 可用事件列表
    if(NULL == eventList) {
        perror("Can't create event list");
        return -1;
    }
    abList = (AioBack *)malloc(sizeof(AioBack) * aip->aio_num);
    if(NULL == abList) {
        perror("Can't create cblist");
        return -1;
    }
    // 初始化消息队列
    if (0 != MQ::init(&(Aio::mq))) {
        perror("init message queue faild");
        return -1;
    }
    // 初始化信号量
    pid = getpid();
    spid = "/tmp/";
    spid += Number::stringify((long long)pid) + ".sem";
    pEventSem = sem_open(spid.c_str(), O_CREAT, 0777, 0);
    if(NULL == pEventSem) {
        perror("init named sem faild");
        return -1;
    }
    // 创建线程
    if(0 != pthread_attr_init(&attr)) {
        perror("init thread attr faild");
        return -1;
    }
    if(0 != pthread_create(&tid, &attr, Aio::listenEvnt, NULL)) {
        perror("create thread faild");
        return -1;
    }
    if(0 != pthread_detach(tid)) {
        perror("detach thread faild");
        return -1;
    }

    for(i = 0; i < aip->aio_threads; i++)
    {
        if(0 != pthread_create(&tid, &attr, Aio::eventCallback, NULL)) {
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

int Aio::aioRead(struct aiocb *aiocbp)
{
    struct kevent kev;

    EV_SET(&kev, aiocbp->aio_fildes, EVFILT_READ, EV_ADD | EV_ONESHOT, 0, 0, aiocbp);
    return kevent(kq, &kev, 1, NULL, 0, NULL);
}

int Aio::aioWrite(struct aiocb *aiocbp)
{
    struct kevent kev;

    EV_SET(&kev, aiocbp->aio_fildes, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, aiocbp);
    return kevent(kq, &kev, 1, NULL, 0, NULL);
}

ssize_t Aio::aioReturn(struct aiocb *aiocbp)
{
    return abList[aiocbp->aio_fildes].readyDataLen;
}

int Aio::aioError(const struct aiocb *aiocbp)
{
    return abList[aiocbp->aio_fildes].error;
}

int Aio::aioCancel(int fd, struct aiocb *aiocbp)
{
    return 0;
}

#endif
