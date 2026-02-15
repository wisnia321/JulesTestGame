#include <iostream>
#include "Core/Engine.h"

int main() {
    std::cout << "Project Jules Starting..." << std::endl;

    try {
        Jules::Core::Engine engine;
        engine.Run();
    } catch (const std::exception& e) {
        std::cerr << "Unhandled Exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown Exception!" << std::endl;
        return 1;
    }

    std::cout << "Project Jules Terminated." << std::endl;
    return 0;
}
