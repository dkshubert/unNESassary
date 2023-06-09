#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <string_view>
#include <vector>

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
    bool _mirroring { false };
    std::vector<std::byte> _prgRom;
    std::vector<std::byte> _chrRom;

    bool headerIsValid(const Header& header);

public:
    Cartridge(Logger& logger);

    /// @brief Loads a ".nes" ROM from a file path on the system.
    ///
    /// @param romPath The path to the ".nes" ROM to load.
    /// @returns True if the ROM loaded successfully, false otherwise.
    [[nodiscard]] bool load(const std::string_view romPath);

    [[nodiscard]] std::span<std::byte> getPrgRom();
    [[nodiscard]] std::span<std::byte> getChrRom();

    /// @brief Does nothing.
    void furiouslyBlowOutDust();
};

}  // namespace unnes
