#include "Engine.h"
#include <iostream>
#include <exception>

int main(int argc, char** argv) {
    std::cout << "==================================" << std::endl;
    std::cout << "   PrimeFlux Engine v1.0.0" << std::endl;
    std::cout << "   Multi-Language Game Engine" << std::endl;
    std::cout << "==================================" << std::endl;

    try {
        PrimeFlux::Engine engine;

        if (!engine.Initialize()) {
            std::cerr << "[ERROR] Failed to initialize engine" << std::endl;
            return 1;
        }

        engine.Run();
        engine.Shutdown();

        std::cout << "[SUCCESS] Engine exited cleanly" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "[FATAL ERROR] " << e.what() << std::endl;
        return 1;
    }
}
