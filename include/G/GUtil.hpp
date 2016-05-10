#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <string>
#include <vector>

using namespace std;

namespace G {
    int split(vector<string> &ret, const string &str, const char *sep);
    int split(vector<string> &ret, const string &str, const string &sep);
}

#endif
