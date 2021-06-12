#include "G/net/http/Dispatcher.hpp"

typedef struct HTTP_Error
{
    int code;
    std::string message;
} HTTPError;

typedef enum middle_type {
    MID_CLASS,
    MID_FUNC
} MiddleType;

typedef struct middle_handle {
    MiddleType is;
    void* that;
} MiddleHandle;

using namespace G;

HTTPDispatcher::HTTPDispatcher()
{
}

int HTTPDispatcher::init(int max)
{
    requests = new HTTPRequest[max];
    responses = new HTTPResponse[max];
    if(nullptr == requests || nullptr == responses)
        return -1;
    return 0;
}

void setFd(int fd)
{
    /*
        aio(fd)
        thread_pool
    *//*
        eventListener.emit(fd)
    */
}

void HTTPDispatcher::onClose(StreamIO *fh)
{
    printf("on %d close\n", fh->getFd());
}

void HTTPDispatcher::onError(StreamIO *fh)
{
    printf("on %d error\n", fh->getFd());
}

void HTTPDispatcher::onData(StreamIO *fh)
{
    int ret;
    HTTPRequest *request;
    HTTPResponse *response;

    ret = fh->getFd();
    request = requests + ret;
    response = responses + ret;
    HTTPResponse::init(response, (Output*)fh);
    HTTPRequest::init(request, fh);
    for (std::list<MiddleHandle>::iterator it = this->process.begin(); it != this->process.end(); ++it)
    {
        try {
            if (MID_FUNC == it->is)
                ret = ((MiddleWareFunc)(it->that))(request, response);
            else
                ret = ((MiddleWare *)(it->that))->call(request, response);
            if( ret )    /* 0 continue, 1 finish */
            {
                return;
            }
        } catch(HTTPError err) {
            response->setCode( 500 );    /* set response stat code */
            response->setContent( err.message );
            break;
        }
    }
    return;
}

int HTTPDispatcher::use(MiddleWare* middleware)
{
    MiddleHandle ware;
    ware.is = MID_CLASS;
    ware.that = middleware;
    this->process.push_back(ware);
    return 0;
}

int HTTPDispatcher::use(MiddleWareFunc middleware)
{
    MiddleHandle ware;
    ware.is = MID_FUNC;
    ware.that = (void*)middleware;
    this->process.push_back(ware);
    return 0;
}

HTTPDispatcher::~HTTPDispatcher()
{
    return;
}
