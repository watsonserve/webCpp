//
//  EventListener.hpp
//  GHTTPd
//
//  Created by James on 18/10/12.
//  Copyright © 2018 watsserve. All rights reserved.
//

#ifndef _EVENT_LISTENER_HPP_
#define _EVENT_LISTENER_HPP_

extern "C"
{
    #include <stdlib.h>
    #include <unistd.h>
    #include <pthread.h>
    #include <errno.h>

    #include "event/event.h"

    #ifdef __BSD__

    #include <sys/time.h>

    #endif
}

#include <string>
#include <map>
#include "ThreadPool.hpp"
#include "Exception.hpp"

namespace G
{
    class EventListener : virtual Object
    {
        int epfd;
        int max;
        G::ThreadPool * tpool;

        // 没有实际作用的构造函数
        EventListener();
        // 不可调用的拷贝和赋值
        EventListener(EventListener &);
        virtual EventListener& operator= (EventListener &);

        // 实际的初始化
        static int _init(G::EventListener &, G::ThreadPool *, int);

        // pthread_create中必须使用静态方法，所以要将类实例传入
        static void* _listener(void *);
    public:
        static G::EventListener& getInstance(G::ThreadPool *, int);
        void listen();
        // 第二个参数一定是堆上的内存地址!
        int emit(event_opt_t, struct event_t *);
        virtual ~EventListener();
    };

}

#endif /* _EVENT_LISTENER_HPP_ */
