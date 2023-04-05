#pragma once

#include <string>

#include "tv_config.h"

namespace unnes
{

struct ApplicationConfig {
    // TODO : update this when command line processing is added. This is set as the default out of
    // convenience during the project boostrapping process.
    std::string _lastPlayedRomPath {
        "../external/nes-test-roms/cpu_dummy_reads/cpu_dummy_reads.nes"
    };

    TvConfig _tvConfig {};
};

}  // namespace unnes
