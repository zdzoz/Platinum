//
// Created by Oskar Zdziarski on 7/7/23.
//

#include "Application.h"

#include "Event.h"
#include "WindowEvent.h"

namespace Platinum {

    Application::Application() : _window(std::shared_ptr<Window>(Window::create())), _renderer(std::unique_ptr<Renderer>(Renderer::create(_window))) {
        _window->setEventCallback([this](auto&& e) { onEvent(std::forward<decltype(e)>(e)); });
    }

    Application::Application(WindowProps props) : _window(std::shared_ptr<Window>(Window::create(props))), _renderer(std::unique_ptr<Renderer>(Renderer::create(_window))) {
        _window->setEventCallback([this](auto&& e) { onEvent(std::forward<decltype(e)>(e)); });
    }

    Application::~Application() = default;

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>([&](auto& e) {
            _running = false;
            return true;
        });

//        std::cout << e << std::endl;
    }

    void Application::loop() {
        while (_running) {
            // handle client code on new thread?
            _renderer->draw();
            _window->onUpdate();
        }
    }
}
