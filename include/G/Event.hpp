//
//  Event.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 18/10/12.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "stdafx.h"
#include "G/Object.hpp"

#ifdef __BSD__

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#endif

namespace G {

    class Event : public Object
    {
        int epfd;
    public:
        Event() {};
        static int init(Event &self);
        virtual void set() =0;
        virtual void listen() =0;
        virtual ~Event() {};
    };

}

#endif /* _EVENT_HPP_ */
