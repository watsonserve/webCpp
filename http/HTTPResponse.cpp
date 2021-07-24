#include <stdio.h>
#include <unistd.h>
#include "G/net/http/Response.hpp"

using namespace G;

std::map<int, std::string> HTTPResponse::statMessage;

void HTTPResponse::initDict()
{
    HTTPResponse::statMessage[100] = "Continue";
    HTTPResponse::statMessage[101] = "Switching Protocols";
    HTTPResponse::statMessage[102] = "Processing";
    HTTPResponse::statMessage[200] = "OK";
    HTTPResponse::statMessage[201] = "Created";
    HTTPResponse::statMessage[202] = "Accepted";
    HTTPResponse::statMessage[203] = "Non-Authoritative Information";
    HTTPResponse::statMessage[204] = "No Content";
    HTTPResponse::statMessage[205] = "Reset Content";
    HTTPResponse::statMessage[206] = "Partial Content";
    HTTPResponse::statMessage[207] = "Multi-Status";
    HTTPResponse::statMessage[300] = "Multiple Choices";
    HTTPResponse::statMessage[301] = "Moved Permanently";
    HTTPResponse::statMessage[302] = "Found";
    HTTPResponse::statMessage[303] = "See Other";
    HTTPResponse::statMessage[304] = "Not Modified";
    HTTPResponse::statMessage[305] = "Use Proxy";
    HTTPResponse::statMessage[306] = "Switch Proxy";
    HTTPResponse::statMessage[307] = "Temporary Redirect";
    HTTPResponse::statMessage[400] = "Bad Request";
    HTTPResponse::statMessage[401] = "Unauthorized";
    HTTPResponse::statMessage[402] = "Payment Required";
    HTTPResponse::statMessage[403] = "Forbidden";
    HTTPResponse::statMessage[404] = "Not Found";
    HTTPResponse::statMessage[405] = "Method Not Allowed";
    HTTPResponse::statMessage[406] = "Not Acceptable";
    HTTPResponse::statMessage[408] = "Request Timeout";
    HTTPResponse::statMessage[409] = "Conflict";
    HTTPResponse::statMessage[410] = "Gone";
    HTTPResponse::statMessage[411] = "Length Required";
    HTTPResponse::statMessage[412] = "Precondition Failed";
    HTTPResponse::statMessage[414] = "Request-URI Too Long";
    HTTPResponse::statMessage[417] = "Expectation Failed";
    HTTPResponse::statMessage[422] = "Unprocessable Entity";
    HTTPResponse::statMessage[423] = "Locked";
    HTTPResponse::statMessage[424] = "Failed Dependency";
    HTTPResponse::statMessage[425] = "Unordered Collection";
    HTTPResponse::statMessage[426] = "Upgrade Required";
    HTTPResponse::statMessage[449] = "Retry With";
    HTTPResponse::statMessage[500] = "Internal Server Error";
    HTTPResponse::statMessage[501] = "Not Implemented";
    HTTPResponse::statMessage[502] = "Bad Gateway";
    HTTPResponse::statMessage[503] = "Service Unavailable";
    HTTPResponse::statMessage[504] = "Gateway Timeout";
    HTTPResponse::statMessage[507] = "Insufficient Storage";
    HTTPResponse::statMessage[508] = "Loop Detected";
    HTTPResponse::statMessage[510] = "Not Extended";
    return;
}

std::string& HTTPResponse::searchStat(int code)
{
    return HTTPResponse::statMessage[code];
}

HTTPResponse::HTTPResponse()
{
}

HTTPResponse::~HTTPResponse()
{
	  return;
}

void HTTPResponse::init(HTTPResponse *that, Output *fh)
{
    that->fh = fh;
    that->set("proto", "HTTP/1.1");
    that->set("code", "200");
    that->set("stat", "OK");
    that->set("Connection", "close");
    that->set("Content-Type", "text/plain; charset=UTF-8");
    return;
}

Output* HTTPResponse::getSock()
{
    return fh;
}

void HTTPResponse::setCode(int code)
{
    char turn[4];
    std::string s;

    turn[3] = 0;
    turn[2] = '0' + (code % 10);
    turn[1] = '0' + (code / 10 % 10);
    turn[0] = '0' + (code / 100 % 10);
    s = turn;
    this->set("code", s);
    s = searchStat(code);
    this->set("stat", s);
    return;
}

void HTTPResponse::setContent(std::string &content)
{
    this->content = content;
    return;
}

void HTTPResponse::setContent(const char *content)
{
    this->content = content;
    return;
}

std::string HTTPResponse::getHeaders()
{
    std::string ret;
    std::map<std::string, std::string>::iterator it;

    ret = data["proto"] + " ";
    ret += data["code"] + " ";
    ret += data["stat"] + " \r\n";
    for (it = data.begin(); data.end() != it; it++)
    {
        if("proto" == it->first || "code" == it->first || "stat" == it->first) {
            continue;
        }
        ret += it->first;
        ret += ": ";
        ret += it->second;
        ret += "\r\n";
    }
    return ret;
}

int HTTPResponse::send(G::Func callback)
{
    std::string gram;
    this->set("Content-Length", this->content.length());
    gram = this->getHeaders() + "\r\n";
    gram += this->content + "\r\n";
    fh->write(gram, callback);
    return 0;
}

int HTTPResponse::send()
{
    return send(nullptr);
}

void endSent(Output *fh)
{
    ((StreamIO*)fh)->close();
}

int HTTPResponse::end()
{
    return send((G::Func)endSent);
}
