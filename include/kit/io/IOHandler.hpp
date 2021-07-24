//
//  IOHandle.hpp
//  GHTTPd
//
//  Created by JamesWatson on 16/5/9.
//  Copyright © 2016 watsserve. All rights reserved.
//

#ifndef _IOHANDLE_HPP_
#define _IOHANDLE_HPP_

#include <string>
#include "Object.hpp"
#include "Exception.hpp"

namespace G
{

    class IOStream;

    class IOHandler
    {
    public:
        virtual void onError(IOStream *, int) =0;
        virtual void onClose(IOStream *) =0;
        virtual void onData(IOStream *) =0;
        virtual void onWritten(IOStream *) =0;
    };
}

#endif /* _IOHANDLE_HPP_ */
