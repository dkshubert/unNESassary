#pragma once

#include <array>
#include <memory>

#include "application_config.h"
#include "input_handler.h"
#include "logger.h"
#include "nes.h"
#include "time_utils.h"
#include "tv.h"
#include "window.h"

namespace unnes
{

class Logger;

static constexpr int kExitSuccess = 0;
static constexpr int kExitFailure = -1;
constexpr size_t kNumEmulatedDevices = 2;
using DeviceList = std::array<IEmulatedDevice*, kNumEmulatedDevices>;

/// @brief This is the main application class, used to house all objects that need to exists for the
/// lifetime of the application (the core abstractions like the NES and TV emulators, specifically)
class Application
{
    // Application Management
    ApplicationConfig _config;
    std::unique_ptr<Logger> _logger { nullptr };
    bool _shutdownRequested { false };
    Window _window;
    InputHandler _inputHandler;

    // Emulated Devices
    TV _tv;
    NES _nes;
    DeviceList _devices { &_tv, &_nes };

public:
    Application(ApplicationConfig config);
    ~Application();

    ApplicationConfig& getConfig();
    TV& getTV();
    InputHandler& getInputHandler();
    Window& getWindow();
    Logger& getLogger();

    /// @brief Runs the application. This method manages the main program loop.
    ///
    /// @returns 0 if and only if the program exited successfully. This return value is the command
    /// line exit status of this application (for example, the value of $? on linux).
    [[nodiscard]] int run();
};

}  // namespace unnes
