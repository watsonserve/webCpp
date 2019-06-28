//
//  Event.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 18/10/12.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#ifndef _EVENT_LISTENER_HPP_
#define _EVENT_LISTENER_HPP_

#include "G/ThreadPool.hpp"
#include <string>

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#ifdef __LINUX__

#include <sys/epoll.h>

#endif

#ifdef __BSD__

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#endif

namespace G {

#ifdef __LINUX__
    typedef enum
    {
        OPT_ADD = EPOLL_CTL_ADD,
        OPT_DEL = EPOLL_CTL_DEL,
        OPT_MOD = EPOLL_CTL_MOD
    } event_opt_t;

    // EPOLL只占用低32位！
    typedef enum
    {
        EV_IN = EPOLLIN,
        EV_OUT = EPOLLOUT,
        EV_RDHUP = EPOLLRDHUP,
        EV_PRI = EPOLLPRI,
        EV_ET = EPOLLET,
        EV_ONESHOT = EPOLLONESHOT,
        EV_WAKEUP = EPOLLWAKEUP,
        EV_EXCLUSIVE = EPOLLEXCLUSIVE,
        EV_ETC = 0x8000000000000000    // 扩展事件
    } event_type_t;

#endif

#ifdef __BSD__
    typedef enum
    {
        EV_ETC = 1u << 63    // 扩展事件
    } event_type_t;
#endif

    class EventListener : Object
    {
        int epfd;
        int max;
        G::ThreadPool * tpool;
        EventListener();
        static G::EventListener _instance;
        // pthread_create中必须使用静态方法，所以要将类实例传入
        static void* listener(void *);
    public:
        static G::EventListener& getInstance();
        static int init(G::EventListener &, G::ThreadPool *, int);
        void listen();
        // 第二个参数一定是堆上的内存地址!
        int emit(G::event_opt_t, G::Event *);
        virtual ~EventListener() {};
    };

}

#endif /* _EVENT_LISTENER_HPP_ */

