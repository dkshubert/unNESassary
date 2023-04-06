#include "input_handler.h"

#include <fmt/core.h>

#include <cassert>

#include "logger.h"

namespace unnes
{

void _handleKeypress(GLFWwindow*, int, int, int, int);

InputHandler::InputHandler(Logger& logger)
    : _logger(logger)
{
}

void InputHandler::setWindow(GLFWwindow* window)
{
    assert(window);

    _window = window;
    glfwSetWindowUserPointer(_window, this);
    glfwSetKeyCallback(_window, _handleKeypress);
}

void _handleKeypress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (auto thisPtr = reinterpret_cast<InputHandler*>(glfwGetWindowUserPointer(window))) {
        thisPtr->handleKeypress(key, scancode, action, mods);
    }
}

void InputHandler::handleKeypress(int key, int scancode, int action, int mods)
{
    _logger.write(LogLevel::info,
                  fmt::format("Key Pressed ({}), scancode ({}), action ({}), mods ({})", key,
                              scancode, action, mods));

    auto entry = _callbacks.find(key);
    if (entry == _callbacks.end()) {
        _logger.write(LogLevel::debug, "No callback registered for key.");
    } else {
        _logger.write(LogLevel::debug, "Executing callback.");
        auto& callback = entry->second;
        callback(static_cast<ButtonState>(action));
    }
}

void InputHandler::registerCallback(KeyCode keyCode, KeyboardCallback callback)
{
    _logger.write(LogLevel::info, fmt::format("Registered handler for key: {}", keyCode));
    _callbacks[keyCode] = callback;
}

void InputHandler::clearCallback(KeyCode keyCode)
{
    _logger.write(LogLevel::info, fmt::format("Deregistered handler for key: {}", keyCode));
    _callbacks.erase(keyCode);
}

void InputHandler::update() { glfwGetCursorPos(_window, &_cursorX, &_cursorY); }

}  // namespace unnes
