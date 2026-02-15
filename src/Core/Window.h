#pragma once

#include <string>

struct GLFWwindow;

namespace Jules::Core {

    class Window {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool ShouldClose() const;
        void PollEvents();
        void SwapBuffers(); // Though with Vulkan we manage swapchain ourselves, let's keep it generic for now or just useful for GLFW context management if needed.

        // Getters
        GLFWwindow* GetNativeWindow() const { return m_Window; }
        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

    private:
        void Initialize();
        void Shutdown();

        int m_Width;
        int m_Height;
        std::string m_Title;
        GLFWwindow* m_Window;
    };

}
