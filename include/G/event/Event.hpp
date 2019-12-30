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

namespace G {

    class Event : virtual public Object
    {
        public:
            uint64_t ident;
            uint64_t event_type;
            void *context;
            void (*function)(Event *);
            Event();
            virtual ~Event() {};
    };
}

#endif
