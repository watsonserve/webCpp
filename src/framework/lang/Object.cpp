//
//  Object.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/4/12.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/Object.hpp"

using namespace G;


void Object::init(Object &obj, std::string &a)
{
    obj.isA = a;
}

void Object::init(Object &obj, char *a)
{
    obj.isA = a;
}

void Object::setIsA(std::string &a)
{
    this->isA = a;
    return;
}

std::string Object::getIsA()
{
    return this->isA;
}