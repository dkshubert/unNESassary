#pragma once

#include "electronic_device.h"
#include "nes.h"
#include "stdoutlogger.h"
#include "tv_config.h"

class GLFWwindow;

namespace unnes
{

class Logger;

/// @brief Television.
class TV : public IElectronicDevice
{
    TvConfig _tvConfig;
    GLFWwindow* _window { nullptr };
    Logger& _logger;

public:
    TV(TvConfig tvConfig, Logger& logger);
    ~TV() = default;

    /// @brief Sets the GLFW window
    ///
    /// @todo This method will probably get deleted when a rudimentary graphics lib is implemented.
    ///
    /// @param window A pointer to the application's GLFW window.
    void setWindow(GLFWwindow* window);

    /// @brief Renders a single scanline.
    void renderScanline(/*scanlineBuffer, row*/);

    void turnOn() override;
    void turnOff() override;
    [[nodiscard]] bool isOn() const override;
    [[nodiscard]] bool update(double time) override;
};

}  // namespace unnes
