/**
 *  EventListener.cpp
 *  GHTTPd
 *
 *  Created by James on 16/6/11.
 *  Copyright © 2016 watsserve. All rights reserved.
 */

extern "C"
{
    #include "G/kit.h"
}
#include "G/event/EventListener.hpp"

// 构造函数
G::EventListener::EventListener()
{
    this->epfd = -1;
}

// 构造函数
G::EventListener::~EventListener()
{
    printf("G::EventListener::~EventListener\n");
}

// 拷贝构造函数
G::EventListener::EventListener(EventListener &nextListener)
{
    throw new G::Exception("Can't Copy G::EventListener", 0);
}

// 赋值操作符
G::EventListener& G::EventListener::operator = (EventListener &nextListener)
{
    throw new G::Exception("Can't operation G::EventListener =", 0);
    return nextListener;
}

// 获取单例
G::EventListener& G::EventListener::getInstance(G::ThreadPool *tpool, int max)
{
    static G::EventListener listener;
    G::EventListener::_init(listener, tpool, max);
    return listener;
}

void G::EventListener::listen()
{
    pthread_t tid;
    #ifdef __BSD__
        tid = nullptr;
    #else
        tid ^= tid;
    #endif

    if (0 != pthread_create(&tid, nullptr, G::EventListener::_listener, this)) {
        perror("create a listen thread faild");
        exit(1);
    }
    if (0 != pthread_detach(tid)) {
        perror("detach a listen thread faild");
        exit(1);
    }
}

void listen_event(event_listener_t listener)
{
    G::EventListener* l = (G::EventListener *)listener;
    l->listen();
}

event_listener_t event_listener_init(void* tpool, int max)
{
    G::EventListener &retval = G::EventListener::getInstance((G::ThreadPool *)tpool, max);
    return &retval;
}

int emit_event(event_listener_t listener, event_opt_t opt, struct event_t *eventData)
{
    G::EventListener* l = (G::EventListener *)listener;
    return l->emit(opt, (struct event_t *)eventData);
}
