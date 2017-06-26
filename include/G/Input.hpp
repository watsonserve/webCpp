//
//  Input.hpp
//  GHTTPd
//
//  Created by JamesWatson on 16/4/13.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _G_INPUT_HPP_
#define _G_INPUT_HPP_

#include <string>
#include "G/Aio.hpp"
#include "G/IOEvents.hpp"

namespace G {

    extern class IOEvents;

    class Input : public Object
    {
    protected:
        struct aiocb rd_acb;
        IOEvents *inEvents;
    public:
        static void callback(union sigval);
        static size_t bufSize;
        static Input* init(Input *, IOEvents *, void* mem, size_t memLen);

        Input();
        virtual void recvd() =0;
        virtual void listen();
    };

}

#endif /* _G_INPUT_HPP_ */
