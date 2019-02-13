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

G::EventListener::EventListener()
{
    this->isA = "EventListener";
    this->epfd = -1;
}

void G::EventListener::listen()
{
    pthread_t tid;
    #ifdef __BSD__
        tid = nullptr;
    #else
        tid ^= tid;
    #endif

    if(0 != pthread_create(&tid, nullptr, G::EventListener::listener, this)) {
        perror("create a listen thread faild");
        exit(1);
    }
    if(0 != pthread_detach(tid)) {
        perror("detach a listen thread faild");
        exit(1);
    }
}
