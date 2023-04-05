#pragma once

#include "application_config.h"
#include "nes.h"
#include "stdoutlogger.h"
#include "time_utils.h"
#include "tv.h"

namespace unnes
{

/// @brief This is the main application class, used to house all objects that need to exists for the
/// lifetime of the application (the core abstractions like the NES and TV emulators, specifically)
class Application
{
    ApplicationConfig _config;
    StdOutLogger _logger;
    NES _nes;
    TV _tv;

public:
    Application(ApplicationConfig config);
    ~Application();

    /// @brief Runs the application. This method manages the main program loop.
    void run();
};

}  // namespace unnes
