#pragma once

#include <string>
#include <string_view>

namespace unnes
{

class Logger;

class Cartridge
{
    Logger& _logger;
    std::string _romPath;

public:
    Cartridge(Logger& logger, const std::string_view romPath);
};

}  // namespace unnes
