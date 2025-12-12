# PrimeFlux Engine Architecture

## Overview

PrimeFlux is a multi-language game engine demonstrating advanced systems programming and cross-language interoperability.

## Architecture Diagram

```mermaid
graph TB
    subgraph "C++ Core Engine"
        Engine[Engine Core]
        ECS[Entity Component System]
        Renderer[Renderer OpenGL/Vulkan]
        Physics[Physics System]
        Telemetry[Telemetry Server]
    end
    
    subgraph "Scripting Layer"
        Lua[Lua Interpreter]
        Scripts[Game Scripts]
    end
    
    subgraph "AI Subsystem"
        Python[Python Runtime]
        BehaviorTree[Behavior Trees]
        Pathfinding[Pathfinding A*]
    end
    
    subgraph "Data Layer"
        Rust[Rust Serialization]
        Serde[Serde + Bincode]
    end
    
    subgraph "Tooling"
        Editor[C# WPF Editor]
        Dashboard[TypeScript Dashboard]
    end
    
    Engine --> ECS
    Engine --> Renderer
    Engine --> Physics
    Engine --> Lua
    Engine --> Python
    Engine --> Rust
    Engine --> Telemetry
    
    Lua --> Scripts
    Python --> BehaviorTree
    Python --> Pathfinding
    Rust --> Serde
    
    Editor -->|TCP/IPC| Engine
    Dashboard -->|WebSocket| Telemetry
    
    style Engine fill:#6366f1
    style Rust fill:#f59e0b
    style Python fill:#10b981
    style Editor fill:#8b5cf6
    style Dashboard fill:#06b6d4
```

## Component Responsibilities

### C++ Core Engine
- **Role**: Host application and runtime orchestrator
- **Responsibilities**:
  - ECS management
  - Rendering pipeline
  - Physics simulation
  - Subsystem coordination
  - Telemetry broadcasting

### Rust Serialization
- **Role**: High-performance data persistence
- **Responsibilities**:
  - Scene serialization/deserialization
  - Asset packaging
  - Zero-copy data loading
  - C ABI for C++ integration

### Lua Scripting
- **Role**: Gameplay logic
- **Responsibilities**:
  - Entity behaviors
  - Game rules
  - Hot-reloadable scripts
  - Event handling

### Python AI
- **Role**: Intelligent agent behaviors
- **Responsibilities**:
  - Behavior tree execution
  - Pathfinding algorithms
  - ML-based decision making
  - NPC controllers

### C# Editor
- **Role**: Content creation tool
- **Responsibilities**:
  - Scene authoring
  - Entity inspection
  - Component editing
  - Asset import

### TypeScript Dashboard
- **Role**: Real-time monitoring
- **Responsibilities**:
  - Performance metrics
  - System telemetry
  - Remote debugging
  - Log aggregation

## Data Flow

1. **Scene Loading**: C++ → Rust (deserialize) → ECS
2. **Gameplay**: ECS → Lua (script execution) → ECS updates
3. **AI Decisions**: ECS → Python (behavior tree) → ECS updates
4. **Rendering**: ECS → Renderer → GPU
5. **Telemetry**: Engine → WebSocket → Dashboard
6. **Editing**: Editor → TCP → Engine (live updates)

## Interop Mechanisms

| From | To | Method |
|------|-----|--------|
| C++ | Rust | C ABI (extern "C") |
| C++ | Lua | Embedded interpreter |
| C++ | Python | pybind11 or C API |
| C++ | Dashboard | WebSocket |
| Editor | C++ | TCP/IPC |

## Performance Considerations

- **Hot Path**: C++ (ECS, Rendering, Physics)
- **Warm Path**: Lua (Gameplay logic)
- **Cold Path**: Python (AI decisions), Rust (Serialization)
- **Async**: Dashboard telemetry, Editor communication

## Future Enhancements

- Multi-threaded job system for ECS
- Vulkan rendering backend
- ML model integration for AI
- Distributed scene editing
- Asset streaming pipeline
