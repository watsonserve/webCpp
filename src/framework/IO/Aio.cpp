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
int Aio::aioInit(struct aioinit * aip)
{
    aio_init(aip);
    return 0;
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
#include "G/ThreadPool.hpp"

int Aio::kq;
AioBack * Aio::rdList;
AioBack * Aio::wrList;
aioinit Aio::conf;
ThreadPool Aio::threadPool;

void* Aio::listenEvnt(void * args)
{
    struct kevent * eventList;
    ThreadPool::Func way;
    int i, nEvent;

    // 可用事件列表
    eventList = (struct kevent *)malloc(sizeof(struct kevent) * conf.aio_num);
    if(NULL == eventList) {
        perror("Can't create event list");
        exit(1);
    }
    
    while (1)
    {
        // 获取可用事件
        nEvent = kevent(Aio::kq, NULL, 0, eventList, conf.aio_num, NULL);
        for(i=0; i<nEvent; i++)
        {
            if (eventList[i].flags & EV_ERROR)  // 出错
            {
                close((int)(eventList[i].ident));
                continue;
            }
            switch (eventList[i].filter)
            {
                case EVFILT_READ:
                    way = Aio::readCallback;
                    break;
                case EVFILT_WRITE:
                    way = Aio::writeCallback;
                    break;
                default:
                    perror("not read or write event");
                    exit(1);
            }
            if (-1 == threadPool.call(eventList[i].udata, way)) {
                perror("request thread pool");
                exit(1);
            }
        }
    }

    return NULL;
}

void* Aio::readCallback(void* args)
{
    AioBack *abp;
    struct aiocb *cbp;

    cbp = (struct aiocb *)args;
    if(NULL != cbp)
    {
        abp = rdList + cbp->aio_fildes;
        abp->dataLen = pread(cbp->aio_fildes, (char*)cbp->aio_buf, cbp->aio_nbytes, cbp->aio_offset);
        if (1 > abp->dataLen) {
            abp->error = errno;
        }

        // 执行回调
        cbp->aio_sigevent.sigev_notify_function(cbp->aio_sigevent.sigev_value);
    }

    return NULL;
}

void* Aio::writeCallback(void* args)
{
    AioBack *abp;
    struct aiocb *cbp;
    struct kevent kev;

    cbp = (struct aiocb *)args;
    if(NULL != cbp)
    {
        abp = wrList + cbp->aio_fildes;
        abp->dataLen = write(cbp->aio_fildes, (char*)cbp->aio_buf + abp->doneLen, abp->sumSize - abp->doneLen);
        if (1 > abp->dataLen) {
            abp->error = errno;
        }
        abp->doneLen += abp->dataLen;
        if (cbp->aio_nbytes > abp->doneLen)
        {

            // 未读完，再监听
            EV_SET(&kev, cbp->aio_fildes, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, cbp);
            kevent(kq, &kev, 1, NULL, 0, NULL);
            return NULL;
        }

        // 执行回调
        cbp->aio_sigevent.sigev_notify_function(cbp->aio_sigevent.sigev_value);
    }
    
    return NULL;
}

int Aio::aioInit(struct aioinit * aip)
{
    pthread_attr_t attr;
    pthread_t tid;

    conf = *aip;

    // 准备注册内核事件
    Aio::kq = kqueue();
    if(-1 == Aio::kq) {
        perror("Can't create kqueue");
        return -1;
    }

    rdList = (AioBack *)malloc(sizeof(AioBack) * aip->aio_num);
    if(NULL == rdList) {
        perror("Can't create cblist");
        return -1;
    }
    wrList = (AioBack *)malloc(sizeof(AioBack) * aip->aio_num);
    if(NULL == wrList) {
        perror("Can't create cblist");
        return -1;
    }

    // 初始化工作线程池
    if (0 != ThreadPool::init(&(Aio::threadPool), aip->aio_threads, "0")) {
        perror("init thread pool faild");
        return -1;
    }

    // 创建监听线程
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
    AioBack *abp;

    abp = wrList + aiocbp->aio_fildes;
    abp->doneLen = 0;
    abp->sumSize = aiocbp->aio_nbytes;
    EV_SET(&kev, aiocbp->aio_fildes, EVFILT_WRITE, EV_ADD | EV_ONESHOT, 0, 0, aiocbp);
    return kevent(kq, &kev, 1, NULL, 0, NULL);
}

ssize_t Aio::aioReturn(struct aiocb *aiocbp)
{
    if(LIO_READ == aiocbp->aio_lio_opcode)
        return rdList[aiocbp->aio_fildes].dataLen;
    return wrList[aiocbp->aio_fildes].dataLen;
}

int Aio::aioError(const struct aiocb *aiocbp)
{
    if(LIO_READ == aiocbp->aio_lio_opcode)
        return rdList[aiocbp->aio_fildes].error;
    return wrList[aiocbp->aio_fildes].error;
}

int Aio::aioCancel(int fd, struct aiocb *aiocbp)
{
    return 0;
}

#endif
