#include "http/header.hpp"

using namespace G;

std::string& Header::toString(std::string *dst)
{
    for (auto& x: data)
    {
        *dst += x.first + ": " + x.second + "\r\n";
    }
    return *dst;
}
