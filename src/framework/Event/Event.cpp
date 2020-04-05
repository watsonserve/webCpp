//
//  Event.cpp
//  GHTTPd
//
//  Created by James on 18/10/12.
//  Copyright © 2018 watsserve. All rights reserved.
//

#include "G/event/Event.hpp"

G::Event::Event() {}

G::Event::Event(const G::Event &ev) : Event()
{
    this->context = ev.context;
    this->function = ev.function;
    this->ident = ev.ident;
    this->event_type = ev.event_type;
    this->magic = ev.magic;
}

G::Event::~Event() {}
