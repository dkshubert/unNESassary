#pragma once

#include "clock.h"

namespace unnes
{

class APU : public IClockedDevice
{

public:
    APU() = default;
    ~APU() override = default;

    void handleClockTick() override;
};

} // unnes
