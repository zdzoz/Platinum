//
// Created by Oskar Zdziarski on 7/7/23.
//

#pragma once

#include <Object.h>
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
        std::vector<std::shared_ptr<Object>> _drawQueue{};
        std::shared_ptr<Window> _window;
    public:
        virtual ~Renderer() = default;
        static Renderer* create(const std::shared_ptr<Window>& win);

        void registerObject(const Object& obj) { _drawQueue.push_back(std::make_shared<Object>(obj)); }

        virtual void draw() = 0;
    };
}