#pragma once

#include <memory>

#include "apu.h"
#include "cartridge.h"
#include "cpu.h"
#include "ppu.h"
#include "ram.h"
#include "rom.h"

namespace unnes
{

class Cartridge;
class Clock;
class Logger;

class NES
{
    double _previousTime { 0 };
    Logger& _logger;
    Clock _clock;
    CPU _cpu;
    PPU _ppu;
    APU _apu;
    RAM _ram;
    ROM _rom;
    std::unique_ptr<Cartridge> _cartridge { nullptr };

public:
    NES(Logger& logger);

    void insertCart(const std::string_view romPath);
    void run(double time);
};

}  // namespace unnes
