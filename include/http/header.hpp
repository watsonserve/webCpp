#ifndef _G_HTTP_HEADER_HPP_
#define _G_HTTP_HEADER_HPP_

#include "http/Gram.hpp"

extern "C"
{
    #include "http/http_srv.h"
}

namespace G
{

    class HTTPHeader : public HTTPGram
    {
    public:
        std::string& toString(std::string *dst);
    };

}

struct http_header_t
{
    G::HTTPHeader header;
};

#endif
