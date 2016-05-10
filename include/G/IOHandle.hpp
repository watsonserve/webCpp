//
//  IOHandle.hpp
//  GHTTPd
//
//  Created by JamesWatson on 16/5/9.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _IOHandle_h_
#define _IOHandle_h_

#include "G/Object.hpp"

namespace G {

    typedef enum handle_type {
        FILE,
        NET_SOCKET,
        UNIX_SOCKET,
        PIPE,
        FIFO
    } HandleType;

    class IOHandle: public Object {
    protected:
        HandleType type;
    public:
        static HandleType handleType;
        virtual void setFd(int, HandleType) =0;
        virtual int getFd() =0;
        virtual void close() =0;
    };

}

#endif /* _IOHandle_h_ */
