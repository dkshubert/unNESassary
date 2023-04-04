#pragma once

#include "clock.h"

namespace unnes
{

class Logger;

class RAM : public IClockedDevice
{
    Logger& _logger;

public:
    RAM(Logger& logger);
    ~RAM() override = default;

    void handleClockTick() override;

};

} // unnes
