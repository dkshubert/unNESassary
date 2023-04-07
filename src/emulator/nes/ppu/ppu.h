#pragma once

#include "clock.h"

namespace unnes
{

class Logger;
class TV;

class PPU : public IClockedDevice
{
    TV& _tv;
    Logger& _logger;

public:
    PPU(TV& tv, Logger& logger);
    ~PPU() override = default;

    bool handleClockTick(std::uint64_t tickNum) override;
};

}  // namespace unnes
