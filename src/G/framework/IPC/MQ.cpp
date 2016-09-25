//
//  MQ.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/8/28.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include <stdlib.h>
#include "G/MQ.hpp"

using namespace G;

int MQ::init(MQ *self)
{
    return pthread_rwlock_init(&(self->locker), NULL);
}

MQ::~MQ()
{
    pthread_rwlock_destroy(&locker);
}

void MQ::push(void* ele)
{
    if(0 != pthread_rwlock_wrlock(&locker)) {
        // todo
        exit(1);
    }
    mQueue.push(ele);
    printf("mq push");
    pthread_rwlock_unlock(&locker);
}

void* MQ::front()
{
    void * ret;

    ret = NULL;
    if(0 != pthread_rwlock_wrlock(&locker)) {
        // todo
        exit(1);
    }
    if (!mQueue.empty()) {
        ret = mQueue.front();
        mQueue.pop();
    }
    pthread_rwlock_unlock(&locker);
    return ret;
}