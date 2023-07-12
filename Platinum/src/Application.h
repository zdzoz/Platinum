//
// Created by Oskar Zdziarski on 7/7/23.
//

#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Object.h"

namespace Platinum {
    class Application {
        std::shared_ptr<Window> _window;
        std::unique_ptr<Renderer> _renderer;
        bool _running = true;
    public:
        Application();
        Application(WindowProps props);
        virtual ~Application();

        void addDrawable(const Object& obj) { _renderer->registerObject(obj); };

        virtual void onEvent(Event& e);
        virtual void loop();
    };

    Application* createApp();
}