#pragma once

#include "electronic_device.h"
#include "nes.h"
#include "stdoutlogger.h"
#include "tv_config.h"

class GLFWwindow;

namespace unnes
{

class Logger;

/// @brief Television.
class TV : public IElectronicDevice
{
    TvConfig _tvConfig;
    Logger& _logger;
    GLFWwindow* _window { nullptr };

public:
    TV(TvConfig tvConfig, Logger& logger);
    ~TV();

    void turnOn() override;
    void turnOff() override;
    [[nodiscard]] bool isOn() const override;
    [[nodiscard]] bool update(double time) override;
};

}  // namespace unnes
