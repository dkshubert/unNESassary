#include "application.h"

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
      _tv(config._tvConfig, *_logger),
      _window(_config, _tv, _inputHandler)
{
    _inputHandler.registerCallback(     //
        GLFW_KEY_ESCAPE,                //
        [this](ButtonState) {           //
            _shutdownRequested = true;  //
        }                               //
    );                                  //
}

Application::~Application() { _nes.ejectCart(); }

int Application::run()
{
    if (!_nes.insertCart(_config._lastPlayedRomPath)) {
        _logger->write(LogLevel::error, "Failed to insert cartridge.");

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
                _logger->write(LogLevel::error,
                               "Emulated device failed to update. Exiting main loop.");
                _shutdownRequested = true;
            }
        }

        _inputHandler.update();

        if (!_window.update()) {
            _logger->write(LogLevel::error, "The window has closed.");
            _shutdownRequested = true;
        }
    }

    return true;
}

}  // namespace unnes
