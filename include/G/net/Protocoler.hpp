#ifndef _PROTOCOLER_HPP_
#define _PROTOCOLER_HPP_

#include "G/event/Event.hpp"

namespace G {
    class Protocoler
    {
    public:
        virtual void onData(int, G::event_type_t) =0;
    };
}

#endif
