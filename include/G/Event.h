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

    typedef event_data_t;

    typedef struct
    {
        void *context;
        void (*function)(event_data_t *);
        unsigned long ident;
        int event_type;
    } event_data_t;

}

#endif
