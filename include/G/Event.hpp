//
//  Event.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 18/10/12.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "G/Object.hpp"
#include <string>

#ifdef __BSD__

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#endif

namespace G {

    class EventListener : Object
    {
        int epfd;
        ThreadPool * tpool;
        EventListener();
    public:
        static int init(EventListener &, ThreadPool *);
        void listen(int);
        virtual ~EventListener() {};
    };

}

#endif /* _EVENT_HPP_ */
