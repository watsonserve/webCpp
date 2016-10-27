#include <stdio.h>
#include <stdlib.h>
#include "G/GUtil.hpp"
#include "G/net/http/Request.hpp"
#include "G/net/URL.hpp"

using namespace std;
using namespace G;

int HTTPRequest::init(HTTPRequest *request, StreamIO *fh)
{
    request->fh = fh;
    string tmp, str, data, firstRow;
    vector<string> foo, bar;
    URL uri;

    tmp = fh->gets(tmp, CRLF);
    split(foo, tmp, " ");    /* 获取第一行 'GET URI HTTP/1.1' */
    // if(foo.size() != 3)
    // {
    //     puts(tmp.c_str());
    //     exit(1);
    // }
    request->set("method", foo[0]);
    request->set("protocol", foo[2]);
    URL::parse(&uri, foo[1]);
    while (1)    /* 设定从第二行开始的每一行 */
    {
        str = fh->gets(str, CRLF);
        if (str.empty())
            break;
        split(foo, str, ": ");
        request->set(foo[0], foo[1]);
    }
    request->set("path", uri.getPath());
    // todo
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

void HTTPRequest::setCookies(std::map<std::string, std::string> cookies)
{
    this->cookies = cookies;
    return;
}

std::map<std::string, std::string> HTTPRequest::getCookies()
{
    return this->cookies;
}


