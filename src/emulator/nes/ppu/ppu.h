#pragma once

#include "clock.h"

namespace unnes
{

class Logger;
class TV;

class PPU : public IClockedDevice
{
    Logger& _logger;
    TV& _tv;

public:
    PPU(TV& tv, Logger& logger);
    ~PPU() override = default;

    bool handleClockTick(std::uint64_t tickNum) override;
};

}  // namespace unnes
