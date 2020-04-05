#ifndef _GSERVER_HPP_
#define _GSERVER_HPP_

extern "C"
{
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <errno.h>
    #ifdef __BSD__
        #include <sys/event.h>
    #endif
    #include "G/net/Gnet.h"
}

#include "G/io/IOHandler.hpp"

namespace G
{
    class Server
    {
    protected:
        SOCKET sockfd;
    public:
        virtual int service(int) =0;
    };
}
#endif
