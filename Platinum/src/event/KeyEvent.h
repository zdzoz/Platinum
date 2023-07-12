//
// Created by Oskar Zdziarski on 7/10/23.
//

#pragma once

#include "Event.h"

namespace Platinum {
    class KeyDownEvent : public Event {

    public:
        KeyDownEvent() : {}

        EVENT_TYPE(KeyDown);

        std::string toString() override {
            std::cout << ""
        }
    };
}