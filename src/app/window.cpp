#include "window.h"

#include <GLFW/glfw3.h>

#include "application_config.h"
#include "input_handler.h"
#include "tv.h"

namespace unnes
{

Window::Window(ApplicationConfig& config, TV& tv, InputHandler& inputHandler)
    : _config(config),
      _tv(tv),
      _inputHandler(inputHandler)
{
    glfwInit();

    // Needs to be called after glfwInit().
    _window =
        glfwCreateWindow(_config._tvConfig._windowWidthPixels,
                         _config._tvConfig._windowHeightPixels, "unNESassary", nullptr, nullptr);

    glfwMakeContextCurrent(_window);

    _tv.setWindow(_window);
    _inputHandler.setWindow(_window);
}

Window::~Window()
{
    glfwSetWindowShouldClose(_window, GL_TRUE);
    glfwDestroyWindow(_window);
    glfwTerminate();
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
