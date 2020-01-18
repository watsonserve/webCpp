#ifndef _G_UNIXSOCKET_HPP_
#define _G_UNIXSOCKET_HPP_

#include <string>
#include "G/net/Socket.hpp"

namespace G
{

    class UNIXSocket: virtual public G::Socket
    {
        std::string path;
    protected:
        virtual void initSocket() override;
    public:
        UNIXSocket(const char *);
        UNIXSocket(std::string &);
        virtual ~UNIXSocket();
        int setPath(const char *);
        int setPath(std::string &);
    };

}

#endif
