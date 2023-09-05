//
// Created by Oskar Zdziarski on 7/9/23.
//

#include "MetalWindow.h"

#include "Event.h"
#include "WindowEvent.h"
#include "MouseEvents.h"
#include "KeyEvent.h"

namespace Platinum {

    bool MetalWindow::GLFWInitialized = false;

    Window* Window::create(const WindowProps& props) {
        return new MetalWindow(props);
    }

    MetalWindow::MetalWindow(const WindowProps& props) {
        _data.title = props.title;
        _data.width = props.width;
        _data.height = props.height;
        _data.resizable = props.resizable;
        if (!GLFWInitialized) {
            if (!glfwInit()) {
                std::cerr << "Failed to Initialise Window\n";
                exit(1);
            }
            GLFWInitialized = true;
        }

        glfwWindowHint(GLFW_RESIZABLE, props.resizable);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // prevent using OpenGL
        win = glfwCreateWindow(_data.width, _data.height, _data.title.c_str(), nullptr, nullptr);
        if (win == nullptr) {
            std::cerr << "Failed to create Window\n";
            exit(1);
        }
        nswin = glfwGetCocoaWindow(win);

        id<MTLDevice> device = MTLCreateSystemDefaultDevice();
        CAMetalLayer* swapchain = [CAMetalLayer layer];

        swapchain.device = device;
        nswin.contentView.layer = swapchain;
        nswin.contentView.wantsLayer = YES;

        // setup callbacks
        glfwSetWindowUserPointer(win, &_data);

        glfwSetWindowCloseCallback(win, [](GLFWwindow* _win) {
            auto data = (WindowData*)glfwGetWindowUserPointer(_win);
            WindowCloseEvent e;
            data->EventCallback(e);
        });

        glfwSetWindowSizeCallback(win, [](GLFWwindow* _win, int width, int height) {
            auto data = (WindowData*)glfwGetWindowUserPointer(_win);
            data->width = width;
            data->height = height;

            WindowResizeEvent e(width, height);
            data->EventCallback(e);
        });

        glfwSetCursorPosCallback(win, [](GLFWwindow* _win, double x, double y) {
            auto data = (WindowData*)glfwGetWindowUserPointer(_win);

            MousePosEvent e(x, y);
            data->EventCallback(e);
        });

        glfwSetMouseButtonCallback(win, [](GLFWwindow* _win, int button, int action, int mods) {
            auto data = (WindowData*)glfwGetWindowUserPointer(_win);

            if (action) {
                MouseDownEvent e(static_cast<MB>(button), static_cast<Key>(mods));
                data->EventCallback(e);
            } else {
                MouseUpEvent e(static_cast<MB>(button), static_cast<Key>(mods));
                data->EventCallback(e);
            }
        });

        glfwSetKeyCallback(win, [](GLFWwindow* _win, int key, int code, int action, int mod) {
            auto data = (WindowData*)glfwGetWindowUserPointer(_win);

            switch (action) {
                case KeyAction::Up: {
                    KeyUpEvent e(key, code, mod);
                    data->EventCallback(e);
                } break;
                case KeyAction::Down: {
                    KeyDownEvent e(key, code, mod);
                    data->EventCallback(e);
                } break;
                case KeyAction::Repeat:
                default:
                    KeyRepeatEvent e(key, code, mod);
                    data->EventCallback(e);
            }
        });
    }

    MetalWindow::~MetalWindow() {
        // TODO: glfwTerminate
        glfwDestroyWindow(win);
    }

    void MetalWindow::onUpdate() {
        glfwPollEvents();
    }
}
