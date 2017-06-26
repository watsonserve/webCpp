#include "G/net/http/Gram.hpp"

using namespace G;

HTTPGram::HTTPGram()
{
    return;
}

HTTPGram::~HTTPGram()
{
    return;
}

bool HTTPGram::isset(const std::string &key)
{
    return false;
}

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
    return;
}

void HTTPGram::set(const char *key, const char *value)
{
    std::string v = value;
    set(key, v);
    return;
}

void HTTPGram::set(const char *key, const long long value)
{
    char buf[24];
    sprintf(buf, "%lld", value);
    set(key, buf);
}

std::string& HTTPGram::get(const std::string &key)
{
	  return data[key];
}

std::string& HTTPGram::get(const char *key)
{
    std::string k = key;
    return data[k];
}