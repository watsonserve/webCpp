//
//  EventListener.cpp
//  GHTTPd
//
//  Created by James on 16/6/11.
//  Copyright © 2016 watsserve. All rights reserved.
//

// struct kevent {
//     uintptr_t       ident;          // 文件描述符
//     int16_t         filter;         /* filter for event */
//     uint16_t        flags;          // general flags
//                                        EV_ADD, EV_ENABLE, EV_DISABLE, EV_DELETE,
//                                        EV_RECEIPT, EV_ONESHOT, EV_CLEAR, EV_EOF, EV_OOBAND, EV_ERRO,
//     uint32_t        fflags;         /* filter-specific flags */
//     intptr_t        data;           /* filter-specific data */
//     void            *udata;         /* opaque user data identifier */
// };

#include "G/event/EventListener.hpp"
#ifdef __BSD__

int EventListener::_init(EventListener &self, ThreadPool * tpool, int max)
{
    if (nullptr == tpool) {
        perror("Can't no thread pool");
        return -1;
    }
    self.tpool = tpool;
    self.max = max << 1;

    // 准备注册内核事件
    self.epfd = kqueue();
    if (-1 == self.epfd) {
        perror("Can't create kqueue");
        return -1;
    }

    return 0;
}

int G::EventListener::emit(G::event_opt_t opt, G::Event *eventData)
{
    struct kevent ev;

    // EV_ETC 扩展事件立即执行
    if (opt == OPT_EXE && eventData->event_type >> 63)
    {
        if (-1 == tpool->call(*eventData)) {
            perror("request thread pool");
            exit(1);
        }
        return 0;
    }

    EV_SET(
        &ev,
        eventData->ident,
        (uint32_t)(eventData->event_type),
        opt,
        0,
        NULL,
        (void*)eventData
    );
    return kevent(epfd, &ev, 1, nullptr, 0, nullptr);
}

void* G::EventListener::_listener(void *that)
{
    G::EventListener *self;
    struct kevent *eventList, *event_ptr;
    int i, nEvent, max;
    uint16_t event_types;
    ThreadPool *tpool;
    G::Event *udata;

    self = (G::EventListener *)that;
    tpool = self->tpool;
    max = self->max;

    // 可用事件列表
    eventList = (struct kevent *)malloc(sizeof(struct kevent) * max);
    if (nullptr == eventList) {
        perror("Can't create event list");
        exit(1);
    }

    while (1)
    {
        // 获取可用事件
        nEvent = kevent(self->epfd, nullptr, 0, eventList, max, nullptr);
        if (-1 == nEvent) {
            perror("wait event faild");
            exit(1);
        }
        for(i = 0; i < nEvent; i++)
        {
            event_ptr = eventList + i;
            udata = (G::Event *)(event_ptr->udata);
            event_types = event_ptr->filter;
            udata->event_type = (G::event_type_t)event_types;

            if (event_ptr->flags & EV_ERROR)  // 出错
            {
                close((int)(event_ptr->ident));
                udata->event_type = EV_ERR;
            }
            // errno or data_length
            udata->magic = event_ptr->data;

            if (-1 == tpool->call(*udata)) {
                perror("request thread pool");
                exit(1);
            }
        }
    }

    free(eventList);
    return nullptr;
}

#endif
