#include "application.h"

#include <fmt/core.h>
#include <GLFW/glfw3.h>

#include "stdout_logger.h"
#include "time_utils.h"

namespace unnes
{

Application::Application(ApplicationConfig config)
    : _config(config),
      // TODO: choose the type of logger to construct based on the application config, via some
      // logger factory function.
      _logger(std::make_unique<stdout_logger>(_config._logLevel)),
      _inputHandler(*_logger),
      _nes(*_logger),
      _tv(config._tvConfig, *_logger)
{
    glfwInit();

    // Needs to be called after glfwInit().
    _window =
        glfwCreateWindow(_config._tvConfig._windowWidthPixels,
                         _config._tvConfig._windowHeightPixels, "unNESassary", nullptr, nullptr);

    glfwMakeContextCurrent(_window);

    _tv.setWindow(_window);
    _inputHandler.setWindow(_window);
    _inputHandler.registerCallback(     //
        GLFW_KEY_ESCAPE,                //
        [this](ButtonState) {           //
            _shutdownRequested = true;  //
        }                               //
    );                                  //
}

Application::~Application()
{
    _nes.ejectCart();
    glfwSetWindowShouldClose(_window, GL_TRUE);
    glfwDestroyWindow(_window);
    glfwTerminate();
}

int Application::run()
{
    if (!_window) {
        _logger->write(LogLevel::error, fmt::format("Failed to create an application window."));

        return kExitFailure;
    }

    if (!_nes.insertCart(_config._lastPlayedRomPath)) {
        _logger->write(LogLevel::error, fmt::format("Failed to insert cartridge."));

        return kExitFailure;
    }

    return runMainLoop() ? kExitSuccess : kExitFailure;  // blocks until app shutdown
}

bool Application::runMainLoop()
{
    while (!_shutdownRequested) {
        const double time { unnes::getTime() };

        for (auto& device : _devices) {
            if (!device->update(time)) {
                return false;
            }
        }

        _inputHandler.update();

        glfwPollEvents();
    }

    return true;
}

}  // namespace unnes
