#pragma once

#include <string>
#include <string_view>

namespace unnes
{

class Logger;
class Header;

/// @brief Represents a game (or test) NES cartridge, which is loaded from an ".nes" ROM from the
/// filesystem.
class Cartridge
{
    Logger& _logger;
    std::string _romPath;
    size_t _prgRomSizeKb { 0 };
    size_t _chrRomSizeKb { 0 };

    bool headerIsValid(const Header& header);

public:
    Cartridge(Logger& logger);

    /// @brief Loads a ".nes" ROM from a file path on the system.
    ///
    /// @param romPath The path to the ".nes" ROM to load.
    /// @returns True if the ROM loaded successfully, false otherwise.
    [[nodiscard]] bool load(const std::string_view romPath);

    /// @brief Enables debugging
    void furiouslyBlowOutDust();
};

}  // namespace unnes
