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
        // 构造函数
        Exception(std::string &);
        Exception(const char *, size_t);
        // 拷贝构造函数
        Exception(Exception &);
        // 析构函数
        virtual ~Exception() {};
        virtual const char *operator = (const char *);
        virtual std::string &operator = (std::string &);
        virtual Exception &operator = (Exception &);
        virtual std::string toString();
    };

}

#endif /* Exception_h */
