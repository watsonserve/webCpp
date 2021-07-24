//
//  G.hpp
//
//  Created by James on 16/3/19.
//  Copyright © 2016 watsserve. All rights reserved.
//

#ifndef _G_HPP_
#define _G_HPP_

#include "stdafx.h"
#include <string>

namespace G
{

    class Object
    {
        public:
            std::string isA;
    };

    typedef void* (*Func)(void *);

}

#endif /* _G_HPP_ */
