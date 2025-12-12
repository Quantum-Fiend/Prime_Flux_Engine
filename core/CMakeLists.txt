cmake_minimum_required(VERSION 3.20)
project(PrimeFluxEngine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Options
option(USE_VULKAN "Use Vulkan instead of OpenGL" OFF)
option(ENABLE_HOT_RELOAD "Enable Lua hot-reloading" ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared
)

# Source files
file(GLOB_RECURSE SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

# Create executable
add_executable(PrimeFluxEngine ${SOURCES} ${HEADERS})

# Platform-specific settings
if(WIN32)
    target_compile_definitions(PrimeFluxEngine PRIVATE PLATFORM_WINDOWS)
    target_link_libraries(PrimeFluxEngine PRIVATE ws2_32)
elseif(UNIX)
    target_compile_definitions(PrimeFluxEngine PRIVATE PLATFORM_LINUX)
endif()

# TODO: Link external libraries
# - Lua/LuaJIT
# - Python (pybind11)
# - Rust serialization DLL
# - Graphics API (OpenGL/Vulkan)
# - Physics (Bullet/PhysX)

# Install targets
install(TARGETS PrimeFluxEngine DESTINATION bin)
