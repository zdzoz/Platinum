//
// Created by Oskar Zdziarski on 7/10/23.
//

#pragma once

#include "Event.h"

namespace Platinum {
    struct KeyAction {
        enum {
            Up, Down, Repeat
        };
    };
    class KeyDownEvent : public Event {
        Key key, native_key, modifier;
    public:
        KeyDownEvent(Key key, Key native_key, Key modifier) : key(key), native_key(native_key), modifier(modifier) {}

        EVENT_TYPE(KeyDown);

        std::string toString() const override {
            return fmt::format("[KeyDown] Key: {}, NativeKey: {}, Modifier: {}", key, native_key, modifier);
        }
    };

    class KeyUpEvent : public Event {
        Key key, native_key, modifier;
    public:
        KeyUpEvent(Key key, Key native_key, Key modifier) : key(key), native_key(native_key), modifier(modifier) {}

        EVENT_TYPE(KeyUp);

        std::string toString() const override {
            return fmt::format("[KeyUp] Key: {}, NativeKey: {}, Modifier: {}", key, native_key, modifier);
        }
    };

    class KeyRepeatEvent : public Event {
        Key key, native_key, modifier;
    public:
        KeyRepeatEvent(Key key, Key native_key, Key modifier) : key(key), native_key(native_key), modifier(modifier) {}

        EVENT_TYPE(KeyRepeat);

        std::string toString() const override {
            return fmt::format("[KeyRepeat] Key: {}, NativeKey: {}, Modifier: {}", key, native_key, modifier);
        }
    };
}