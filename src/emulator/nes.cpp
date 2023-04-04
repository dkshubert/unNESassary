#include <cstdint>

#include <iostream>

#include "nes.h"

namespace unnes
{

NES::NES()
{
    const std::vector<IClockedDevice*> devices {
        &_cpu,
        &_ppu,
        &_apu,
        &_ram,
        &_rom
    };

    _clock.connect(devices);
}

void NES::run(double time)
{
    const double timeDelta = time - _previousTime;

    // Note : the narrowing conversion here is desired
    const std::uint32_t numCyclesToRun = _clock.getSpeedHz() * timeDelta;

    for (std::uint32_t i = 0; i < numCyclesToRun; i++)
    {
        _clock.tick();
    }

    _previousTime = time;
}

} // namespace unnes
