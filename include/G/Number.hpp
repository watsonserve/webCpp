//
//  Number.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/9/25.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef Number_h
#define Number_h

#include "G/Object.hpp"

namespace G
{
    class Number : public Object
    {
    public:
        static long parseInt(const char *);
        static unsigned long parseUInt(const char *);
        static long long parseInt64(const char *);
        static unsigned long long parseUInt64(const char *);
        
        static std::string stringify(long long);
        static std::string stringify(unsigned long long);
    };
}

#endif /* Number_h */
