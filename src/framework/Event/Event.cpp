//
//  Event.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 18/10/12.
//  Copyright © 2018年 watsserve. All rights reserved.
//

#include "G/event/Event.hpp"

G::Event::Event()
{
    this->isA = "Event";
}

G::Event::Event(G::Event &ev)
{
    this->isA = "Event";
    this->context = ev.context;
    this->function = ev.function;
    this->ident = ev.ident;
    this->event_type = ev.event_type;
}
