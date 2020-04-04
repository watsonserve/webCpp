//
//  EventListener.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//
// typedef union epoll_data {
//     void    *ptr;
//     int      fd;
//     uint32_t u32;
//     uint64_t u64;
// } epoll_data_t;

// struct epoll_event {
//     uint32_t     events;    /* Epoll events */
//     epoll_data_t data;      /* User data variable */
// };

#include "G/event/EventListener.hpp"
#ifdef __LINUX__

int G::EventListener::_init(EventListener &self, ThreadPool * tpool, int max)
{
    if (nullptr == tpool) {
        perror("Can't no thread pool");
        return -1;
    }
    self.tpool = tpool;
    self.max = max << 1;

    // 准备注册内核事件
    self.epfd = epoll_create1(EPOLL_CLOEXEC);
    if (-1 == self.epfd) {
        perror("Can't create epoll");
        return -1;
    }

    return 0;
}

int G::EventListener::emit(G::event_opt_t opt, G::Event *eventData)
{
    struct epoll_event ev;

    // EV_ETC 扩展事件立即执行
    if (opt == OPT_EXE && eventData->event_type >> 63)
    {
        if (-1 == tpool->call(*eventData)) {
            perror("request thread pool");
            exit(1);
        }
        return 0;
    }

    ev.events = (uint32_t)(eventData->event_type);
    ev.data.ptr = eventData;

    return epoll_ctl(epfd, opt, eventData->ident, &ev);
}

void* G::EventListener::_listener(void *that)
{
    G::EventListener *self;
    struct epoll_event *eventList, *event_ptr;
    int i, nEvent, max;
    uint32_t event_types;
    ThreadPool *tpool;
    G::Event *udata;

    self = (G::EventListener *)that;
    tpool = self->tpool;
    max = self->max;

    // 可用事件列表
    eventList = (struct epoll_event *)malloc(sizeof(struct epoll_event) * max);
    if (nullptr == eventList) {
        perror("Can't create event list");
        exit(1);
    }

    while (1)
    {
        // 获取可用事件
        nEvent = epoll_wait(self->epfd, eventList, max, -1);
        if (-1 == nEvent) {
            perror("wait event faild");
            exit(1);
        }
        for (i = 0; i < nEvent; i++)
        {
            event_ptr = eventList + i;
            udata = (G::Event*)(event_ptr->data.ptr);
            event_types = event_ptr->events;
            udata->event_type = (G::event_type_t)event_types;

            if (event_types & EPOLLERR)  // 出错
            {
                close(udata->ident);
                udata->event_type = EV_ERR;
            }
            udata->magic = -1;

            if (-1 == tpool->call(*udata)) {
                perror("request thread pool");
                exit(1);
            }
            // printf("delete %lX\n", (int64_t)udata);
            // if(-1 == epoll_ctl(self->epfd, OPT_DEL, udata->ident, NULL)) {
            //     perror("G::EventListener::remove");
            //     exit(1);
            // }
        }
    }

    free(eventList);
    return nullptr;
}

#endif
