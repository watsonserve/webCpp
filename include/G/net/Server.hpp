#ifndef _GSERVER_HPP_
#define _GSERVER_HPP_

#include "G/Object.hpp"
#include "G/StreamIO.hpp"
extern "C" {
    #include "G/net/Gnet.h"
}

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