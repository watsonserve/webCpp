#ifndef _G_HTTPGRAM_HPP_
#define _G_HTTPGRAM_HPP_

#include <string>
#include <map>
#include "G/Object.hpp"

namespace G
{

    class HTTPGram : virtual Object
    {
    protected:
        std::map<std::string, std::string> data;
    public:
        void setMap(const std::map<std::string, std::string> &);
        void set(const std::string &, const std::string &);    /* left */
        void set(const char *, const std::string &);
        void set(const char *, const char *);
        void set(const char *, const long long int);
        std::string* get(const std::string &);    /* left */
        std::string* get(const char *);
        std::string& toString(std::string *dst);
    };

}

#endif
