#pragma once

#include "clock.h"
#include "registers.h"

namespace unnes
{

class Cartridge;
class Logger;

/// @brief The NES uses a modified 6502, an 8-bit processor with a 16-bit address bus.
class CPU : public IClockedDevice
{
    Logger& _logger;
    Cartridge* _cartridge;
    Registers _registers;

public:
    CPU(Logger& logger);
    ~CPU() override = default;

    void connectCartridge(Cartridge* cartridge);
    [[nodiscard]] bool handleClockTick(std::uint64_t tickNum) override;
};

}  // namespace unnes
