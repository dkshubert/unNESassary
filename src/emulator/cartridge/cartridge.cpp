#include "cartridge.h"

#include <fmt/core.h>

#include <array>
#include <cstddef>

#include "file_utils.h"
#include "logger.h"

namespace unnes
{

static constexpr size_t kRomPageSizeKB = 16;

struct Header {
    // Bytes 0-3 of the ROM should be the string 'N', 'E', 'S', '\x1A'.
    std::array<char, 4> _nesString {};

    // Byte 4 is the size of Program ROM (PRG-ROM), in units of 16kB.
    std::byte _prgRomSize { 0 };

    // Byte 5 is the size of the Character ROM (CHR-ROM), in units of 16kB.
    std::byte _chrRomSize { 0 };
};

Cartridge::Cartridge(Logger& logger)
    : _logger(logger)
{
}

bool Cartridge::headerIsValid(const Header& header)
{
    const std::string nesString(header._nesString.begin(), header._nesString.end());
    if (nesString != "NES\x1A") {
        _logger.write(LogLevel::error, fmt::format("Failed to load the NES ROM. The file doesn't "
                                                   "appear to be a valid ROM. Starting bytes: {}",
                                                   header._nesString));
        return false;
    }

    if (header._prgRomSize == std::byte { 0 }) {
        _logger.write(LogLevel::error,
                      "The ROM is invalid. The header claims there's no program data.");
        return false;
    }
    _logger.write(LogLevel::debug,
                  fmt::format("Program ROM size (num 16kB chunks): {}", header._prgRomSize));

    if (header._chrRomSize == std::byte { 0 }) {
        _logger.write(LogLevel::error,
                      "The ROM is invalid. The header claims there's no character data.");
        return false;
    }
    _logger.write(LogLevel::debug,
                  fmt::format("Character ROM size (num 16kB chunks): {}", header._chrRomSize));

    return true;
}

bool Cartridge::load(const std::string_view romPath)
{
    _logger.write(LogLevel::info, fmt::format("Attempting to load ROM: {}", romPath));

    std::ifstream rom { std::string(romPath.begin(), romPath.end()),
                        std::ios_base::binary | std::ios_base::in };
    if (!rom) {
        _logger.write(LogLevel::error, "Failed to open ROM");
        return false;
    }

    const Header header = read<Header>(rom);
    if (!headerIsValid(header)) {
        _logger.write(LogLevel::error, "Failed to load ROM Header");
        return false;
    }

    _prgRomSizeKb = static_cast<size_t>(header._prgRomSize) * kRomPageSizeKB;
    _chrRomSizeKb = static_cast<size_t>(header._chrRomSize) * kRomPageSizeKB;

    _logger.write(LogLevel::info, fmt::format("Successfully loaded ROM"));

    return true;
}

}  // namespace unnes
