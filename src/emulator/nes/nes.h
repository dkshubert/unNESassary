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

class Clock;
class Logger;

/// @brief The NES emulator! This class contains all NES hardware components,
class NES
{
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

    /// @brief Inserts a cartridge into the NES.
    ///
    /// @param romPath The path the ".nes" ROM in the filesystem.
    /// @return True if the cart was successfully inserted (the ROM loaded), false otherwise.
    [[nodiscard]] bool insertCart(const std::string_view romPath);
    void ejectCart();

    /// @brief Runs the NES emulator, emulating as much as neccessary since the last call to run.
    ///
    /// @param time The time since boot (in seconds).
    /// @return True if this time slice has been successfully emulated, false otherwise.
    [[nodiscard]] bool run(double time);
};

}  // namespace unnes
