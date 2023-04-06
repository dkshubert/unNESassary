#include "nes.h"

#include <fmt/core.h>

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

bool NES::update(double time) { return _clock.run(time); }

bool NES::insertCart(const std::string_view romPath)
{
    _cartridge = std::make_unique<Cartridge>(_logger);
    return _cartridge->load(romPath);
}

void NES::ejectCart() { _cartridge.release(); }

}  // namespace unnes
