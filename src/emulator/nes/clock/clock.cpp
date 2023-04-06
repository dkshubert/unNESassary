#include "clock.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes
{

Clock::Clock(Logger& logger)
    : _logger(logger)
{
}

void Clock::connect(const std::vector<IClockedDevice*>& devices)
{
    _connectedDevices.insert(_connectedDevices.end(), devices.begin(), devices.end());
}

std::uint32_t Clock::calculateCyclesToRun(double time) const
{
    const double timeDelta { time - _previousTime };

    // Note : some kind of narrowing conversion here is desired, though the rounding used here
    // almost certainly results in less fidelitous clock timing, which means this approach for
    // determining the # of cycles to execute since the last run might need to be revised when this
    // project is further along. This will probably work reasonably well for the time being, though.
    return getSpeedHz() * timeDelta;
}

bool Clock::run(double time)
{
    const std::uint32_t numCyclesToRun { calculateCyclesToRun(time) };

    for (std::uint32_t i { 0 }; i < numCyclesToRun; i++) {
        if (!tick()) {
            _logger.write(LogLevel::error, "Shutting down.");
            return false;
        }
    }

    _previousTime = time;

    return true;
}

bool Clock::tick()
{
    for (auto& device : _connectedDevices) {
        if (!device->handleClockTick(_totalTicks++)) {
            _logger.write(LogLevel::error,
                          "Tick failed. A hardware component connected to the Clock malfunctioned "
                          "(look above in the log for details).");
            return false;
        }
    }

    return true;
}

std::uint32_t Clock::getSpeedHz() const { return _speedHz; }

}  // namespace unnes
