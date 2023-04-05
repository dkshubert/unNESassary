#include "ppu.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes
{

PPU::PPU(Logger& logger)
    : _logger(logger)
{
}

bool PPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO

    return true;
}

}  // namespace unnes
