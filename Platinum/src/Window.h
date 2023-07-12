//
// Created by Oskar Zdziarski on 7/9/23.
//

#pragma once

namespace Platinum {
    class Event;
    using EventCallbackFn = std::function<void(Event&)> ;
    struct WindowProps {
        const char* title{};
        int width = 960, height = 480;
    };

    class Window {
    public:

        virtual ~Window() = default;

        // Implement in platform specific window class
        static Window* create(const WindowProps& props = WindowProps());

        virtual inline const std::string& title() = 0;
        virtual inline int width() = 0;
        virtual inline int height() = 0;

        virtual void* getNativeWindow() = 0;

        virtual void onUpdate() = 0;

        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
    };
}