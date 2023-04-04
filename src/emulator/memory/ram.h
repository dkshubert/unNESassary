#pragma once

#include "clock.h"

namespace unnes
{

class RAM : public IClockedDevice
{

public:
    RAM() = default;
    ~RAM() override = default;

    void handleClockTick() override;

};

} // unnes
