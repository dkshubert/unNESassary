#pragma once

#include <string>
#include <string_view>

namespace unnes
{

class Logger;

/// @brief Represents a game (or test) NES cartridge
class Cartridge
{
    Logger& _logger;
    std::string _romPath;

    /// @brief Loads a ".nes" ROM from a file path on the system.
    ///
    /// @param romPath The path to the ".nes" ROM to load.
    /// @returns True if the ROM loaded successfully, false otherwise.
    bool load(const std::string_view romPath);

public:
    Cartridge(Logger& logger, const std::string_view romPath);

    /// @brief Enables debugging
    void furiouslyBlowOutDust();
};

}  // namespace unnes
