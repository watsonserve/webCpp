#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <string>
#include <vector>

namespace G
{
    ssize_t G::split(std::vector<std::string> &, const std::string &, const char *, unsigned int);
    ssize_t G::split(std::vector<std::string> &, const std::string &, const std::string &, unsigned int);
}

#endif
