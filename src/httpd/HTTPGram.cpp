#include "http/Gram.hpp"

using namespace G;

void HTTPGram::setMap(const std::map<std::string, std::string> &data)
{
    this->data = data;
}

void HTTPGram::set(const std::string &key, const std::string &value)
{
    data[key] = value;
    return;
}

void HTTPGram::set(const char *key, const std::string &value)
{
    std::string k = key;
    set(k, value);
}

void HTTPGram::set(const char *key, const char *value)
{
    std::string k = key;
    std::string v = value;
    set(k, v);
}

void HTTPGram::set(const char *key, const long long int value)
{
    char buf[24];
    sprintf(buf, "%lld", value);
    set(key, buf);
}

std::string* HTTPGram::get(const std::string &key)
{
    try
    {
	    return &data.at(key);
    }
    catch (...)
    {
        return nullptr;
    }
}

std::string* HTTPGram::get(const char *key)
{
    std::string k = key;
    return get(k);
}

std::string& HTTPGram::toString(std::string *dst)
{
    for (auto& x: data)
    {
        *dst += x.first + ": " + x.second + "\r\n";
    }
    return *dst;
}
