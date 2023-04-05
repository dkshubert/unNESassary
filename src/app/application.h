#pragma once

#include "application_config.h"
#include "nes.h"
#include "stdoutlogger.h"
#include "time_utils.h"
#include "tv.h"

namespace unnes
{

class Application
{
    StdOutLogger _logger {};
    NES _nes { _logger };
    ApplicationConfig _config;
    TV _tv;

public:
    Application(ApplicationConfig config);
    ~Application();

    void run();
};

}  // namespace unnes
