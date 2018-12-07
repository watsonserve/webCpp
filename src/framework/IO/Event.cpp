//
//  Event.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/Event.hpp"

#ifdef __BSD__

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "G/ThreadPool.hpp"

using namespace G;

int Event::init(Event &self)
{
    // 准备注册内核事件
    self.epfd = kqueue();
    if (-1 == self.epfd) {
        perror("Can't create kqueue");
        return -1;
    }

    return 0;
}

void* Event::listen(void * args)
{
    struct kevent * eventList;
    Func way;
    int i, nEvent;

    // 可用事件列表
    eventList = (struct kevent *)malloc(sizeof(struct kevent) * conf.aio_num);
    if (NULL == eventList) {
        perror("Can't create event list");
        exit(1);
    }
    
    while (1)
    {
        // 获取可用事件
        nEvent = kevent(Aio::kq, NULL, 0, eventList, conf.aio_num, NULL);
        for(i = 0; i < nEvent; i++)
        {
            if (eventList[i].flags & EV_ERROR)  // 出错
            {
                close((int)(eventList[i].ident));
                continue;
            }
            switch (eventList[i].filter)
            {
                case EVFILT_READ:
                    way = Aio::readCallback;
                    break;
                case EVFILT_WRITE:
                    way = Aio::writeCallback;
                    break;
                default:
                    perror("not read or write event");
                    exit(1);
            }
            if (-1 == threadPool.call(eventList[i].udata, way)) {
                perror("request thread pool");
                exit(1);
            }
        }
    }

    return NULL;
}

#endif
