//
//  Output.hpp
//  GHTTPd
//
//  Created by JamesWatson on 16/4/13.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _G_Output_HPP_
#define _G_Output_HPP_

#include <string>
#include "G/io/Aio.hpp"
#include "G/io/IOEvents.hpp"

namespace G {

    class Output;
    class IOEvents;

    class Output : virtual public Object
    {
    protected:
        struct aiocb wr_acb;
        IOEvents *outEvents;
        Func onComplete;
    public:
        static void callback(union sigval);
        static Output* init(Output *, IOEvents *);

        virtual void sent() =0;
        virtual void write(const char *buf, ssize_t len, Func callback) =0;
        virtual void write(std::string &, Func callback) =0;
    };
}

#endif /* _G_Output_HPP_ */
