//
//  Exception.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 2017/3/19.
//  Copyright © 2017年 watsserve. All rights reserved.
//

#include "G/Exception.hpp"

using namespace G;

void Exception::constructor()
{
    Exception::isA = "Exception";
}

Exception::Exception()
{
    this->constructor();
    this->msg = "success";
}

Exception::Exception(std::string &msg)
{
    this->constructor();
    this->msg = msg;
}

Exception::Exception(const char *msg, size_t len = 0)
{
    this->constructor();
    0 == len ? this->msg = msg : this->msg.assign(msg, len);
}

// copy
Exception::Exception(Exception &exception)
{
    this->constructor();
    this->msg = exception.msg;
}

// reload operator
std::string & Exception::operator=(std::string &msg)
{
    this->msg = msg;
    return msg;
}

const char * Exception::operator=(const char *msg)
{
    this->msg = msg;
    return msg;
}

Exception& Exception::operator=(Exception &exception)
{
    this->msg = exception.msg;
    return exception;
}

std::string Exception::toString()
{
    return this->msg;
}
