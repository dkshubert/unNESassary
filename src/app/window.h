#pragma once

class GLFWwindow;

namespace unnes
{

class Application;
class Logger;

/// @brief Represents the application window.
class Window
{
    GLFWwindow* _window { nullptr };  // This is a C resource. It probably makes sense to wrap this
                                      // in a unique_ptr with a custom deleter (TODO).
    Application& _application;
    Logger& _logger;
    int _currentWidth { 0 };
    int _currentHeight { 0 };

public:
    Window(Application& application);
    ~Window();

    void handleResize(int width, int height);
    [[nodiscard]] GLFWwindow* getGlfwWindow();
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] bool update();
};

}  // namespace unnes