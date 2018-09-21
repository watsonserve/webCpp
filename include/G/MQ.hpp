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
    #include "sem.h"
}
#include <queue>
#include "G/Object.hpp"

namespace G {

    template <typename T>
    class MQ : public Object
    {
        std::queue<T> mQueue;
        sem_t p_sem;

    public:
        MQ() {
            memset(&this->p_sem, 0, sizeof(sem_t));
        };
        virtual ~MQ()
        {
            destroy_sem(&this->p_sem);
        };

        static int init(MQ *self)
        {
            // 初始化信号量
            if (0 != init_sem(&self->p_sem, 0, 0)) {
                perror("init named sem faild");
                return -1;
            }
            return 0;
        };

        int push(const T ele)
        {
            sem_t *p_sem;

            p_sem = &this->p_sem;
            mQueue.push(ele);

            // 等待信号量
            return post_sem(p_sem);
        };

        T front()
        {
            sem_t *p_sem;
            T ret;

            p_sem = &this->p_sem;

            // 等待信号量
            if(0 != wait_sem(p_sem)) {
                perror("wait a sem");
                exit(1);
            }
            if (!mQueue.empty()) {
                ret = mQueue.front();
                mQueue.pop();
            }

            // throw exception
            return ret;
        };
    };

}

#endif /* MQ_h */
