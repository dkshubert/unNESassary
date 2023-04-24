#include "tv.h"

#include <fmt/core.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cassert>

#include "logger.h"
#include "window.h"

namespace unnes
{

TV::TV(Window& window, Logger& logger)
    : _window(window),
      _logger(logger)
{
}

[[nodiscard]] constexpr float getPixelWidth() { return 2.0f / screen::kWidthPixels; }

[[nodiscard]] constexpr float getPixelHeight() { return 2.0f / screen::kHeightPixels; }

void TV::incrementScanline(Color<float> color)
{
    const float x { -1.0f + getPixelWidth() * _currentScanlineColumn };
    const float y { 1.0f - getPixelHeight() * _currentScanlineRow };

    renderPixel({ ._x = x, ._y = y }, color);

    _currentScanlineColumn++;
    if (_currentScanlineColumn == screen::kWidthPixels) {
        _currentScanlineColumn = 0;
        _currentScanlineRow++;
    }

    if (_currentScanlineRow >= screen::kHeightPixels) {
        // Swap buffers when an entire screen's worth of pixels has been drawn
        _currentScanlineRow = 0;

        flushGraphics();
    }
}

void TV::forceNextScanline()
{
    _currentScanlineColumn = 0;
    _currentScanlineRow++;
}

void TV::flushGraphics()
{
    _currentScanlineRow = 0;
    _currentScanlineColumn = 0;

    glfwSwapBuffers(_window.getGlfwWindow());
}

void TV::renderPixel(Point<float> coords, Color<float> color)
{
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(color._r, color._g, color._b);
    glVertex2f(coords._x, coords._y);                                       // upper left
    glVertex2f(coords._x + getPixelWidth(), coords._y);                     // upper right
    glVertex2f(coords._x, coords._y - getPixelHeight());                    // lower left
    glVertex2f(coords._x + getPixelWidth(), coords._y - getPixelHeight());  // lower right
    glEnd();
}

bool TV::update(double time)
{
    // TODO : delete this function?

    _previousTime = time;

    return true;
}

}  // namespace unnes
