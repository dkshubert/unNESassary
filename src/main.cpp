#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <iostream>

#include "emulator/nes.h"

static void error_callback(int /* error */ , const char* /* description */)
{
    // TODO
}

static void key_callback(GLFWwindow* window,
                         int key,
                         int /* scancode */,
                         int action,
                         int /* mods */)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main()
{
    unnes::NES nes;
    (void) nes;

    // TODO : actually run the NES

    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "unNESassary", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        double x {0};
        double y {0};

        int width {0};
        int height {0};

        double t { glfwGetTime() };

        glfwGetCursorPos(window, &x, &y);

        std::cout << "t: " << t
                  << ", x: " << x
                  << ", y: " << y
                  << std::endl;

        // Get window size (may be different than the requested size)
        glfwGetWindowSize(window, &width, &height);

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

    return -1;
}
