#ifndef _G_HTTPREQUEST_HPP_
#define _G_HTTPREQUEST_HPP_

#include <string>
#include <map>
#include "G/net/http/Gram.hpp"
#include "G/StreamIO.hpp"

namespace G {

    class HTTPRequest : public HTTPGram
    {
        IOHandle *fh;
        void* session;
        std::map<std::string, std::string> cookies;
    public:
        HTTPGram _GET;
        HTTPGram _POST;

        static int init(HTTPRequest *request, StreamIO *fh);
        HTTPRequest();
        virtual ~HTTPRequest();
        virtual IOHandle* getSock();
        virtual void setSession(void *);
        virtual void* getSession();
        void setCookies(std::map<std::string, std::string>);
        std::map<std::string, std::string> getCookies();
    };

}

#endif
