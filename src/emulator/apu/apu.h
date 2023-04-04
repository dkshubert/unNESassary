#pragma once

#include "clock.h"

namespace unnes
{

class Logger;

class APU : public IClockedDevice
{
    Logger& _logger;

public:
    APU(Logger& logger);
    ~APU() override = default;

    void handleClockTick(std::uint64_t tickNum) override;
};

} // unnes
