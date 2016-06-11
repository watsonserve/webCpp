//
//  Aio.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef Aio_h
#define Aio_h

extern "C" {
    #include <aio.h>
}
#include "G/Object.hpp"

#if !defined (__linux__) && !defined(__linux)
struct aioinit
{
    int aio_threads;   // Maximum number of threads
    int aio_num;       // Number of expected simultaneous requests
    int aio_idle_time;
};
#endif

namespace G {
    class Aio : public Object {
    public:
        static void aioInit(struct aioinit *);
        static int aioRead(struct aiocb *);
        static int aioWrite(struct aiocb *);
        static ssize_t aioReturn(struct aiocb *);
        static int aioError(const struct aiocb *);
        static int aioCancel(int, struct aiocb *);
    };
}

#endif /* Aio_h */
