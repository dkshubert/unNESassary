#include "input_handler.h"

#include <fmt/core.h>

#include <cassert>

#include "application.h"
#include "logger.h"

namespace unnes
{

void _handleKeypress(GLFWwindow*, int, int, int, int);

InputHandler::InputHandler(Application& application)
    : _application(application),
      _logger(_application.getLogger())
{
    glfwSetKeyCallback(_application.getWindow().getGlfwWindow(), _handleKeypress);
}

void _handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (auto applicationPtr = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window))) {
        applicationPtr->getInputHandler().handleKeypress(key, scancode, action, mods);
    }
}

void InputHandler::handleKeypress(int key, int scancode, int action, int mods)
{
    _logger.write(LogLevel::info,
                  fmt::format("Key Pressed ({}), scancode ({}), action ({}), mods ({})", key,
                              scancode, action, mods));

    auto entry { _callbacks.find(static_cast<Key>(key)) };
    if (entry == _callbacks.end()) {
        _logger.write(LogLevel::debug, "No callback registered for key.");
    } else {
        _logger.write(LogLevel::debug, "Executing callback.");
        auto& callback { entry->second };
        callback(static_cast<ButtonState>(action));
    }
}

Point<double> InputHandler::getMouseCoordinates() { return _cursorPosition; }

void InputHandler::registerCallback(Key key, KeyboardCallback&& callback)
{
    _logger.write(LogLevel::info, fmt::format("Registered handler for key: {}", static_cast<int>(key)));
    _callbacks[key] = std::move(callback);
}

void InputHandler::clearCallback(Key key)
{
    _logger.write(LogLevel::info, fmt::format("Deregistered handler for key: {}", static_cast<int>(key)));
    _callbacks.erase(key);
}

void InputHandler::update()
{
    glfwGetCursorPos(_application.getWindow().getGlfwWindow(), &_cursorPosition._x,
                     &_cursorPosition._y);
}

}  // namespace unnes
