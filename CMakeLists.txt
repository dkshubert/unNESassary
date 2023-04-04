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
    src/emulator/nes/apu/apu.cpp
    src/emulator/nes/clock/clock.cpp
    src/emulator/nes/cpu/cpu.cpp
    src/emulator/nes/memory/ram.cpp
    src/emulator/nes/memory/rom.cpp
    src/emulator/nes/nes.cpp
    src/emulator/nes/ppu/ppu.cpp
    src/utils/logger.cxx
    src/utils/stdoutlogger.cpp
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    src
    src/emulator
    src/emulator/nes
    src/emulator/nes/apu
    src/emulator/nes/clock
    src/emulator/nes/cpu
    src/emulator/nes/memory
    src/emulator/nes/ppu
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
