#include "nes.h"

#include <fmt/core.h>

#include "cartridge/cartridge.h"
#include "clock.h"
#include "logger.h"
#include "tv.h"

namespace unnes
{

NES::NES(TV& tv, Logger& logger)
    : _logger(logger),
      _clock(_logger),
      _cpu(_logger),
      _ppu(tv, _logger),
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
    if (!_cartridge->load(romPath)) {
        return false;
    }

    _ppu.connectCartridge(_cartridge.get());

    return true;
}

void NES::ejectCart() { _cartridge.reset(); }

}  // namespace unnes
