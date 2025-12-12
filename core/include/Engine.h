#pragma once

#include <memory>
#include <string>

namespace PrimeFlux {

/**
 * @brief Main Engine class - orchestrates all subsystems
 */
class Engine {
public:
    Engine();
    ~Engine();

    // Core lifecycle
    bool Initialize();
    void Run();
    void Shutdown();

    // Subsystem access
    class ECS* GetECS() const { return m_ecs.get(); }
    class Renderer* GetRenderer() const { return m_renderer.get(); }
    class Physics* GetPhysics() const { return m_physics.get(); }
    class ScriptEngine* GetScriptEngine() const { return m_scriptEngine.get(); }

    // Engine state
    bool IsRunning() const { return m_isRunning; }
    float GetDeltaTime() const { return m_deltaTime; }

private:
    void Update();
    void FixedUpdate();

    std::unique_ptr<class ECS> m_ecs;
    std::unique_ptr<class Renderer> m_renderer;
    std::unique_ptr<class Physics> m_physics;
    std::unique_ptr<class ScriptEngine> m_scriptEngine;
    std::unique_ptr<class Telemetry> m_telemetry;

    bool m_isRunning;
    float m_deltaTime;
    float m_fixedTimeStep;
};

} // namespace PrimeFlux
