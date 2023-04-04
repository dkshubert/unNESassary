#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>

#include "nes.h"
#include "stdoutlogger.h"

static void error_callback(int /* error */, const char* /* description */) {
    // TODO
}

static void key_callback(GLFWwindow* window, int key, int /* scancode */, int action,
                         int /* mods */) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main() {
    unnes::StdOutLogger logger;
    unnes::NES nes(logger);

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window{glfwCreateWindow(1024, 768, "unNESassary", nullptr, nullptr)};
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        const double time{glfwGetTime()};
        nes.run(time);

        double x{0};
        double y{0};
        glfwGetCursorPos(window, &x, &y);

        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(0.f + x / 2000, 0.5f - y / 2000);
        glColor3f(0.f, 1.f, 0.f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
