#pragma once

#include "clock.h"

namespace unnes
{

class Logger;
class Cartridge;
class TV;

class PPU : public IClockedDevice
{
    TV& _tv;
    Cartridge* _cartridge;
    Logger& _logger;

public:
    PPU(TV& tv, Logger& logger);
    ~PPU() override = default;

    void connectCartridge(Cartridge* cartridge);
    [[nodiscard]] bool handleClockTick(std::uint64_t tickNum) override;
};

}  // namespace unnes
