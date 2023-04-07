#pragma once

#include <span>

#include "color.h"
#include "emulated_device.h"
#include "logger.h"
#include "nes_constants.h"
#include "point.h"
#include "tv_config.h"

class GLFWwindow;

namespace unnes
{

class Logger;

using ScanlineBuffer = std::span<std::uint8_t, screen::kWidthPixels>;

/// @brief The main television abstraction. TV is capable of rendering individual scanlines, or
/// pixels.
class TV : public IEmulatedDevice
{
    TvConfig& _config;
    GLFWwindow* _window { nullptr };
    Logger& _logger;

    // Rendering details
    double _previousTime { 0 };
    std::uint16_t _currentScanlineRow { 0 };
    std::uint16_t _currentScanlineColumn { 0 };

    /// @brief Calculates the number of scanlines to render since the last call to TV::update.
    ///
    /// @param time The time since application start, in seconds.
    ///
    /// @return The total number of scanlines that need to be drawn.
    std::uint16_t calculateNumScanlinesToRender(double time) const;

public:
    TV(TvConfig& tvConfig, Logger& logger);
    ~TV() = default;

    /// @brief Sets the GLFW window
    ///
    /// @todo This method will probably get deleted when a rudimentary graphics lib is implemented.
    ///
    /// @param window A pointer to the application's GLFW window.
    void setWindow(GLFWwindow* window);

    float getPixelWidth() const;
    float getPixelHeight() const;

    /// @brief Plots the next pixel on the current scanline, or starts a new scanline if the end of
    /// the current scanline has been reached.
    ///
    void incrementScanline(Color<float> color);

    /// @brief Renders a single pixel, at any given screen coordinate. The coordinate system spans
    /// from (-1,-1) top-left, to (1,1) bottom-right, inherited from GLFW.
    ///
    /// @param coords The coordinates of the pixel to be rendered. The x coordinate of the pixel to
    /// be rendered spans from -1 (leftmost) to 1 (rightmost). The y coordinate of the pixel to be
    /// rendered spans from 1 (top) to -1 (bottom).
    /// @param color The color of the pixel to be rendered.
    void renderPixel(Point<float> coords, Color<float> color);

    [[nodiscard]] bool update(double time) override;
};

}  // namespace unnes
