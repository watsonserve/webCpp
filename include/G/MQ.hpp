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

    template <class T>
    class MQ : public Object
    {
        std::queue<T> mQueue;
        pthread_rwlock_t locker;
    public:
        MQ() {};
        virtual ~MQ();
        static int init(MQ *);
        void push(T);
        void* front();
    };

}

#endif /* MQ_h */
