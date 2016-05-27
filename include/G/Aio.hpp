//
//  Aio.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/5/21.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef Aio_hpp
#define Aio_hpp

#include <queue>
#include <atomic>
#include "G/ThreadPool.hpp"

namespace G {

    class Aio : public Object
    {
        static size_t max;
        static ThreadPool pool;
        static std::atomic<std::queue<unsigned long>> fdQueue;
        static void eventThread();
        int fd;
    protected:
        static void threadCallback(void*);
    public:
        static int config(size_t max);
        static int initAio(Aio *, void *buf, int bufSiz);
        Aio();
        int setFd(int fd);
        virtual ~Aio() {};
        virtual int aioRead();
        virtual int aioWrite();
        virtual int aioReturn();
        virtual int aioError();
        virtual void threadFunction();
    };

}

#endif /* Aio_hpp */
