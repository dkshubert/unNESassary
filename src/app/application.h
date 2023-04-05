#pragma once

#include <array>
#include <memory>

#include "application_config.h"
#include "logger.h"
#include "nes.h"
#include "time_utils.h"
#include "tv.h"

namespace unnes
{

class Logger;

/// @brief This is the main application class, used to house all objects that need to exists for the
/// lifetime of the application (the core abstractions like the NES and TV emulators, specifically)
class Application
{
    ApplicationConfig _config;
    bool _closeRequested { false };
    std::unique_ptr<Logger> _logger { nullptr };
    NES _nes;
    TV _tv;
    std::array<IElectronicDevice*, 2> _devices { &_nes, &_tv };

public:
    Application(ApplicationConfig config);
    ~Application();

    /// @brief Runs the application. This method manages the main program loop.
    ///
    /// @returns True if the application exited successfully (intentionally user terminated), false
    /// otherwise.
    [[nodiscard]] bool run();
};

}  // namespace unnes
