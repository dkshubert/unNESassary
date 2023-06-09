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

    [[nodiscard]] bool handleClockTick(std::uint64_t tickNum) override;
};

}  // namespace unnes
