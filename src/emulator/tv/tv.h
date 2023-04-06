#pragma once

#include <span>

#include "emulated_device.h"
#include "logger.h"
#include "nes_constants.h"
#include "tv_config.h"

class GLFWwindow;

namespace unnes
{

class Logger;

using ScanlineBuffer = std::span<std::uint8_t, screen::kWidthPixels>;

/// @brief Television.
class TV : public IEmulatedDevice
{
    TvConfig _config;
    GLFWwindow* _window { nullptr };
    Logger& _logger;

    // Rendering details
    double _previousTime { 0 };
    std::uint16_t _currentScanlineRow { 0 };

    std::uint16_t calculateNumScanlinesToRender(double time) const;

public:
    TV(TvConfig tvConfig, Logger& logger);
    ~TV() = default;

    /// @brief Sets the GLFW window
    ///
    /// @todo This method will probably get deleted when a rudimentary graphics lib is implemented.
    ///
    /// @param window A pointer to the application's GLFW window.
    void setWindow(GLFWwindow* window);

    /// @brief Renders a single scanline, directly under the previously rendered scanline, until the
    /// screen wraps.
    ///
    /// @param buffer A row of pixels spanning the entire screen, containing 256 pixels (the
    /// horizontal resolution of the NES).
    void renderScanline(ScanlineBuffer buffer);

    /// @brief Renders a single pixel. The coordinate system spans from (-1,-1) top-left, to (1,1)
    /// bottom-right, inherited from GLFW.
    /// @param x
    /// @param y
    /// @param color
    void renderPixel(float x, float y, std::uint8_t color);

    [[nodiscard]] bool update(double time) override;
};

}  // namespace unnes
