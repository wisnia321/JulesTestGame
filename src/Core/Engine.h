#pragma once

#include <memory>
#include "Window.h"

namespace Jules::Core {

    class Engine {
    public:
        Engine();
        ~Engine();

        void Run();

    private:
        void Initialize();
        void Update();
        void Render();
        void Shutdown();

        std::unique_ptr<Window> m_Window;
        bool m_IsRunning;
    };

}
