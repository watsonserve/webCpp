#ifndef _G_HTTPREQUEST_HPP_
#define _G_HTTPREQUEST_HPP_

#include <string>
#include <map>
#include "http/Gram.hpp"
#include "G/io/IOStream.hpp"

namespace G
{

    class HTTPRequest : virtual public HTTPGram
    {
        IOHandler *fh;
        void* session;
        std::map<std::string, std::string> cookies;
    public:

        static int init(HTTPRequest *request, IOStream *fh);
        HTTPRequest();
        virtual ~HTTPRequest();
        virtual IOStream* getSock();
        virtual void setSession(void *);
        virtual void* getSession();
        void setCookies(std::map<std::string, std::string>);
        std::map<std::string, std::string> getCookies();
    };

}

#endif
