#pragma once

#include "clock.h"

namespace unnes
{

class ROM : public IClockedDevice
{

public:
    ROM() = default;
    ~ROM() override = default;

    void handleClockTick() override;

};

} // unnes
