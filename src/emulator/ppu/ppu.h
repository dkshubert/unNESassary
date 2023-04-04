#pragma once

#include "clock.h"

namespace unnes
{

class Logger;

class PPU : public IClockedDevice
{
    Logger& _logger;

public:
    PPU(Logger& logger);
    ~PPU() override = default;

    void handleClockTick() override;

};

} // unnes
