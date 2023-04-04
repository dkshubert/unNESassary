#pragma once

#include <cstdint>
#include <vector>

#include "clock_defaults.h"

namespace unnes
{

class Logger;

struct IClockedDevice
{
    virtual ~IClockedDevice() = default;

    virtual void handleClockTick() = 0;
};

class Clock
{
    /// @note _speedHz isn't const because we want to be able to adjust the speed of emulation
    /// dynamically, based on the user's application settings.
    std::uint32_t _speedHz { ntsc::kSpeedHz };
    std::uint64_t _cycleNum { 0 };
    std::vector<IClockedDevice*> _connectedDevices;
    Logger& _logger;

public:
    Clock(Logger& logger);

    void connect(const std::vector<IClockedDevice*>& devices);

    /// @brief Cycles the clock once.
    ///
    /// @return The current cycle number. 
    std::uint64_t tick();

    /// @return Returns the currently set clock speed, in Hz. 
    [[nodiscard]]
    std::uint32_t getSpeedHz() const;
};

} // unnes
