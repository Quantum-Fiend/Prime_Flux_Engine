#include "Engine.h"
#include "ECS.h"
#include <iostream>
#include <chrono>

namespace PrimeFlux {

Engine::Engine() 
    : m_isRunning(false)
    , m_deltaTime(0.0f)
    , m_fixedTimeStep(1.0f / 60.0f)
{
}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Initialize() {
    std::cout << "[PrimeFlux] Initializing engine..." << std::endl;

    // Initialize ECS
    m_ecs = std::make_unique<ECS>();
    std::cout << "[PrimeFlux] ECS initialized" << std::endl;

    // TODO: Initialize other subsystems
    // m_renderer = std::make_unique<Renderer>();
    // m_physics = std::make_unique<Physics>();
    // m_scriptEngine = std::make_unique<ScriptEngine>();
    // m_telemetry = std::make_unique<Telemetry>();

    m_isRunning = true;
    std::cout << "[PrimeFlux] Engine initialized successfully" << std::endl;
    return true;
}

void Engine::Run() {
    std::cout << "[PrimeFlux] Starting main loop..." << std::endl;

    auto lastTime = std::chrono::high_resolution_clock::now();
    float accumulator = 0.0f;

    while (m_isRunning) {
        // Calculate delta time
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = currentTime - lastTime;
        lastTime = currentTime;
        m_deltaTime = elapsed.count();

        // Cap delta time to prevent spiral of death
        if (m_deltaTime > 0.25f) {
            m_deltaTime = 0.25f;
        }

        accumulator += m_deltaTime;

        // Fixed update loop (physics, etc.)
        while (accumulator >= m_fixedTimeStep) {
            FixedUpdate();
            accumulator -= m_fixedTimeStep;
        }

        // Variable update (rendering, input, etc.)
        Update();

        // Simple exit condition for now
        static int frameCount = 0;
        if (++frameCount > 100) {
            m_isRunning = false;
        }
    }

    std::cout << "[PrimeFlux] Main loop ended" << std::endl;
}

void Engine::Update() {
    // Update ECS systems
    if (m_ecs) {
        m_ecs->Update(m_deltaTime);
    }

    // TODO: Update other subsystems
    // if (m_scriptEngine) m_scriptEngine->Update(m_deltaTime);
    // if (m_renderer) m_renderer->Render();
    // if (m_telemetry) m_telemetry->SendMetrics();
}

void Engine::FixedUpdate() {
    // TODO: Fixed timestep updates (physics)
    // if (m_physics) m_physics->Step(m_fixedTimeStep);
}

void Engine::Shutdown() {
    if (!m_isRunning) return;

    std::cout << "[PrimeFlux] Shutting down engine..." << std::endl;
    
    m_isRunning = false;
    
    // Cleanup subsystems in reverse order
    m_telemetry.reset();
    m_scriptEngine.reset();
    m_physics.reset();
    m_renderer.reset();
    m_ecs.reset();

    std::cout << "[PrimeFlux] Engine shutdown complete" << std::endl;
}

} // namespace PrimeFlux
