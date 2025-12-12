# PrimeFlux Engine - Build Instructions

## Prerequisites

Ensure you have the following installed:

### Required
- **CMake** 3.20 or higher
- **C++ Compiler**:
  - Windows: MSVC 2019+ (Visual Studio)
  - Linux: GCC 9+ or Clang 10+
- **Rust** 1.70+ with Cargo
- **Python** 3.9+
- **.NET SDK** 6.0+
- **Node.js** 18+ with npm

### Optional
- **Lua** 5.4 or LuaJIT (for scripting)
- **OpenGL** or **Vulkan** SDK (for rendering)

---

## Building the Project

### 1. Build Rust Serialization Module

```bash
cd serialization
cargo build --release
```

This creates `primeflux_serialization.dll` (Windows) or `.so` (Linux) in `target/release/`.

### 2. Build C++ Core Engine

```bash
cd core
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable will be in `core/build/bin/PrimeFluxEngine.exe`.

### 3. Setup Python AI Module

```bash
cd ai
pip install -r requirements.txt  # If you create one
python behavior_tree.py  # Test the module
```

### 4. Build C# Level Editor

```bash
cd editor
dotnet restore
dotnet build --configuration Release
```

Run with:
```bash
dotnet run
```

### 5. Build TypeScript Dashboard

```bash
cd dashboard
npm install
npm run dev
```

Access at `http://localhost:3000`.

---

## Running the Engine

1. **Start the C++ Core Engine**:
   ```bash
   cd core/build/bin
   ./PrimeFluxEngine
   ```

2. **Launch the Dashboard** (in a separate terminal):
   ```bash
   cd dashboard
   npm run dev
   ```

3. **Open the Level Editor** (optional):
   ```bash
   cd editor
   dotnet run
   ```

---

## Project Structure

```
PrimeFlux Engine/
├── core/              # C++ Engine (CMake)
│   ├── include/       # Headers
│   ├── src/           # Source files
│   └── CMakeLists.txt
├── serialization/     # Rust library
│   ├── src/lib.rs
│   └── Cargo.toml
├── scripting/         # Lua scripts
│   └── example_script.lua
├── ai/                # Python AI
│   ├── __init__.py
│   └── behavior_tree.py
├── editor/            # C# WPF Editor
│   ├── App.xaml
│   ├── MainWindow.xaml
│   └── PrimeFluxEditor.csproj
├── dashboard/         # TypeScript Dashboard
│   ├── src/
│   ├── package.json
│   └── vite.config.ts
└── shared/            # Shared headers/schemas
    └── RustSerialization.h
```

---

## Troubleshooting

### Rust DLL not found
Ensure `primeflux_serialization.dll` is in the same directory as the C++ executable or in your system PATH.

### Python module errors
Make sure Python is in your PATH and the `ai` directory is accessible.

### Dashboard won't connect
The WebSocket connection is currently a placeholder. Full integration requires implementing the WebSocket server in the C++ engine.

---

## Next Steps

- Integrate Lua interpreter (LuaJIT) into C++ engine
- Implement actual rendering (OpenGL/Vulkan)
- Add physics engine (Bullet/PhysX)
- Complete WebSocket telemetry bridge
- Implement hot-reload for Lua scripts
