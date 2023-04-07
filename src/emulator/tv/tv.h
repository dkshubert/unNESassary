#pragma once

#include <span>

#include "color.h"
#include "emulated_device.h"
#include "logger.h"
#include "nes_constants.h"
#include "point.h"

class GLFWwindow;

namespace unnes
{

class ApplicationConfig;
class Logger;
class Window;

using ScanlineBuffer = std::span<std::uint8_t, screen::kWidthPixels>;

/// @brief The main television abstraction. TV is capable of rendering individual scanlines, or
/// pixels.
class TV : public IEmulatedDevice
{
    Window& _window;
    Logger& _logger;

    // Rendering details
    double _previousTime { 0 };
    std::uint16_t _currentScanlineRow { 0 };
    std::uint16_t _currentScanlineColumn { 0 };

public:
    TV(Window& window, Logger& logger);
    ~TV() = default;

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
