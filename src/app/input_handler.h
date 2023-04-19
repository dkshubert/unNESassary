#pragma once

#include <GLFW/glfw3.h>

#include <functional>
#include <map>
#include <vector>

#include "point.h"

class GLFWwindow;

namespace unnes
{

class Application;
class Logger;

enum class Key {
    ESCAPE = GLFW_KEY_ESCAPE
    // TODO : the rest
};

enum class ButtonState {
    PRESSED = GLFW_PRESS,
    RELEASED = GLFW_RELEASE,
    REPEAT = GLFW_REPEAT
};

using KeyboardCallback = std::function<void(ButtonState)>;

/// @brief This is the main input handler for the application. Any object interested in handling
/// keyboard or mouse input from the user can register a callback to the sole InputHandler instance,
/// which is owned by the Application class.
class InputHandler
{
    Point<double> _cursorPosition { ._x = 0, ._y = 0 };
    std::map<Key, KeyboardCallback> _callbacks {};

    Application& _application;
    Logger& _logger;

public:
    InputHandler(Application& application);
    ~InputHandler() = default;

    /// @brief Callback to the glfwSetKeyCallback function to handle keypresses. This function needs
    /// to be public to deal with the static C-style callback API provided by GLFW, but should never
    /// be called directly outside of the static callback to GLFW.
    ///
    /// @param key A unique ID for the key that was pressed. GLFW_KEY_<key_name> is the pattern for
    /// GLFW keycode defines (for example, GLFW_KEY_ESCAPE).
    /// @param scancode The system-specific scancode of the key.
    /// @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
    /// @param mods Bit field describing which modifier keys were held down. An example modifier
    /// would be GLFW_MOD_CONTROL (or GLFW_MOD_ALT, etc).
    void handleKeypress(int key, int scancode, int action, int mods);

    /// @brief Gets the current mouse coordinates.
    ///
    /// @return The current mouse coordinates.
    [[nodiscard]] Point<double> getMouseCoordinates();

    /// @brief Registers a callback that will be invoked when the provided keyCode is pressed. The
    /// callback contains a ButtonState value to indicate whether the key was pressed, release, or
    /// held.
    ///
    /// @note Currently only a single callback can be registered to one key, but it might be worth
    /// incurring the added the complexity of having multiple callbacks for one keypress. We'll
    /// cross that road when it becomes necessary.
    /// @param key The key that was pressed.
    /// @param callback The callback that will be invoked when keyCode is pressed.
    void registerCallback(Key key, KeyboardCallback&& callback);

    /// @brief Clears a registered callback.
    ///
    /// @param key The key whose callback will be cleared.
    void clearCallback(Key key);

    /// @brief Updates the input handler (the mouse coordinates specifically).
    void update();
};

}  // namespace unnes