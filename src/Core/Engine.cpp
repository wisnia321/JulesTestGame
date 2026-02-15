#include "Engine.h"
#include <iostream>

namespace Jules::Core {

    Engine::Engine() : m_IsRunning(false) {
        Initialize();
    }

    Engine::~Engine() {
        Shutdown();
    }

    void Engine::Initialize() {
        std::cout << "Engine Initializing..." << std::endl;
        m_Window = std::make_unique<Window>(1280, 720, "Project Jules - Dev Build");

        if (m_Window->ShouldClose()) {
            std::cerr << "Window creation failed or immediate close requested." << std::endl;
            m_IsRunning = false;
        } else {
            m_IsRunning = true;
        }
    }

    void Engine::Run() {
        std::cout << "Engine Loop Starting..." << std::endl;
        int frames = 0;
        while (m_IsRunning) {
            if (m_Window->ShouldClose()) {
                m_IsRunning = false;
                break;
            }

            m_Window->PollEvents();
            Update();
            Render();

            frames++;
            if (frames > 100) {
                std::cout << "Auto-shutdown after 100 frames for testing." << std::endl;
                m_IsRunning = false;
            }
        }
        std::cout << "Engine Loop Ended." << std::endl;
    }

    void Engine::Update() {
        // Game logic update
    }

    void Engine::Render() {
        // Render commands
        // m_Window->SwapBuffers(); // Not needed for Vulkan, handled by swapchain
    }

    void Engine::Shutdown() {
        std::cout << "Engine Shutting Down..." << std::endl;
        m_IsRunning = false;
        m_Window.reset(); // Calls Window destructor
    }

}
