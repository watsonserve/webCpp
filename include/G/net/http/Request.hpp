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

        static int init(StreamIO *fh, HTTPRequest *request);
        HTTPRequest();
        virtual ~HTTPRequest();
        virtual void setSock(IOHandle *fh);
        virtual void setSession(void *);
        virtual void* getSession();
    };

}

#endif
