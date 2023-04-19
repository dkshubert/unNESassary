#include "cartridge.h"

#include <fmt/core.h>

#include <array>
#include <cstddef>

#include "file_utils.h"
#include "logger.h"

namespace unnes
{

static constexpr size_t kRomPageSizeKB { 16 };

struct Header {
    // Bytes 0-3 of the ROM should be the string 'N', 'E', 'S', '\x1A'.
    std::array<char, 4> _nesString {};

    // Byte 4 is the number of 16kB Program ROM (PRG-ROM) banks.
    std::uint8_t _prgRomSize { 0 };

    // Byte 5 is the size of 8kB Character ROM (CHR-ROM) banks.
    std::uint8_t _chrRomSize { 0 };

    // Byte 6 contains a number of flags. From https://www.nesdev.org/wiki/INES :
    // 76543210
    // ||||||||
    // |||||||+- Mirroring: 0: horizontal (vertical arrangement) (CIRAM A10 = PPU A11)
    // |||||||              1: vertical (horizontal arrangement) (CIRAM A10 = PPU A10)
    // ||||||+-- 1: Cartridge contains battery-backed PRG RAM ($6000-7FFF) or other persistent
    // memory
    // |||||+--- 1: 512-byte trainer at $7000-$71FF (stored before PRG data)
    // ||||+---- 1: Ignore mirroring control or above mirroring bit; instead provide four-screen
    // VRAM
    // ++++----- Lower nybble of mapper number
    std::uint8_t _flags6 { 0 };
    std::uint8_t _flags7 { 0 };
    std::uint8_t _flags8 { 0 };
    std::uint8_t _flags9 { 0 };
    std::uint8_t _flags10 { 0 };
    std::array<std::uint8_t, 5> _padding;
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

    if (header._prgRomSize == std::uint8_t { 0 }) {
        _logger.write(LogLevel::error,
                      "The ROM is invalid. The header claims there's no program data.");
        return false;
    }
    _logger.write(LogLevel::debug,
                  fmt::format("Program ROM size (num 16kB chunks): {}", header._prgRomSize));

    if (header._chrRomSize == std::uint8_t { 0 }) {
        _logger.write(LogLevel::info, "CH-RAM cart detected.");
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

    // TODO : finish parsing header flags...

    static constexpr size_t kPrgRomBankSize = 0x4000;
    const size_t prgRomSize = static_cast<size_t>(header._prgRomSize);
    _prgRom.resize(kPrgRomBankSize * prgRomSize);
    if (!rom.read(reinterpret_cast<char*>(_prgRom.data()),
                  static_cast<long int>(_prgRom.capacity()))) {
        _logger.write(LogLevel::error, "Failed to read PRG-ROM");
        return false;
    }

    static constexpr size_t kChrRomBankSize = 0x2000;
    const size_t chrRomSize = static_cast<size_t>(header._chrRomSize);
    if (chrRomSize != 0) {
        _chrRom.resize(kChrRomBankSize * chrRomSize);
        if (!rom.read(reinterpret_cast<char*>(_chrRom.data()),
                      static_cast<long int>(_chrRom.capacity()))) {
            _logger.write(LogLevel::error, "Failed to read CHR-ROM");
            return false;
        }
    }

    _logger.write(LogLevel::info, fmt::format("Successfully loaded ROM"));

    return true;
}

std::span<std::uint8_t> Cartridge::getPrgRom() { return _prgRom; }

std::span<std::uint8_t> Cartridge::getChrRom() { return _chrRom; }

void Cartridge::furiouslyBlowOutDust()
{
    _logger.write(LogLevel::info, fmt::format("Nothing happened..."));
}

}  // namespace unnes
