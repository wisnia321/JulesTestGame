#include "Window.h"
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Jules::Core {

    Window::Window(int width, int height, const std::string& title)
        : m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr) {
        Initialize();
    }

    Window::~Window() {
        Shutdown();
    }

    void Window::Initialize() {
        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_NULL);
        if (!glfwInit()) {
            const char* description;
            int code = glfwGetError(&description);
            std::cerr << "Failed to initialize GLFW! Error " << code << ": " << (description ? description : "Unknown") << std::endl;
            return;
        }

        // Tell GLFW not to create an OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // Disable resizing for now
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
        if (!m_Window) {
            std::cerr << "Failed to create GLFW window! (This is expected in a headless environment)" << std::endl;
            // In a real scenario we might throw or exit, but here we just log
        }
    }

    void Window::Shutdown() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
        }
        glfwTerminate();
    }

    bool Window::ShouldClose() const {
        if (!m_Window) return true; // Close immediately if window creation failed
        return glfwWindowShouldClose(m_Window);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    void Window::SwapBuffers() {
        // Vulkan handles swapchain manually, so this might be empty or used for other purposes
        // but for now we leave it empty.
    }

}
