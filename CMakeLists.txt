cmake_minimum_required(VERSION 3.22)
project(unNESassary)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE src)

find_package(fmt REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    fmt::fmt
    glfw
    OpenGL::OpenGL
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    src
    src/app
    src/emulator
    src/emulator/cartridge
    src/emulator/nes
    src/emulator/nes/apu
    src/emulator/nes/clock
    src/emulator/nes/cpu
    src/emulator/nes/memory
    src/emulator/nes/ppu
    src/emulator/tv
    src/utils
)

if (${CMAKE_COMPILER_IS_GNUCXX})
    target_compile_options(
        ${PROJECT_NAME} PRIVATE
        -pedantic
        -Wall
        -Wextra
        -Wcast-align
        -Wcast-qual
        -Wctor-dtor-privacy
        -Wdisabled-optimization
        -Wformat=2
        -Winit-self
        -Wlogical-op
        -Wmissing-declarations
        -Wmissing-include-dirs
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wshadow
        -Wsign-conversion
        -Wsign-promo
        -Wstrict-null-sentinel
        -Wstrict-overflow=5
        -Wswitch-default
        -Wundef
        -Werror
    )
endif()
