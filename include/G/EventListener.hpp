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
    typedef enum {
        OPT_ADD = EPOLL_CTL_ADD,
        OPT_DEL = EPOLL_CTL_DEL,
        OPT_MOD = EPOLL_CTL_MOD
    } event_opt_t;

    typedef enum {
        EV_IN = EPOLLIN,
        EV_OUT = EPOLLOUT,
        EV_RDHUP = EPOLLRDHUP,
        EV_PRI = EPOLLPRI,
        EV_ET = EPOLLET,
        EV_ONESHOT = EPOLLONESHOT,
        EV_WAKEUP = EPOLLWAKEUP,
        EV_EXCLUSIVE = EPOLLEXCLUSIVE
    } event_type_t;

#endif

#ifdef __BSD__
    typedef enum {
    } event_type_t;
#endif

    class EventListener : Object
    {
        int epfd;
        G::ThreadPool * tpool;
        EventListener();
    public:
        static int init(G::EventListener &, G::ThreadPool *);
        void listen(int);
        int emit(G::event_opt_t, G::Event *);
        virtual ~EventListener() {};
    };

}

#endif /* _EVENT_LISTENER_HPP_ */
