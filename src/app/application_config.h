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
    std::string _lastPlayedRomPath { "/home/dkshubert/work/mario_mine2.nes" };

    LogLevel _logLevel = LogLevel::debug;

    TvConfig _tvConfig {};
};

}  // namespace unnes
