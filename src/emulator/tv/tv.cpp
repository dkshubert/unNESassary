#include "tv.h"

#include <fmt/core.h>
#include <GLFW/glfw3.h>

#include <array>
#include <cassert>

#include "logger.h"

namespace unnes
{

TV::TV(TvConfig& tvConfig, Logger& logger)
    : _config(tvConfig),
      _logger(logger)
{
}

void TV::setWindow(GLFWwindow* window)
{
    assert(window);

    _window = window;
}

float TV::getPixelWidth() const { return 2.0f / screen::kWidthPixels; }

float TV::getPixelHeight() const { return 2.0f / screen::kHeightPixels; }

void TV::incrementScanline(Color<float> color)
{
    const float x { -1.0f + getPixelWidth() * _currentScanlineColumn };
    const float y { 1.0f - getPixelHeight() * _currentScanlineRow };

    // Draw a test image a this point in the project. Later on we'll obviously really draw an image
    // obtained from the NES.
    renderPixel({ ._x = x, ._y = y }, color);  // TODO: construct the right color value here

    _currentScanlineColumn++;
    if (_currentScanlineColumn == screen::kWidthPixels) {
        _currentScanlineColumn = 0;
        _currentScanlineRow++;
    }

    if (_currentScanlineRow == screen::kHeightPixels) {
        // Swap buffers when an entire screen's worth of pixels has been drawn
        _currentScanlineRow = 0;
        glfwSwapBuffers(_window);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
    }
}

void TV::renderPixel(Point<float> coords, Color<float> color)
{
    glColor3f(color._r, color._g, color._b);
    glVertex2f(coords._x, coords._y);                                       // upper left
    glVertex2f(coords._x + getPixelWidth(), coords._y);                     // upper right
    glVertex2f(coords._x, coords._y - getPixelHeight());                    // lower left
    glVertex2f(coords._x + getPixelWidth(), coords._y - getPixelHeight());  // lower right
}

std::uint16_t TV::calculateNumScanlinesToRender(double time) const
{
    const double timeDelta { time - _previousTime };

    return _config._refreshRateHz * timeDelta * screen::kHeightPixels;
}

bool TV::update(double time)
{
    // TODO : pretty sure this is all trash. I think the PPU will take a reference to the TV, and
    // call incrementScanline. const std::uint16_t numScanlinesToRender {
    // calculateNumScanlinesToRender(time) };

    const std::uint16_t numPixelsToRender { 61440 };
    for (std::uint16_t i { 0 }; i < numPixelsToRender; i++) {
        incrementScanline({ ._r = (i / numPixelsToRender) / 2.0f + _currentScanlineRow / 240.0f,
                            ._g = (i / numPixelsToRender) / 2.0f - _currentScanlineColumn / 256.0f,
                            ._b = (i / numPixelsToRender) / 2.0f - _currentScanlineRow / 240.0f });
    }

    _previousTime = time;

    return true;
}

}  // namespace unnes
