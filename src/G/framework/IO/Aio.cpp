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
#include <pthread.h>

int Aio::kq;
struct kevent * Aio::eventList;
struct aiocb * Aio::cbList;
aioinit Aio::conf;
sem_t * Aio::pEventSem;
MQ Aio::mq;

void* Aio::listenEvnt(void * args)
{
    int i, nEvent;
    struct aiocb *cbp;
    
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
            cbp = cbList + eventList[i].ident;
            mq.push(cbp);        // 写消息队列
            sem_post(pEventSem); // 触发信号量
        }
        
    }
    return NULL;
}

void* Aio::eventCallback(void* args)
{
    struct aiocb *cbp;
    while (1)
    {
        // 等待信号量
        if(0 != sem_wait(pEventSem)) {
            exit(1);
        }
        // 读消息队列
        cbp = (struct aiocb *)mq.front();
        if(NULL == cbp) {
            continue;
        }
        read(cbp->aio_fildes, (char*)cbp->aio_buf + cbp->aio_offset, cbp->aio_nbytes);
        // 执行回调
        cbp->aio_sigevent.sigev_notify_function(cbp->aio_sigevent.sigev_value);
    }
    return NULL;
}

int Aio::aioInit(struct aioinit * aip)
{
    int i;
    pthread_attr_t attr;
    pthread_t tid;

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
    cbList = (struct aiocb *)malloc(sizeof(struct aiocb) * aip->aio_num);
    if(NULL == cbList) {
        perror("Can't create cblist");
        return -1;
    }
    // 创建线程
    if(0 != pthread_attr_init(&attr)) {
        return -1;
    }
    if(0 != pthread_create(&tid, &attr, Aio::listenEvnt, NULL)) {
        return -1;
    }
    if(0 != pthread_detach(tid)) {
        return -1;
    }
    for(i = 0; i < aip->aio_threads; i++)
    {
        if(0 != pthread_create(&tid, &attr, Aio::eventCallback, NULL)) {
            return -1;
        }
        if(0 != pthread_detach(tid)) {
            return -1;
        }
    }
    // 初始化信号量
    pEventSem = sem_open("/tmp/+pid+.sem", O_CREAT, 0777);
    if(NULL == pEventSem) {
        return -1;
    }
    // 初始化消息队列
    MQ::init(&(Aio::mq));
    return 0;
}

int Aio::aioRead(struct aiocb *aiocbp)
{
    struct kevent kev;

    EV_SET(&kev, aiocbp->aio_fildes, EVFILT_READ, EV_DISABLE, 0, 0, NULL);
    return 0;
}

int Aio::aioWrite(struct aiocb *aiocbp)
{
    return 0;
}

ssize_t Aio::aioReturn(struct aiocb *aiocbp)
{
    return 0;
}

int Aio::aioError(const struct aiocb *aiocbp)
{
    return 0;
}

int Aio::aioCancel(int fd, struct aiocb *aiocbp)
{
    return 0;
}

#endif
