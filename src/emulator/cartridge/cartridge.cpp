#include "cartridge.h"

#include <fmt/core.h>

#include <fstream>

#include "logger.h"

namespace unnes
{

Cartridge::Cartridge(Logger& logger)
    : _logger(logger)
{
}

bool Cartridge::load(const std::string_view romPath)
{
    _logger.write(LogLevel::info, fmt::format("Attempting to load ROM: {}", romPath));

    std::ifstream rom { _romPath, std::ios_base::binary | std::ios::in };

    // if (!rom) {
    //     _logger.write(LogLevel::warn, fmt::format("Failed to load ROM"));
    //     return false;
    // }

    // TODO : parse ROM header and load memory buffers + provide accessors to cart memory

    _logger.write(LogLevel::info, fmt::format("Successfully loaded ROM"));

    return true;
}

}  // namespace unnes
