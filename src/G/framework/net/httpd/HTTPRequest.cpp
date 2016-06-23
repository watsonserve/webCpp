#include <stdio.h>
#include <stdlib.h>
#include "G/GUtil.hpp"
#include "G/net/http/Request.hpp"

using namespace std;
using namespace G;

int HTTPRequest::init(HTTPRequest *request, StreamIO *fh)
{
    request->fh = fh;
    return 0;
}

HTTPRequest::HTTPRequest()
{
}

HTTPRequest::~HTTPRequest()
{
    return;
}

IOHandle * HTTPRequest::getSock()
{
    return fh;
}

void HTTPRequest::setSession(void * session)
{
    this->session = session;
    return;
}

void* HTTPRequest::getSession()
{
    return this->session;
}
