//
//  Event.cpp
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

#include "G/EventListener.hpp"
#ifdef __LINUX__

G::EventListener::EventListener()
{
    this->isA = "EventListener";
    this->epfd = -1;
}

int G::EventListener::init(EventListener &self, ThreadPool * tpool)
{
    if (nullptr == tpool) {
        perror("Can't no thread pool");
        return -1;
    }
    self.tpool = tpool;

    // 准备注册内核事件
    self.epfd = epoll_create(0);
    if (-1 == self.epfd) {
        perror("Can't create epoll");
        return -1;
    }

    return 0;
}

int G::EventListener::emit(G::event_type_t eventType, G::event_data_t *eventData)
{
    struct epoll_event ev;
    ev.events = eventType;
    ev.data.ptr = (void*)eventData;

    epoll_ctl(this->epfd, EPOLL_CTL_ADD, eventData->ident, &ev);
}

void G::EventListener::listen(int fd_num)
{
    struct epoll_event *eventList;
    int i, nEvent;
    G::event_data_t *edata;
    G::exeable_t *udata;
    ThreadPool *tpool;
    tpool = this->tpool;

    // 可用事件列表
    eventList = (struct epoll_event *)malloc(sizeof(struct epoll_event) * fd_num);
    if (nullptr == eventList) {
        perror("Can't create event list");
        exit(1);
    }

    while (1)
    {
        // 获取可用事件
        nEvent = epoll_wait(this->epfd, eventList, fd_num, -1);
        for (i = 0; i < nEvent; i++)
        {
            edata = (G::event_data_t*)(eventList[i].data.ptr);
            if (eventList[i].events & EPOLLERR)  // 出错
            {
                close(edata->ident);
                continue;
            }

            udata = (G::exeable_t *)edata->udata;
            if (-1 == tpool->call(*udata)) {
                perror("request thread pool");
                exit(1);
            }
        }
    }

    return;
}

#endif
