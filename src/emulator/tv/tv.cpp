#include "tv.h"

#include <GLFW/glfw3.h>

#include "logger.h"

namespace unnes {

TV::TV(Logger& logger) : _logger(logger) {
    glfwInit();

    _window = glfwCreateWindow(1024, 768, "unNESassary", nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(_window);
    // glfwSetKeyCallback(_window, key_callback);
}

TV::~TV() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool TV::isOn() const { return !glfwWindowShouldClose(_window); }

void TV::run(double /* time */) {
    double x{0};
    double y{0};

    glfwGetCursorPos(_window, &x, &y);

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a test image a this point in the project. Later on we'll obviously really draw an image
    // obtained from the NES.
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(0.f + x / 2000, 0.5f - y / 2000);
    glColor3f(0.f, 1.f, 0.f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    // Swap buffers
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

}  // namespace unnes
