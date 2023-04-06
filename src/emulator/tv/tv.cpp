#include "tv.h"

#include <GLFW/glfw3.h>

#include <cassert>

#include "logger.h"

namespace unnes
{

TV::TV(TvConfig tvConfig, Logger& logger)
    : _tvConfig(tvConfig),
      _logger(logger)
{
}

void TV::setWindow(GLFWwindow* window)
{
    assert(window);

    _window = window;
}

void TV::renderScanline()
{
    // TODO (1): Scale scanline to the width of the window. Something like... pixelWidth =
    // windowWidth / scanlineBufferLength. Move this to its own function.

    // TODO (2): It probably makes sense to wrap all the gl functions to make it really easy to draw
    // a horizontal sequence of pixels, so that they're not used directly in this class. Maybe some
    // kind of IScanLineRenderer interface can be used, and the implementation can be swapped out,
    // with a GLScanlineRenderer, and possibly even a BashScanlineRenderer, or something fun like
    // that...
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a test image a this point in the project. Later on we'll obviously really draw an image
    // obtained from the NES.
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(0.f, 0.5f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    // Swap buffers
    glfwSwapBuffers(_window);
}

bool TV::update(double /* time */)
{
    // TODO: calculate the number of scanlines to render based on the refresh rate and the time
    // delta since last update.
    renderScanline();

    return true;
}

}  // namespace unnes
