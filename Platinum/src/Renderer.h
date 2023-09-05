//
// Created by Oskar Zdziarski on 7/7/23.
//

#pragma once

#include <Window.h>

#ifdef LIB_PATH
#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)
#define SHADER_DIRECTORY STRINGIFY(LIB_PATH)
#else
#define SHADER_DIRECTORY ""
#endif

namespace Platinum {
    class Renderer {
//        friend Window;
    protected:
        std::shared_ptr<Window> _window;
    public:
        virtual ~Renderer() = default;
        static Renderer* create(const std::shared_ptr<Window>& win);

        virtual void draw() = 0;
    };
}