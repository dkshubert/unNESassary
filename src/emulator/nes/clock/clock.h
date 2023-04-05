#pragma once

#include <cstdint>
#include <vector>

#include "clock_defaults.h"

namespace unnes
{

class Logger;

/// @brief An interface for any device connected to the clock (like the CPU or PPU). When a clock
/// tick occurs, any device implementing this interface that has connected itself to the Clock via
/// Clock::connect will be notified of the clock tick via its handClockTick implementation.
///
/// @see Clock::connect
struct IClockedDevice {
    virtual ~IClockedDevice() = default;

    /// @brief Hardware components react to each cock tick via their implementation of this
    /// method.
    ///
    /// @param tickNum The exact clock tick number since emulator boot.
    /// @returns True if the device handled the clock tick, false otherwise.
    [[nodiscard]] virtual bool handleClockTick(std::uint64_t tickNum) = 0;
};

/// @brief Represents the system clock.
class Clock
{
    /// @note _speedHz isn't const because we want to be able to adjust the speed of emulation
    /// dynamically, based on the user's application settings.
    std::uint32_t _speedHz { ntsc::kSpeedHz };
    std::uint64_t _totalTicks { 0 };
    std::vector<IClockedDevice*> _connectedDevices {};
    double _previousTime { 0 };

    Logger& _logger;

public:
    Clock(Logger& logger);

    /// @brief Connects a set of devices to this clock. These devices will be notified on each
    /// clock tick, via the IClockedDevice::handleClockTick function.
    ///
    /// @param devices The devices to connect to this clock instance.
    void connect(const std::vector<IClockedDevice*>& devices);

    /// @brief Runs the clock, ticking the clock as many times as necessary since the previous call
    /// to run(), which is a function of the main loop speed and the configured frequency of this
    /// clock instance.
    ///
    /// @param time The time (in seconds) since boot.
    /// @returns True if the clock successfully ran, false otherwise.
    [[nodiscard]] bool run(double time);

    /// @brief Cycles the clock once.
    ///
    /// @return True if ALL the HW modules connected to the clock succesfully updated, false
    /// otherwise.
    [[nodiscard]] bool tick();

    /// @return Returns the currently set clock speed, in Hz.
    [[nodiscard]] std::uint32_t getSpeedHz() const;
};

}  // namespace unnes
