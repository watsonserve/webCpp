#ifndef _GSERVER_HPP_
#define _GSERVER_HPP_

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
        int setPort(int);
        virtual int service(G::IOEvents *, int) =0;
    };

}
#endif