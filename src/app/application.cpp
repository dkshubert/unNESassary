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
}

Application::~Application() { _nes.ejectCart(); }

bool Application::run()
{
    if (!_nes.insertCart(_config._lastPlayedRomPath)) {
        _logger->write(LogLevel::error, fmt::format("Failed to insert cartridge."));

        return false;
    }

    while (!_closeRequested) {
        const double time { unnes::getTime() };

        for (auto& device : _devices) {
            if (device->isOn() && !device->update(time)) {
                return false;
            }
        }
    }

    return true;
}

}  // namespace unnes
