#ifndef _G_HTTPGRAM_HPP_
#define _G_HTTPGRAM_HPP_

#include <string>
#include <map>
#include "G/Object.hpp"

namespace G {

    class HTTPGram : virtual Object
    {
    protected:
        std::map<std::string, std::string> data;
    public:
        HTTPGram();
        virtual ~HTTPGram();
        virtual bool isset(const std::string &key);
        virtual void setMap(const std::map<std::string, std::string> &);
        virtual void set(const std::string &key, const std::string &value);    /* left */
        virtual void set(const char *key, const std::string &value);
        virtual void set(const char *key, const char *value);
        virtual void set(const char *key, const long long value);
        virtual std::string& get(const std::string &key);    /* left */
        virtual std::string& get(const char *key);
    };

}

#endif
