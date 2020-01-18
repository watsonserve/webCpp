#ifndef _IOHUB_HPP_
#define _IOHUB_HPP_

#include <map>
#include "G/event/EventListener.hpp"
#include "G/io/IOHandler.hpp"
#include "G/io/IOStream.hpp"

namespace G
{
    class IOHub: public virtual G::Object
    {
    private:
        G::EventListener *listener;
        std::map<int, G::IOStream *> streams;
    protected:
        void listen(int, IOHandler *);
    public:
        IOHub(G::EventListener *);
        virtual ~IOHub();
    };
}

#endif
