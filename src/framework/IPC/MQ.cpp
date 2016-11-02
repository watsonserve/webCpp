//
//  MQ.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/8/28.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/MQ.hpp"

using namespace G;

template <typename T>
int MQ<T>::init(MQ<T> *self)
{
    return pthread_rwlock_init(&(self->locker), NULL);
}

template <typename T>
MQ<T>::~MQ()
{
    pthread_rwlock_destroy(&locker);
}

template <typename T>
void MQ<T>::push(const T ele)
{
    if(0 != pthread_rwlock_wrlock(&locker)) {
        // todo
        exit(1);
    }
    mQueue.push(ele);
    pthread_rwlock_unlock(&locker);
}

template <typename T>
T MQ<T>::front()
{
    T ret;

    if(0 != pthread_rwlock_wrlock(&locker)) {
        // todo
        exit(1);
    }
    if (!mQueue.empty()) {
        ret = mQueue.front();
        mQueue.pop();
    }
    pthread_rwlock_unlock(&locker);
    // throw exception
    return ret;
}
