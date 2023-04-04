cmake_minimum_required(VERSION 3.22)
project(unNESassary)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/emulator/apu/apu.cpp
    src/emulator/clock/clock.cpp
    src/emulator/cpu/cpu.cpp
    src/emulator/memory/ram.cpp
    src/emulator/memory/rom.cpp
    src/emulator/nes.cpp
    src/emulator/ppu/ppu.cpp
    src/utils/logger.cxx
    src/utils/stdoutlogger.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    src/emulator
    src/emulator/apu
    src/emulator/clock
    src/emulator/cpu
    src/emulator/memory
    src/emulator/ppu
    src/utils
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    fmt::fmt
    glfw
    OpenGL::OpenGL
    OpenGL::GLU
)
