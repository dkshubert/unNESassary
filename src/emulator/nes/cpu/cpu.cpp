#include "cpu.h"

#include <fmt/core.h>

#include <cassert>
#include <cstddef>

#include "cartridge.h"
#include "logger.h"

namespace unnes
{

CPU::CPU(Logger& logger)
    : _logger(logger)
{
}

void CPU::connectCartridge(Cartridge* cartridge)
{
    assert(cartridge);
    _cartridge = cartridge;
    _registers._PC = cartridge->getPrgRom().data();
}

bool CPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    if (_registers._PC) {
        const std::byte instructionByte = *_registers._PC;
        (void)instructionByte;

        // TODO : actually handle the instruction
    }

    return true;
}

}  // namespace unnes
