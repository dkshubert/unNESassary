#pragma once

#include "apu.h"
#include "clock.h"
#include "cpu.h"
#include "ppu.h"
#include "ram.h"
#include "rom.h"

namespace unnes
{

class NES
{
    double _previousTime { 0 };
    Clock _clock {};
    CPU _cpu {};
    PPU _ppu {};
    APU _apu {};
    RAM _ram {};
    ROM _rom {};

public:
    NES();

    void run(double time);
};

} // namespace unnes
