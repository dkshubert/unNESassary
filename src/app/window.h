#pragma once

class GLFWwindow;

namespace unnes
{

class ApplicationConfig;
class TV;
class InputHandler;

/// @brief Represents the application window.
class Window
{
    GLFWwindow* _window { nullptr };  // This is a C resource. It probably makes sense to wrap this
                                      // in a unique_ptr with a custom deleter (TODO).
    ApplicationConfig& _config;
    TV& _tv;
    InputHandler& _inputHandler;

public:
    Window(ApplicationConfig& config, TV& tv, InputHandler& inputHandler);
    ~Window();

    bool update();
};

}  // namespace unnes