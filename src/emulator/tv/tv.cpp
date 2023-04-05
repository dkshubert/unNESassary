#include "tv.h"

#include <GLFW/glfw3.h>

#include "logger.h"

namespace unnes
{

TV::TV(TvConfig tvConfig, Logger& logger)
    : _tvConfig(tvConfig),
      _logger(logger)
{
    glfwInit();

    _window = glfwCreateWindow(_tvConfig._widthPixels, _tvConfig._heightPixels, "unNESassary",
                               nullptr, nullptr);
    if (!_window) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(_window);
    // glfwSetKeyCallback(_window, key_callback);
}

TV::~TV()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool TV::update(double /* time */)
{
    double x { 0 };
    double y { 0 };

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

    return true;
}

void TV::turnOn()
{
    // no-op
}

void TV::turnOff()
{
    // no-op
}

bool TV::isOn() const { return !glfwWindowShouldClose(_window); }

}  // namespace unnes
