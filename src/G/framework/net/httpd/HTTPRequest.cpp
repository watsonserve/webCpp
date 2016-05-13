#include <stdio.h>
#include "G/GUtil.hpp"
#include "G/net/http/Request.hpp"

using namespace std;
using namespace G;

int HTTPRequest::init(StreamIO *fh, HTTPRequest *request)
{
    int tmpFlag;
    string tmp, str, data, firstRow;
    vector<string> foo, bar;

    request->setSock(fh);
    tmp = fh->gets();
    split(foo, tmp, " ");
    if(foo.size() != 3)
    {
        puts(tmp.c_str());
        exit(1);
    }
    request->set("method", foo[0]);
    request->set("protocol", foo[2]);
    tmp = foo[1];
    while(1)    /* 设定从第二行开始的每一行 */
    {
        str = fh->gets();
        if(str.empty())
            break;
        split(foo, str, ": ");    /* 获取第一行 'GET URI HTTP/1.1' */
        request->set(foo[0], foo[1]);
    }
    tmpFlag = 0;  /* 0 path, 1 args, 2 hash */
    for(unsigned int i=0; i<tmp.length(); i++)
    {
        if( '?' == tmp[i] || '#' == tmp[i] )
        {
            str = tmp.substr(0, i);
            request->set("path", str);
            if( '?' == tmp[i] )
            {
                tmpFlag = 1;
                tmp = tmp.erase(0, i+1);
            }
            else
            {
                tmpFlag = 2;
            }
            break;
        }
    }
    if( 0 == tmpFlag )
    {
        request->set("path", tmp);
    }
    if( 1 == tmpFlag )  /* set query */
    {
        int begin = 0;
        int kvFlag = 0;
        string key;
        unsigned int i;
        for(i=0; i<tmp.length(); i++)
        {
            switch( tmp[i] )
            {
                case '=':
                    key = tmp.substr(begin, i-begin);
                    kvFlag = 1;
                    break;
                case '&':
                    if(kvFlag)
                    {
                        request->_GET.set(key, tmp.substr(begin, i-begin));
                        kvFlag = 0;
                    }
                    break;
                default:
                    continue;
            }
            begin = i +1;
        }
        if(kvFlag)
        {
            if( 0 == i-begin )
                request->_GET.set(key, "");
            else
                request->_GET.set(key, tmp.substr(begin, i-begin));
        }
    }
    return 0;
}

/* 开始解析post参数 */
    // contentType = request->get("Content-Type");
    // if( "multipart/form-data" == contentType.substr(0, 19) )    /* multipart/form-data; boundary=----XXXX */
    // {
    //     boundary = contentType.substr(30);
    //     /* to do */
    // }
    // else
    // {
    //     vector<string> bar;
    //     split(foo, gram[1], "&");    /* 分割get参数 */
    //     len = foo.size();
    //     for(int i=0; i<len; i++)    /* 设定从第二行开始的每一行 */
    //     {
    //         split(bar, foo[i], "=");    /* 分割键值对 */
    //         request->_POST.set(bar[0], bar[1]);
    //     }
    // }

HTTPRequest::HTTPRequest()
{
    return;
}

HTTPRequest::~HTTPRequest()
{
    return;
}

void HTTPRequest::setSock( G::IOHandle *fh )
{
    this->fh = fh;
    return;
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
