//
//  IO.hpp
//
//  Created by JamesWatson on 16/4/13.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _G_IO_HPP_
#define _G_IO_HPP_

#include "G/Object.hpp"

namespace G
{

    class IO : public virtual Object
    {
        protected:
            int fd;
        public:
            IO(int);
            virtual ~IO();
            void close();
    };
}

#endif /* _G_IO_HPP_ */
