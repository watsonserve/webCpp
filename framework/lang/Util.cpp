#include "GUtil.hpp"

using namespace std;

ssize_t G::split(vector<string> &ret, const string &str, const char *sep, unsigned int limit)
{
    string sep_str = sep;
    return G::split(ret, str, sep_str, limit);
}

ssize_t G::split(vector<string> &ret, const string &str, const string &sep, unsigned int limit)
{
    if (str.empty())
    {
        return -1;
    }
    ret.clear();
    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;
    unsigned int i;

    for (i = 0; i < limit && string::npos != pos_begin; i++)
    {
        comma_pos = str.find(sep, pos_begin);
        if (string::npos != comma_pos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }
        if (!tmp.empty())
        {
            ret.push_back(tmp);
            tmp.clear();
        }
    }
    return pos_begin;
}
