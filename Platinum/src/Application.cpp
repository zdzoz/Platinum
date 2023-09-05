//
// Created by Oskar Zdziarski on 7/7/23.
//

#include "Application.h"

#include "Event.h"
#include "WindowEvent.h"
#include "KeyEvent.h"

namespace Platinum {

    Application::~Application() = default;

    void Application::onEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>([&](auto& e) {
            _running = false;
            return true;
        });

//        dispatcher.dispatch<KeyDownEvent>([] (auto& e) {
//            std::cout << e.toString()  << std::endl;
//            return true;
//        });
//
//        dispatcher.dispatch<KeyUpEvent>([] (auto& e) {
//            std::cout << e.toString()  << std::endl;
//            return true;
//        });
//
//        dispatcher.dispatch<KeyRepeatEvent>([] (auto& e) {
//            std::cout << e.toString()  << std::endl;
//            return true;
//        });
    }

    void Application::run() {
        _window = std::shared_ptr<Window>(Window::create(appInfo));
        _renderer = std::unique_ptr<Renderer>(Renderer::create(_window));
        _window->setEventCallback([this](auto&& e) { onEvent(std::forward<decltype(e)>(e)); });
        while (_running) {
            // handle client code on new thread?
            _renderer->draw();
            _window->onUpdate();
        }
    }
}
