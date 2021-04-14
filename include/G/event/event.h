#ifndef _G_EVENT_H_
#define _G_EVENT_H_

#include "G/stdafx.h"

#ifdef __LINUX__

#include <sys/epoll.h>

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

typedef enum
{
    OPT_EXE = 0,
    OPT_ADD = EPOLL_CTL_ADD,
    OPT_DEL = EPOLL_CTL_DEL,
    OPT_MOD = EPOLL_CTL_MOD
} event_opt_t;

#endif

#ifdef __BSD__

#include <sys/types.h>
#include <sys/event.h>

// kevent只占用低16位！
typedef enum
{
    EV_ERR = EV_ERROR,
    EV_IN = (uint16_t)EVFILT_READ,
    EV_OUT = (uint16_t)EVFILT_WRITE,
    EV_ETC = 0x8000000000000000    // 扩展事件
} event_type_t;

typedef enum
{
    OPT_EXE = 0,
    OPT_ADD = EV_ADD | EV_CLEAR | EV_ONESHOT,
    OPT_DEL = EV_DELETE
} event_opt_t;

#endif

#ifndef _EVENT_FIELDS_
#define _EVENT_FIELDS_ \
    int64_t ident; \
    void *self; \
    event_callback on_event; \
    event_type_t event_type; \
    int magic;
#endif

struct event_t;

typedef void (*event_callback)(struct event_t);

struct event_t
{
    _EVENT_FIELDS_
};

#endif
