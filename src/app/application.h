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
    ApplicationConfig _config;
    StdOutLogger _logger;
    NES _nes;
    TV _tv;

public:
    Application(ApplicationConfig config);
    ~Application();

    void run();
};

}  // namespace unnes
