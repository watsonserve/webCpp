//
//  IOHandle.hpp
//  GHTTPd
//
//  Created by JamesWatson on 16/5/9.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _IOHANDLE_HPP_
#define _IOHANDLE_HPP_

#include <string>
#include "G/Object.hpp"
#include "G/Exception.hpp"

namespace G
{

    class FDHandler
    {
    public:
        virtual void onOpen(IOStream *) =0;
        virtual void onError(IOStream *, int) =0;
        virtual void onClose(IOStream *) =0;
    };

    class InputHandler : public virtual FDHandler
    {
    public:
        virtual void onData(IOStream *) =0;
    };

    class OutputHandler : public virtual FDHandler
    {
    public:
        virtual void onWritten(IOStream *, ssize_t) =0;
    };

    class IOHandler : virtual public InputHandler, virtual public OutputHandler
    {
    };
}

#endif /* _IOHandle_h_ */
