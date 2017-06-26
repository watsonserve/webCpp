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
#include "G/Aio.hpp"
#include "G/IOEvents.hpp"

namespace G {

    class Output;
    class IOEvents;

    typedef void (*OutBack)(Output *);

    class Output : public Object
    {
    protected:
        struct aiocb wr_acb;
        IOEvents *outEvents;
        OutBack onComplete;
    public:
        static void callback(union sigval);
        static Output* init(Output *, IOEvents *);

        virtual void sent() =0;
        virtual void write(const char *buf, ssize_t len, OutBack callback) =0;
        virtual void write(std::string &, OutBack callback) =0;
    };
}

#endif /* _G_Output_HPP_ */
