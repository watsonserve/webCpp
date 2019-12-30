//
//  Event.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 18/10/12.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#ifndef _EVENT_LISTENER_HPP_
#define _EVENT_LISTENER_HPP_

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
// 这里定义编译环境
#include "G/stdafx.h"

#ifdef __LINUX__

#include <sys/epoll.h>

#endif

#ifdef __BSD__

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#endif

#include <string>
#include <map>
#include "G/ThreadPool.hpp"
#include "G/Exception.hpp"

namespace G {

#ifdef __LINUX__
    typedef enum
    {
        OPT_ADD = EPOLL_CTL_ADD,
        OPT_DEL = EPOLL_CTL_DEL,
        OPT_MOD = EPOLL_CTL_MOD
    } event_opt_t;
#endif

#ifdef __BSD__
    typedef enum
    {
        OPT_ADD = EV_ADD,
        OPT_DEL = EV_DELETE
    } event_opt_t;
#endif

    class EventListener : virtual Object
    {
        int epfd;
        int max;
        G::ThreadPool * tpool;
        std::map<int, G::Event> eventPool;

        // 没有实际作用的构造函数
        EventListener();
        // 不可调用的拷贝和赋值
        EventListener(EventListener &);
        virtual EventListener& operator= (EventListener &);

        // 实际的初始化
        static int _init(G::EventListener &, G::ThreadPool *, int);

        // pthread_create中必须使用静态方法，所以要将类实例传入
        static void* _listener(void *);
    public:
        static G::EventListener& getInstance(G::ThreadPool *, int);
        void listen();
        // 第二个参数一定是堆上的内存地址!
        int emit(G::event_opt_t, G::Event *);
        int emit(G::event_opt_t, G::Event &);
        virtual ~EventListener() {};
    };

}

#endif /* _EVENT_LISTENER_HPP_ */
