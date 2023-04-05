#pragma once

#include "nes.h"
#include "stdoutlogger.h"
#include "tv_config.h"

class GLFWwindow;

namespace unnes
{

class Logger;

/// @brief Television.
class TV
{
    TvConfig _tvConfig;
    Logger& _logger;
    GLFWwindow* _window { nullptr };

public:
    TV(TvConfig tvConfig, Logger& logger);
    ~TV();

    /// @return True if the TV is turned on, False if it has been switched off.
    bool isOn() const;
    void run(double time);
};

}  // namespace unnes
