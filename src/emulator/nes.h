#pragma once

#include "apu.h"
#include "cpu.h"
#include "ppu.h"
#include "ram.h"
#include "rom.h"

namespace unnes
{

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

public:
    NES(Logger& logger);

    void run(double time);
};

} // namespace unnes
