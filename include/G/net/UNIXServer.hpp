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
        virtual ~UNIXServer();
        virtual int initPool(int, int, int);
        int setPath(const char *);
        int setPath(std::string&);
        virtual int service(G::IOEvents *, int max);
    };

}

#endif
