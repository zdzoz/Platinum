//
// Created by Oskar Zdziarski on 7/9/23.
//

#pragma once

#include "Window.h"

#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Platinum {
    class MetalWindow : public Window {
        static bool GLFWInitialized;
        GLFWwindow* win;
        NSWindow* nswin;

        struct WindowData {
            std::string title;
            int width, height;
            bool resizable;
            EventCallbackFn EventCallback;
        } _data;

    public:
        MetalWindow(const WindowProps& props);
        ~MetalWindow() override;

        virtual inline const std::string& title() override { return _data.title; }
        inline int width() override { return _data.width; }
        inline int height() override { return _data.height; }

        inline void* getNativeWindow() override { return nswin; }
        void setResizable(bool resizable) override { glfwWindowHint(GLFW_RESIZABLE, resizable); }

        void onUpdate() override;

        inline void setEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }
    };
}