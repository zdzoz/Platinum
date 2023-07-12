//
// Created by Oskar Zdziarski on 7/10/23.
//

#pragma once

#include "Event.h"

// Mouse Macros
#define PLAT_MB_1         0
#define PLAT_MB_2         1
#define PLAT_MB_3         2
#define PLAT_MB_4         3
#define PLAT_MB_5         4
#define PLAT_MB_6         5
#define PLAT_MB_7         6
#define PLAT_MB_8         7
#define PLAT_MB_LEFT      PLAT_MB_1
#define PLAT_MB_RIGHT     PLAT_MB_2
#define PLAT_MB_MIDDLE    PLAT_MB_3

namespace Platinum {
    enum MB {
        MB_NONE = -1,
        MB1 = 0, MB2, MB3, MB4, MB5, MB6, MB7, MB8,
        MBL = MB1,
        MBR = MB2,
        MBM = MB3
    };

    class MousePosEvent : public Event {
        double _x, _y;
    public:
        MousePosEvent(double x, double y) : _x(x), _y(y) {}

        EVENT_TYPE(MousePos);

        std::string toString() const override {
            std::stringstream ss;
            ss << name() << std::fixed << std::setprecision(2) << ": (" << _x << ", " << _y << ")";
            return ss.str();
        }
    };

    class MouseDownEvent : public Event {
        MB _button;
        Key _mod;
    public:
        MouseDownEvent(MB button, Key mod) : _button(button), _mod(mod) {}

        EVENT_TYPE(MouseDown);

        std::string toString() const override {
            std::stringstream ss;
            ss << name() << ": MB" << _button << ", " << (int)_mod << std::endl;
            return ss.str();
        }
    };

    class MouseUpEvent : public Event {
        MB _button;
        Key _mod;
    public:
        MouseUpEvent(MB button, Key mod) : _button(button), _mod(mod) {}

        EVENT_TYPE(MouseUp);

        std::string toString() const override {
            std::stringstream ss;
            ss << name() << ": MB" << _button << ", " << (int)_mod << std::endl;
            return ss.str();
        }
    };
}