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

constexpr size_t kNumEmulatedDevices = 2;
using DeviceList = std::array<IElectronicDevice*, kNumEmulatedDevices>;

/// @brief This is the main application class, used to house all objects that need to exists for the
/// lifetime of the application (the core abstractions like the NES and TV emulators, specifically)
class Application
{
    // Application management members
    ApplicationConfig _config;
    GLFWwindow* _window { nullptr };  // wrap in unique_ptr with custom deleter
    std::unique_ptr<Logger> _logger { nullptr };
    bool _shutdownRequested { false };

    // TODO: better encapsulate these mouse coordinates, probably in some AppGUI class.
    double _cursorX { 0 };
    double _cursorY { 0 };

    // The emulated device list
    NES _nes;
    TV _tv;
    DeviceList _devices { &_nes, &_tv };

    static void _handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    Application(ApplicationConfig config);
    ~Application();

    void handleKeypress(int key, int scancode, int action, int mods);

    /// @brief Runs the application. This method manages the main program loop.
    ///
    /// @returns True if the application exited successfully (intentionally user terminated), false
    /// otherwise.
    [[nodiscard]] bool run();
};

}  // namespace unnes
