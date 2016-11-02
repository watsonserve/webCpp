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
#include <deque>
#include <queue>
#include "G/Object.hpp"

namespace G {

    template <typename T>
    class MQ : public Object
    {
        std::queue<T> mQueue;
        pthread_rwlock_t locker;
    public:
        MQ();
        virtual ~MQ();
        static int init(MQ<T> *);
        void push(const T);
        T front();
    };

}
template class G::MQ<int>;

#endif /* MQ_h */
