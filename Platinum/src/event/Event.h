//
// Created by Oskar Zdziarski on 7/10/23.
//

#pragma once

namespace Platinum {
    enum class Key {
        none = -1,
        shift = 0x0001,
        ctrl = 0x0002,
        alt = 0x0004,
        super = 0x0008,
        caps_lock = 0x0010,
        num_lock = 0x0020,
    };

    enum class EventType {
        None = 0,
        WindowClose, WindowResize,
        MousePos, MouseDown, MouseUp,
        KeyDown, KeyUp
    };

#define EVENT_TYPE(type) inline EventType getType() const override {  \
                            return EventType::type;                 \
                         }                                            \
                         inline static EventType getTypeStatic() {    \
                            return EventType::type;                 \
                         }                                            \
                         const char* name() const override {          \
                            return #type;                             \
                         }

    class Event {
        friend class EventDispatcher;
        bool _handled = false;
    public:
        virtual EventType getType() const = 0;
        virtual const char* name() const = 0;
        virtual std::string toString() const { return name(); };
    };

    class EventDispatcher {
        Event& _event;
    public:
        EventDispatcher(Event& e) : _event(e) {}

        template<typename T>
        bool dispatch(std::function<bool(T&)> func) {
            if (_event.getType() == T::getTypeStatic()) {
                _event._handled = func(*(T*)&_event);
                return true;
            }
            return false;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.toString();
    }
}
