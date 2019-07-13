#ifndef _GUNIXSERVER_HPP_
#define _GUNIXSERVER_HPP_

#include <string>
#include "G/net/StreamServer.hpp"

namespace G {

    class UNIXServer: public G::StreamServer
    {
        std::string path;
    protected:
        SOCKET initSocket() override;
    public:
        UNIXServer();
        UNIXServer(const char *path);
        UNIXServer(std::string &path);
        virtual ~UNIXServer() override;
        int setPath(const char *);
        int setPath(std::string&);
    };

}

#endif
