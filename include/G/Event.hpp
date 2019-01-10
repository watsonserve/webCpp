//
//  Event.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 18/10/12.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#ifndef _EVENT_HPP_
#define _EVENT_HPP_

namespace G {

    class Exeable
    {
        public:
            void *context;
            void (*function)(Exeable *);
    };

    class Event : public Exeable
    {
        public:
            unsigned long ident;
            int event_type;
    };
}

#endif
