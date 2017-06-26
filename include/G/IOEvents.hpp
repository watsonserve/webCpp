//
//  IOEvents.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/5/9.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef IOEvents_h
#define IOEvents_h

#include "G/StreamIO.hpp"

namespace G {

    extern class StreamIO;

    class IOEvents : public Object
    {
    public:
        IOEvents() {};
        virtual void onConnect(StreamIO *) =0;
        virtual void onData(StreamIO *) =0;
        virtual void onError(StreamIO *) =0;
        virtual void onClose(StreamIO *) =0;
        virtual ~IOEvents() {};
    };

}

#endif /* IOEvents_h */
