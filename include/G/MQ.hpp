//
//  MQ.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/8/28.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _MQ_H_
#define _MQ_H_

extern "C" {
    #include <string.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include "G/sem.h"
}
#include <queue>
#include "G/Object.hpp"

namespace G
{

    template <typename T>
    class MQ : virtual public Object
    {
        // std::queue是值拷贝, push进去的变量和front出来的引用，地址不一样
        std::queue<T> mQueue;
        sem_t p_sem;
        pthread_mutex_t lock;

    public:
        MQ() {
            memset(&this->p_sem, 0, sizeof(sem_t));
            memset(&this->lock, 0, sizeof(pthread_mutex_t));
        };
        virtual ~MQ()
        {
            destroy_sem(&this->p_sem);
            pthread_mutex_destroy(&this->lock);
        };

        static int init(MQ *self)
        {
            // 初始化信号量
            if (0 != init_sem(&self->p_sem, 0, 0)) {
                perror("MQ init sem faild");
                return -1;
            }
            if (0 != pthread_mutex_init(&self->lock, NULL)) {
                destroy_sem(&self->p_sem);
                perror("MQ init lock faild");
                return -1;
            }
            
            return 0;
        };

        int push(const T &ele)
        {
            sem_t *p_sem;
            pthread_mutex_t *p_lock;

            p_sem = &this->p_sem;
            p_lock = &this->lock;

            // 上锁
            if (0 != pthread_mutex_lock(p_lock)) {
                perror("MQ push lock");
                exit(1);
            }
            mQueue.push(ele);

            // 发射信号量
            if(0 != post_sem(p_sem)) {
                perror("MQ post sem");
                exit(1);
            }
            // 解锁
            pthread_mutex_unlock(p_lock);
            return 0;
        };

        T front()
        {
            sem_t *p_sem;
            pthread_mutex_t *p_lock;

            p_sem = &this->p_sem;
            p_lock = &this->lock;

            // 等待信号量
            if(0 != wait_sem(p_sem)) {
                perror("wait a sem");
                exit(1);
            }
            // 上锁
            if (0 != pthread_mutex_lock(p_lock)) {
                perror("MQ pop lock");
                exit(1);
            }

            T ret = mQueue.front();
            mQueue.pop();
            // 解锁
            pthread_mutex_unlock(p_lock);

            // throw exception
            return ret;
        };
    };
}

#endif /* MQ_h */
