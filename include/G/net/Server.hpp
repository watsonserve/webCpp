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
#include "G/net/Protocoler.hpp"

namespace G {
    class Server : virtual public G::Object
    {
    protected:
        virtual SOCKET initSocket() =0;
        virtual int _service(G::Protocoler *, int) =0;
    public:
        Server() {};
        virtual ~Server() =0;
    };
}
#endif