#include "clock.h"

#include <cstdint>

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

std::uint64_t Clock::tick()
{
    for (auto& device : _connectedDevices) {
        device->handleClockTick(_totalTicks);
    }

    return _totalTicks++;
}

std::uint32_t Clock::getSpeedHz() const { return _speedHz; }

}  // namespace unnes
