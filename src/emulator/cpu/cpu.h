#pragma once

#include "clock.h"

namespace unnes
{

class CPU : public IClockedDevice
{

public:
    CPU() = default;
    ~CPU() override = default;

    void handleClockTick() override;

};

} // unnes
