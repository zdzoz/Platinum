//
// Created by Oskar Zdziarski on 7/7/23.
//

#pragma once

#include "Window.h"
#include "Renderer.h"

namespace Platinum {
    using ApplicationInfo = WindowProps;
    class Application {
        std::shared_ptr<Window> _window;
        std::unique_ptr<Renderer> _renderer;
        ApplicationInfo appInfo{};
        bool _running{true};
    public:
        Application(const ApplicationInfo& info = {}) : appInfo(info) {};

        virtual ~Application();

        virtual void onEvent(Event& e);

        void run();
    };
}
