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

static constexpr int kExitSuccess = 0;
static constexpr int kExitFailure = -1;
constexpr size_t kNumEmulatedDevices = 2;
using DeviceList = std::array<IEmulatedDevice*, kNumEmulatedDevices>;

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

    /// @brief Callback to the glfwSetKeyCallback function to handle keypresses. This function needs
    /// to be static because GLFW provides a C-style callback API.
    ///
    /// @param window A pointer to the main application window.
    /// @param key A unique ID for the key that was pressed. GLFW_KEY_<key_name> is the pattern for
    /// GLFW keycode defines (for example, GLFW_KEY_ESCAPE).
    /// @param scancode The system-specific scancode of the key.
    /// @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
    /// @param mods Bit field describing which modifier keys were held down. An example modifier
    /// would be GLFW_MOD_CONTROL (or GLFW_MOD_ALT, etc).
    static void _handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// @brief Runs the main application loop. This function blocks until the application has
    /// received a shutdown request, or until a major failure has occurred.
    ///
    /// @return True if the main loop exited gracefully as a result of a user application shutdown
    /// request. This function will return false if an error caused the loop to shutdown.
    bool runMainLoop();

public:
    Application(ApplicationConfig config);
    ~Application();

    /// @brief Callback to the glfwSetKeyCallback function to handle keypresses. This is the
    /// internal implementation of the static callback of this method, that provides access to class
    /// members.
    ///
    /// @param key A unique ID for the key that was pressed. GLFW_KEY_<key_name> is the pattern for
    /// GLFW keycode defines (for example, GLFW_KEY_ESCAPE).
    /// @param scancode The system-specific scancode of the key.
    /// @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
    /// @param mods Bit field describing which modifier keys were held down. An example modifier
    /// would be GLFW_MOD_CONTROL (or GLFW_MOD_ALT, etc).
    void handleKeypress(int key, int scancode, int action, int mods);

    /// @brief Runs the application. This method manages the main program loop.
    ///
    /// @returns 0 if and only if the program exited successfully. This return value is the command
    /// line exit status of this application (for example, the value of $? on linux).
    [[nodiscard]] int run();
};

}  // namespace unnes
