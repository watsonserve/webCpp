//
//  Number.hpp
//  GHTTPd
//
//  Created by James on 16/9/25.
//  Copyright © 2016 watsserve. All rights reserved.
//

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "G/Object.hpp"

namespace G
{
    class Number : virtual public Object
    {
    public:
        static long parseInt(const char *);
        static unsigned long parseUInt(const char *);
        static long long parseInt64(const char *);
        static unsigned long long parseUInt64(const char *);
    };
}

#endif /* _NUMBER_H_ */
