//
// Created by Oskar Zdziarski on 7/9/23.
//

#pragma once

namespace Platinum {
    class Event;
    using EventCallbackFn = std::function<void(Event&)>;
    struct WindowProps {
        const char* title{"Platinum App"};
        int width{800}, height{600};
        bool resizable{true};
    };

    class Window {
    public:

        virtual ~Window() = default;

        // Implement in platform specific window class
        static Window* create(const WindowProps& props = {});

        virtual inline const std::string& title() = 0;
        virtual inline int width() = 0;
        virtual inline int height() = 0;

        virtual void* getNativeWindow() = 0;
        virtual void setResizable(bool resizable) = 0;

        virtual void onUpdate() = 0;

        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
    };
}
