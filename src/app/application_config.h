#pragma once

#include <string>

#include "logger.h"
#include "tv_config.h"

namespace unnes
{

/// @brief The application configuration, housing values like the refresh rate, window dimensions,
/// key mappings, and so forth.
struct ApplicationConfig {
    // TODO : update this when command line processing is added. This is set as the default out of
    // convenience during the project boostrapping process.
    std::string _lastPlayedRomPath {
        "../external/nes-test-roms/cpu_dummy_reads/cpu_dummy_reads.nes"
    };

    LogLevel _logLevel = LogLevel::info;

    TvConfig _tvConfig {};
};

}  // namespace unnes
