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
    #include <pthread.h>
}
#include <queue>
#include "Object.hpp"

namespace G {

    class MQ : public Object
    {
        std::queue<void *> mQueue;
        pthread_rwlock_t locker;
    public:
        MQ();
        static int init(MQ *);
        virtual ~MQ();
        void push(void*);
        void* front();
    };

}

#endif /* MQ_h */
