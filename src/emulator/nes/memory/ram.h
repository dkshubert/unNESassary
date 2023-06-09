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

    [[nodiscard]] bool handleClockTick(std::uint64_t tickNum) override;
};

}  // namespace unnes
