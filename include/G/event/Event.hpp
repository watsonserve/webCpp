//
//  Event.hpp
//  GHTTPd
//
//  Created by James on 18/10/12.
//  Copyright © 2018 watsserve. All rights reserved.
//

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "G/Object.hpp"

#ifdef __LINUX__

#include <sys/epoll.h>

#endif

#ifdef __BSD__

#include <sys/types.h>
#include <sys/event.h>

#endif

namespace G
{

#ifdef __LINUX__
    // EPOLL只占用低32位！
    typedef enum
    {
        EV_ERR = EPOLLERR,
        EV_IN = EPOLLIN | EPOLLET,
        EV_OUT = EPOLLOUT | EPOLLONESHOT,
        EV_RDHUP = EPOLLRDHUP,
        EV_PRI = EPOLLPRI,
        EV_ET = EPOLLET,
        EV_WAKEUP = EPOLLWAKEUP,
        EV_EXCLUSIVE = EPOLLEXCLUSIVE,
        EV_ETC = 0x8000000000000000    // 扩展事件
    } event_type_t;
#endif

#ifdef __BSD__
    // kevent只占用低16位！
    typedef enum
    {
        EV_ERR = EV_ERROR,
        EV_IN = (uint16_t)EVFILT_READ,
        EV_OUT = (uint16_t)EVFILT_WRITE,
        EV_ETC = 0x8000000000000000    // 扩展事件
    } event_type_t;
#endif

    class Event final : virtual public Object
    {
        public:
            int64_t ident;
            event_type_t event_type;
            void *context;
            void (*function)(Event &);
            int magic;

            Event();
            Event(const G::Event &ev);
            virtual ~Event();
    };
}

#endif
