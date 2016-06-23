#ifndef _G_HTTPREQUEST_HPP_
#define _G_HTTPREQUEST_HPP_

#include "G/net/http/Gram.hpp"
#include "G/StreamIO.hpp"

namespace G {

    class HTTPRequest : public HTTPGram
    {
        IOHandle *fh;
        void* session;
    public:
        HTTPGram _GET;
        HTTPGram _POST;

        static int init(HTTPRequest *request, StreamIO *fh);
        HTTPRequest();
        virtual ~HTTPRequest();
        virtual IOHandle* getSock();
        virtual void setSession(void *);
        virtual void* getSession();
    };

}

#endif
