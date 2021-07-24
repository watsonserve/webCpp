//
//  var.cpp
//  GHTTPd
//
//  Created by James on 18/6/18.
//  Copyright © 2018 watsserve. All rights reserved.
//

#include "G/var.hpp"

using namespace G;

Var::Var()
{

}

Var::Var(const Var &foo)
{
    this->type = foo.type;
    this->data = foo.data;
    this->v_string = foo.v_string;
    this->v_dict = foo.v_dict;
}

Var::Var(const std::vector<Var> &foo)
{
    this->type = Array;
    this->v_array = foo;
}

Var::Var(const std::map<std::string, Var> &foo)
{
    this->type = var_type_t::Object;
    this->v_dict = foo;
}

Var::Var(const char foo)
{
    this->type = String;
    this->v_string = foo;
}

Var::Var(const char *foo)
{
    this->type = String;
    this->v_string = foo;
}

Var::Var(const std::string &foo)
{
    this->type = String;
    this->v_string = foo;
}

Var::Var(const bool foo)
{
    this->type = Bool;
    this->data.v_bool = foo;
}

Var::Var(const double foo)
{
    this->type = Float;
    this->data.v_float = foo;
}

Var::Var(const long long foo)
{
    this->type = Int;
    this->data.v_int64 = foo;
}

Var Var::setArray(const std::string *foo, const int len)
{
    Var container;

    this->type = Array;
    for (int i = 0; i < len; i++)
    {
        container = foo[i];
        this->v_array.push_back(container);
    }
    return *this;
}

Var Var::setArray(const Var *foo, const int len)
{
    this->type = Array;
    for (int i = 0; i < len; i++)
    {
        this->v_array.push_back(foo[i]);
    }
    return *this;
}

std::string Var::toString()
{
    std::vector<Var> &v_array = this->v_array;
    std::string ret = "";

    switch (this->type)
    {
        case Bool:
            return this->data.v_bool ? "true" : "false";
        case String:
            return "\"" + this->v_string + "\"";
        case Array:
            ret = "[";
            for (auto i = std::begin(v_array); i != std::end(v_array); i++)
            {
                ret += i->toString() + ", ";
            }
            ret = ret.erase(ret.length() - 2, 2);
            ret += "]";
            return ret;
        case var_type_t::Object:
            //return this->v_dict.keys();
        default:
            return ret;
    }
}
