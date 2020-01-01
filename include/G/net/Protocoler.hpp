#ifndef _PROTOCOLER_HPP_
#define _PROTOCOLER_HPP_

#include "G/event/Event.hpp"

namespace G {
    class Protocoler : virtual public G::Object
    {
    public:
        Protocoler() {};
        virtual ~Protocoler() =0;
        virtual void onData(int, G::event_type_t) =0;
    };
}

#endif
