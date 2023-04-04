#include <cstdint>

#include "clock.h"
#include "logger.h"

namespace unnes
{

Clock::Clock(Logger& logger)
    : _connectedDevices()
    , _logger(logger)
{
}

void Clock::connect(const std::vector<IClockedDevice*>& devices)
{
    _connectedDevices.insert(_connectedDevices.end(), devices.begin(), devices.end());
}

std::uint64_t Clock::tick()
{
    ++_cycleNum;

    for (auto& device : _connectedDevices)
    {
        device->handleClockTick();
    }

    return _cycleNum;
}

std::uint32_t Clock::getSpeedHz() const
{
    return _speedHz;
}

} // unnes