#pragma once

class GLFWwindow;

namespace unnes {

class Logger;

/// @brief Television.
class TV {
    Logger& _logger;
    GLFWwindow* _window{nullptr};

   public:
    TV(Logger& logger);
    ~TV();

    /// @return True if the TV is turned on, False if it has been switched off.
    bool isOn() const;
    void run(double time);
};

}  // namespace unnes
