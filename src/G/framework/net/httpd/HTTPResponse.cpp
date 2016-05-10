#include <stdio.h>
#include <unistd.h>
#include "G/net/http/Response.hpp"

using namespace G;

std::map<int, std::string> HTTPResponse::statMessage;

void HTTPResponse::initDict()
{
    HTTPResponse::statMessage[200] = "OK";
    HTTPResponse::statMessage[206] = "OK";
    HTTPResponse::statMessage[301] = "OK";
    HTTPResponse::statMessage[302] = "OK";
    HTTPResponse::statMessage[304] = "NOT MODIFY";
    HTTPResponse::statMessage[401] = "OK";
    HTTPResponse::statMessage[403] = "OK";
    HTTPResponse::statMessage[404] = "NOT FOUND";
    HTTPResponse::statMessage[500] = "SERVER ERROR";
    HTTPResponse::statMessage[502] = "GATE EXCEPTION";
    HTTPResponse::statMessage[505] = "OK";
    return;
}

std::string& HTTPResponse::searchStat(int code)
{
    return HTTPResponse::statMessage[code];
}

HTTPResponse::HTTPResponse()
{
    this->set("proto", "HTTP/1.1");
    this->set("code", "200");
    this->set("stat", "OK");
	return;
}

HTTPResponse::~HTTPResponse()
{
	  return;
}

void HTTPResponse::setSock(Output *fh)
{
    this->fh = fh;
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
    turn[2] = code % 10;
    turn[1] = code / 10 % 10;
    turn[0] = code / 100 % 10;
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

int HTTPResponse::send(OutBack callback)
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
    return send(NULL);
}

void endSent(Output *fh)
{
    ((StreamIO*)fh)->close();
}

int HTTPResponse::end()
{
    return send(endSent);
}
