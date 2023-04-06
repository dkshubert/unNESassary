#include "application.h"

#include <fmt/core.h>

#include "stdoutlogger.h"
#include "time_utils.h"

namespace unnes
{

Application::Application(ApplicationConfig config)
    : _config(config),
      // TODO: choose the type of logger to construct based on the application config, via some
      // logger factory function.
      _logger(std::make_unique<StdOutLogger>(_config._logLevel)),
      _nes(*_logger),
      _tv(config._tvConfig, *_logger)
{
    glfwInit();

    // Needs to be called after glfwInit().
    _window =
        glfwCreateWindow(_config._tvConfig._windowWidthPixels,
                         _config._tvConfig._windowHeightPixels, "unNESassary", nullptr, nullptr);

    glfwSetWindowUserPointer(_window, this);
    glfwMakeContextCurrent(_window);
    glfwSetKeyCallback(_window, _handleKeypress);

    _tv.setWindow(_window);
}

Application::~Application()
{
    _nes.ejectCart();
    glfwSetWindowShouldClose(_window, GL_TRUE);
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Application::handleKeypress(int key, int scancode, int action, int mods)
{
    _logger->write(LogLevel::info,
                   fmt::format("Key Pressed ({}), scancode ({}), action ({}), mods ({})", key,
                               scancode, action, mods));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        _shutdownRequested = true;
    }
}

void Application::_handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (auto thisPtr = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window))) {
        thisPtr->handleKeypress(key, scancode, action, mods);
    }
}

bool Application::run()
{
    if (!_window) {
        _logger->write(LogLevel::error, fmt::format("Failed to create an application window."));

        return false;
    }

    if (!_nes.insertCart(_config._lastPlayedRomPath)) {
        _logger->write(LogLevel::error, fmt::format("Failed to insert cartridge."));

        return false;
    }

    while (!_shutdownRequested) {
        const double time { unnes::getTime() };

        for (auto& device : _devices) {
            if (!device->update(time)) {
                return false;
            }
        }

        glfwGetCursorPos(_window, &_cursorX, &_cursorY);
        glfwPollEvents();
    }

    return true;
}

}  // namespace unnes
