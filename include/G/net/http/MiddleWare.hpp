#ifndef _GMiddleware_HPP_
#define _GMiddleware_HPP_

#include "G/net/http/Request.hpp"
#include "G/net/http/Response.hpp"

namespace G
{

    typedef enum middle_type {
        MID_CLASS,
        MID_FUNC
    } MiddleType;

    typedef struct middle_handle {
        MiddleType is;
        void* that;
    } MiddleHandle;

    typedef int (*MiddleWareFunc)(G::HTTPRequest *req, G::HTTPResponse *res);
    class MiddleWare : virtual public G::Object
    {
    public:
        MiddleWare() {};
        virtual ~MiddleWare() {};
        virtual int call(G::HTTPRequest *req, G::HTTPResponse *res) =0;
    };

}

#endif
