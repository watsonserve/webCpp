//
//  Event.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 18/10/12.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

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
        EV_IN = EPOLLIN,
        EV_OUT = EPOLLOUT,
        EV_RDHUP = EPOLLRDHUP,
        EV_PRI = EPOLLPRI,
        EV_ET = EPOLLET,
        EV_ONESHOT = EPOLLONESHOT,
        EV_WAKEUP = EPOLLWAKEUP,
        EV_EXCLUSIVE = EPOLLEXCLUSIVE
    } event_type_t;

    typedef struct {
        unsigned long ident;
        void* udata;
    } event_data_t;
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
        int emit(G::event_type_t, G::event_data_t *);
        virtual ~EventListener() {};
    };

}

#endif /* _EVENT_HPP_ */
