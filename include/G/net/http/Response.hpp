#ifndef _GHTTPRESPONSE_HPP_
#define _GHTTPRESPONSE_HPP_

#include <string>
#include <map>
#include "G/net/http/Gram.hpp"
#include "G/StreamIO.hpp"

namespace G {

    class HTTPResponse : public G::HTTPGram
    {
        std::string content;
        static std::map<int, std::string> statMessage;
        std::string& searchStat(int code);
        Output *fh;
        virtual std::string getHeaders();
    public:
        static void initDict();
        static void init(HTTPResponse *that, Output *fh);
        HTTPResponse();
        virtual ~HTTPResponse();
        virtual Output* getSock();
        virtual void setCode(int code);
        virtual void setContent(std::string &content);
        virtual void setContent(const char *content);
        virtual int send();
        virtual int send(G::Func);
        virtual int end();
    };

}

#endif
