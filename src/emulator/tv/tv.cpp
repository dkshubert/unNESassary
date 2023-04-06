#include "tv.h"

#include <GLFW/glfw3.h>

#include <array>
#include <cassert>

#include "logger.h"

namespace unnes
{

TV::TV(TvConfig tvConfig, Logger& logger)
    : _config(tvConfig),
      _logger(logger)
{
}

void TV::setWindow(GLFWwindow* window)
{
    assert(window);

    _window = window;
}

constexpr float getPixelWidth() { return 2.0f / screen::kWidthPixels; }

void TV::renderScanline(ScanlineBuffer buffer)
{
    const float y { 1.0f - getPixelWidth() * _currentScanlineRow };

    // TODO (2): It probably makes sense to wrap all the gl functions to make it really easy to draw
    // a horizontal sequence of pixels, so that they're not used directly in this class. Maybe some
    // kind of IScanLineRenderer interface can be used, and the implementation can be swapped out,
    // with a GLScanlineRenderer, and possibly even a BashScanlineRenderer, or something fun like
    // that...

    // Draw a test image a this point in the project. Later on we'll obviously really draw an image
    // obtained from the NES.
    for (std::uint16_t i { 0 }; i < screen::kWidthPixels; i++) {
        const float x { -1.0f + getPixelWidth() * i };

        // TODO: populate color value from buffer
        renderPixel(x, y, buffer[i]);
    }

    _currentScanlineRow++;
    if (_currentScanlineRow == screen::kHeightPixels) {
        _currentScanlineRow = 0;
        glfwSwapBuffers(_window);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
    }
}

void TV::renderPixel(float x, float y, std::uint8_t color)
{
    glColor3f(color, color, color);
    glVertex2f(x, y);                                      // upper left
    glVertex2f(x + getPixelWidth(), y);                    // upper right
    glVertex2f(x, y - getPixelWidth());                    // lower left
    glVertex2f(x + getPixelWidth(), y - getPixelWidth());  // lower right
}

std::uint16_t TV::calculateNumScanlinesToRender(double time) const
{
    const double timeDelta { time - _previousTime };

    return _config._refreshRateHz * timeDelta * screen::kHeightPixels;
}

bool TV::update(double time)
{
    const std::uint16_t numScanlinesToRender { calculateNumScanlinesToRender(time) };

    // TODO: Actually populate this buffer from the PPU
    std::array<std::uint8_t, screen::kWidthPixels> dummyScanlineBuffer;

    for (std::uint16_t i { 0 }; i < numScanlinesToRender; i++) {
        renderScanline(dummyScanlineBuffer);
    }

    _previousTime = time;

    return true;
}

}  // namespace unnes
