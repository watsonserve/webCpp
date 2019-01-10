#ifndef _GSERVER_HPP_
#define _GSERVER_HPP_

extern "C" {
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <thread>
    #include <errno.h>
    #include "G/net/Gnet.h"
    #ifdef __BSD__
        #include <sys/event.h>
    #endif
}

#include "G/Object.hpp"
#include "G/StreamIO.hpp"

namespace G {

    typedef int (*taskFunc)(int fd);

    class Server : public G::Object
    {
    protected:
        int port;
    public:
        Server() {};
        virtual ~Server() {};
        virtual int initPool(int, int, int);
        virtual SOCKET initSocket() =0;
        virtual int service(G::IOEvents *, int);
    };

}
#endif