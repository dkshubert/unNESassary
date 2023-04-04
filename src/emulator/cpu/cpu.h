#pragma once

#include "clock.h"

namespace unnes
{

class CPU : public IClockedDevice
{
    Logger& _logger;

public:
    CPU(Logger& logger);
    ~CPU() override = default;

    void handleClockTick(std::uint64_t tickNum) override;

};

} // unnes
