#include "nes.h"

#include <fmt/core.h>

#include <cstdint>

#include "cartridge/cartridge.h"
#include "clock.h"
#include "logger.h"

namespace unnes
{

NES::NES(Logger& logger)
    : _logger(logger),
      _clock(_logger),
      _cpu(_logger),
      _ppu(_logger),
      _apu(_logger),
      _ram(_logger),
      _rom(_logger)
{
    const std::vector<IClockedDevice*> devices { &_cpu, &_ppu, &_apu, &_ram, &_rom };

    _clock.connect(devices);
}

void NES::run(double time)
{
    const double timeDelta { time - _previousTime };

    // Note : some kind of narrowing conversion here is desired, though the rounding used here
    // almost certainly results in less fidelitous clock timing, which means this approach for
    // determining the # of cycles to execute since the last run might need to be revised when this
    // project is further along. This will probably work reasonably well for the time being, though.
    const std::uint32_t numCyclesToRun = _clock.getSpeedHz() * timeDelta;

    _logger.write(LogLevel::trace,                                                   //
                  fmt::format("time: {}, previous time: {}, num cycles to run: {}",  //
                              time,                                                  //
                              _previousTime,                                         //
                              numCyclesToRun));

    for (std::uint32_t i { 0 }; i < numCyclesToRun; i++) {
        _clock.tick();
    }

    _previousTime = time;
}

void NES::insertCart(const std::string_view romPath)
{
    _cartridge = std::make_unique<Cartridge>(_logger, romPath);
}

}  // namespace unnes
