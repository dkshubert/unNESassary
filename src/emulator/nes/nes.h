#pragma once

#include <memory>

#include "apu.h"
#include "cpu.h"
#include "ppu.h"
#include "cart.h"
#include "ram.h"
#include "rom.h"

namespace unnes {

class Cart;
class Clock;
class Logger;

class NES {
    double _previousTime{0};
    Logger& _logger;
    Clock _clock;
    CPU _cpu;
    PPU _ppu;
    APU _apu;
    RAM _ram;
    ROM _rom;
    std::unique_ptr<Cart> _cart{nullptr};

   public:
    NES(Logger& logger);

    void insertCart(const std::string_view romPath);
    void run(double time);
};

}  // namespace unnes
