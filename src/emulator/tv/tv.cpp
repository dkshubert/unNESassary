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

constexpr float getPixelWidth() { return 2.0f / screen::kWidthPixels; }

constexpr float getPixelHeight() { return 2.0f / screen::kHeightPixels; }

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
        glEnd();
        glfwSwapBuffers(_window.getGlfwWindow());

        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, _window.getWidth(),
                   _window.getHeight());  // Set the viewport to the entire window

        glMatrixMode(GL_PROJECTION);               // Set the matrix mode to projection
        glLoadIdentity();                          // Load the identity matrix
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Set the orthographic projection

        glMatrixMode(GL_MODELVIEW);  // Set the matrix mode to modelview
        glLoadIdentity();            // Load the identity matrix

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

bool TV::update(double time)
{
    // TODO : this is all test code

    const std::uint16_t numPixelsToRender { 61440 };
    for (std::uint16_t i { 0 }; i < numPixelsToRender; i++) {
        incrementScanline(
            { ._r = (i / numPixelsToRender) / 2.0f +
                    static_cast<float>(_currentScanlineRow) / screen::kHeightPixels,
              ._g = (i / numPixelsToRender) / 2.0f - _currentScanlineColumn / 256.0f,
              ._b = (i / numPixelsToRender) / 2.0f -
                    static_cast<float>(_currentScanlineRow) / screen::kHeightPixels });
    }

    _previousTime = time;

    return true;
}

}  // namespace unnes
