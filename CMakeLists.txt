cmake_minimum_required(VERSION 3.15)
project(unNESassary)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::OpenGL
    OpenGL::GLU
)
