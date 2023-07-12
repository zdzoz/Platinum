//
// Created by Oskar Zdziarski on 7/11/23.
//

#pragma once

namespace Platinum {

    template<typename T>
    struct vec2 {
        union {
            struct {
                T x, y;
            };
            struct {
                T w, h;
            };
        };
        vec2() = default;
        vec2(T x, T y) : x(x), y(y) {}
    };

    class Object {
    protected:
        Object() = default;
        virtual void onLoad() {}
        virtual void onUpdate() {}
        virtual void onDestroy() {}
    public:
        vec2<int> pos{};

        virtual ~Object() = default;
    };

    class Rect : public Object {
    public:
        vec2<int> dim{};
        Rect() = default;
        Rect(int x, int y) : dim({x, y}) {}
    };
}
