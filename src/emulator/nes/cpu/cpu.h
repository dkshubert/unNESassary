#pragma once

#include "clock.h"

namespace unnes
{

/// @brief The NES uses a modified 6502, an 8-bit processor with a 16-bit address bus.
class CPU : public IClockedDevice
{
    Logger& _logger;

public:
    CPU(Logger& logger);
    ~CPU() override = default;

    [[nodiscard]] bool handleClockTick(std::uint64_t tickNum) override;
};

}  // namespace unnes
