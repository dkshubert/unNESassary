#pragma once

#include "clock.h"

namespace unnes
{

class PPU : public IClockedDevice
{

public:
    PPU() = default;
    ~PPU() override = default;

    void handleClockTick() override;

};

} // unnes
