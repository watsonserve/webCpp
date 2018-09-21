#ifndef _GUNIXSERVER_HPP_
#define _GUNIXSERVER_HPP_

#include <string>
#include "G/net/Server.hpp"

namespace G {

    class UNIXServer: public G::Server
    {
        std::string path;
    public:
        UNIXServer();
        UNIXServer(const char *path);
        UNIXServer(std::string &path);
        virtual ~UNIXServer() override;
        int setPath(const char *);
        int setPath(std::string&);
        SOCKET initSocket() override;
    };

}

#endif
