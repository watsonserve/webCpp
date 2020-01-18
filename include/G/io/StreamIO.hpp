//
//  IO.hpp
//  GHTTPd
//
//  Created by JamesWatson on 16/4/13.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _G_STREAMIO_HPP_
#define _G_STREAMIO_HPP_

#include <string>
#include "G/io/Aio.hpp"
#include "G/io/IOHandle.hpp"
#include "G/io/IOEvents.hpp"
#include "G/io/Input.hpp"
#include "G/io/Output.hpp"

namespace G
{

    class IOEvents;

    typedef enum lineEndFlag
    {
        CR,
        LF,
        CRLF
    } LineEndFlag;

    class StreamIO : virtual public Input, virtual public Output, virtual public IOHandle
    {
        std::string cache;
        int closed;
    protected:
        IOEvents *ioEvents;
        size_t len;
    public:
        static StreamIO* init(StreamIO *, G::IOEvents *, void*, size_t);
        StreamIO();
        virtual ~StreamIO() {};

        virtual void setFd(int, HandleType);
        virtual int getFd();
        virtual void close();

        virtual void recvd();
        virtual void sent();
        virtual void cleanCache();
        virtual int isEmpty();
        virtual std::string & gets(std::string &, LineEndFlag);
        virtual std::string gets(LineEndFlag);
        virtual std::string load(size_t);

        virtual void write(const char *, ssize_t, Func);
        virtual void write(std::string &, Func);
    };

}

#endif /* _G_STREAMIO_HPP_ */
