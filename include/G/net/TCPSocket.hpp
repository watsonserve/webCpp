#ifndef _GTCPSERVER_HPP_
#define _GTCPSERVER_HPP_

#include <string>
#include "G/Object.hpp"
#include "G/net/Socket.hpp"

namespace G
{

    class TCPSocket: virtual public G::Object, virtual public G::Socket
    {
        unsigned short port;
        std::string cert;
        std::string key;
    protected:
        virtual void initSocket() override;
    public:
        TCPSocket();
        virtual ~TCPSocket();
        int setPort(unsigned short);
        int setCert(const char *);
        int setKey(const char *);
    };

}

#endif
