//
//  Object.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/4/12.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/Object.hpp"

using namespace G;

void Object::getIsA(std::string &a)
{
    a = this->isA;
    return;
}

std::string Object::getIsA()
{
    return this->isA;
}