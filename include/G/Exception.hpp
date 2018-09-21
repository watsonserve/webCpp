//
//  Exception.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 2017/3/19.
//  Copyright © 2017年 watsserve. All rights reserved.
//

#ifndef _Exception_HPP_
#define _Exception_HPP_

#include "G/Object.hpp"

namespace G {

    class Exception : public Object
    {
        void constructor();
    protected:
        std::string msg;
    public:
        Exception();
        virtual ~Exception() {};
        Exception(const char *, size_t);
        Exception(std::string &);
        Exception(Exception &);
        virtual const char *operator = (const char *);
        virtual std::string &operator = (std::string &);
        virtual Exception &operator = (Exception &);
        virtual std::string toString();
    };

}

#endif /* Exception_h */
