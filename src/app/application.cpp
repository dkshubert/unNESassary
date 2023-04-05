#include "application.h"

#include "time_utils.h"

namespace unnes
{

Application::Application(ApplicationConfig config)
    : _config(config),
      _logger(_config._logLevel),
      _nes(_logger),
      _tv(config._tvConfig, _logger)
{
    _nes.insertCart(_config._lastPlayedRomPath);
}

Application::~Application() { _nes.ejectCart(); }

void Application::run()
{
    while (_tv.isOn()) {
        const double time { unnes::getTime() };
        _nes.run(time);
        _tv.run(time);
    }
}

}  // namespace unnes
