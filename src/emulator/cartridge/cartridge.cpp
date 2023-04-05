#include "cartridge.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes
{

Cartridge::Cartridge(Logger& logger, const std::string_view romPath)
    : _logger(logger),
      _romPath(romPath)
{
    _logger.write(LogLevel::info,
                  fmt::format("cart loaded: {}", std::string(romPath.begin(), romPath.end())));
}

}  // namespace unnes