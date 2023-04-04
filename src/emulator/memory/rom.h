#pragma once

#include "clock.h"

namespace unnes
{

class Logger;

class ROM : public IClockedDevice
{
    Logger& _logger;

public:
    ROM(Logger& logger);
    ~ROM() override = default;

    void handleClockTick() override;

};

} // unnes
