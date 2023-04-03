#pragma once

#include "apu/apu.h"
#include "cpu/cpu.h"
#include "ppu/ppu.h"
#include "memory/ram.h"
#include "memory/rom.h"

namespace unnes
{

class NES
{
    CPU _cpu;
    PPU _ppu;
    APU _apu;
    RAM _ram;
    ROM _rom;

public:
};

} // namespace unnes
