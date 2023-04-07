#include "window.h"

#include <GLFW/glfw3.h>
#include <fmt/core.h>

#include "application.h"

namespace unnes
{

static void resizeCallback(GLFWwindow* window, int width, int height) {
    if (auto applicationPtr = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window))) {
        applicationPtr->getWindow().handleResize(width, height);
    }
}

Window::Window(Application& application)
    : _application(application)
    , _logger(_application.getLogger())
    , _currentWidth(_application.getConfig()._tvConfig._windowWidthPixels)
    , _currentHeight(_application.getConfig()._tvConfig._windowHeightPixels)
{
    glfwInit();

    // Needs to be called after glfwInit().
    _window =
        glfwCreateWindow(_application.getConfig()._tvConfig._windowWidthPixels,
                         _application.getConfig()._tvConfig._windowHeightPixels, "unNESassary", nullptr, nullptr);

    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, &_application);
    glfwSetWindowSizeCallback(_window, resizeCallback);
}

Window::~Window()
{
    glfwSetWindowShouldClose(_window, GL_TRUE);
    glfwDestroyWindow(_window);
    glfwTerminate();
}

GLFWwindow* Window::getGlfwWindow()
{
    return _window;
}

int Window::getWidth() const
{
    return _currentWidth;
}

int Window::getHeight() const
{
    return _currentHeight;
}

void Window::handleResize(int width, int height)
{
    _logger.write(LogLevel::info, fmt::format("Window resized: width: {}, height: {}", width, height));
    _currentWidth = width;
    _currentHeight = height;
}

bool Window::update()
{
    if (!_window) {
        return false;
    }

    glfwPollEvents();
    return !glfwWindowShouldClose(_window);
}

}  // namespace unnes
