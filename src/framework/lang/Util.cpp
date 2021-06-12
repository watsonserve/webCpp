#include "G/GUtil.hpp"

using namespace std;

int G::split(vector<string> &ret, const string &str, const char *sep)
{
    string sep_str = sep;
    return split(ret, str, sep_str);
}

int G::split(vector<string> &ret, const string &str, const string &sep)
{
    if (str.empty()) {
        return -1;
    }
    ret.clear();
    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while(string::npos != pos_begin)
    {
        comma_pos = str.find(sep, pos_begin);
        if( string::npos != comma_pos )
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
    return 0;
}

