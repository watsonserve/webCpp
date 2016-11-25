//
//  MQ.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/8/28.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef MQ_h
#define MQ_h

extern "C" {
    #include <stdlib.h>
    #include <pthread.h>
}
#include <queue>
#include "G/Object.hpp"

namespace G {

    template <typename T>
    class MQ : public Object
    {
        std::queue<T> mQueue;
        pthread_rwlock_t locker;
    public:
        MQ() {};
        virtual ~MQ()
        {
            pthread_rwlock_destroy(&locker);
        };

        static int init(MQ *self)
        {
            return pthread_rwlock_init(&(self->locker), NULL);
        };

        void push(const T ele)
        {
            if(0 != pthread_rwlock_wrlock(&locker)) {
                // todo
                exit(1);
            }
            mQueue.push(ele);
            pthread_rwlock_unlock(&locker);
        };

        T front()
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
        };
    };

}

#endif /* MQ_h */
