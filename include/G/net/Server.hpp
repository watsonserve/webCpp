#ifndef _GSERVER_HPP_
#define _GSERVER_HPP_

extern "C"
{
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <thread>
    #include <errno.h>
    #ifdef __BSD__
        #include <sys/event.h>
    #endif
}

#include "G/Object.hpp"
#include "G/StreamIO.hpp"

namespace G {
    class Server : public G::Object
    {
    public:
        Server() {};
        virtual ~Server() =0;
        virtual SOCKET initSocket() =0;
        virtual int service(G::IOEvents *, int) =0;
    };
}
#endif