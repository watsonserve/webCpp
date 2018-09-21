//
//  G.hpp
//
//  Created by 王兴卓 on 16/3/19.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _G_HPP_
#define _G_HPP_

#include <string>

namespace G {

    class Object
    {
    protected:
        std::string isA;
    public:
        static void init(Object &, std::string &a);
        static void init(Object &, char *a);
        void getIsA(std::string &a);
        std::string getIsA();
    };

    typedef void* (*Func)(void *);

}

#endif /* _G_HPP_ */
