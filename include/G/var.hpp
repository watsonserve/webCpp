#ifndef __VAR_HPP__
#define __VAR_HPP__

#include <string>
#include <vector>
#include <map>
#include "G/Object.hpp"

typedef enum {
    Null,
    Object,
    Int,
    Float,
    Bool,
    String,
    Array
} var_type_t;

typedef union {
    long long         v_int64;
    double            v_float;
    bool              v_bool;
} var_t;

namespace G {
    class Var : virtual public Object
    {
        var_type_t type;
        var_t data;
        std::string v_string;
        std::vector<Var> v_array;
        std::map<std::string, Var> v_dict;

        public:
            Var();
            Var(const Var &);
            Var(const char *);
            Var(const std::vector<Var> &);
            Var(const std::map<std::string, Var> &);
            Var(const std::string &);
            Var(const char);
            Var(const double);
            Var(const bool);
            Var(const long long);
            virtual ~Var() {}

            Var setArray(const std::string *, const int);
            Var setArray(const Var *, const int);
            std::string toString();
    };
}

#endif
