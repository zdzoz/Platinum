//
// Created by Oskar Zdziarski on 7/10/23.
//

#pragma once

#include "Event.h"

namespace Platinum {
    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_TYPE(WindowClose);
    };

    class WindowResizeEvent : public Event {
        int _width, _height;
    public:
        WindowResizeEvent(int width, int height) : _width(width), _height(height) {}

        EVENT_TYPE(WindowResize);

        std::string toString() const override {
            std::stringstream ss;
            ss << name() << ": (" << _width << ", " << _height << ")";
            return ss.str();
        }
    };
}