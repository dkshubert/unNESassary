#include "ppu.h"

#include <fmt/core.h>

#include "logger.h"
#include "tv.h"

namespace unnes
{

PPU::PPU(TV& tv, Logger& logger)
    : _tv(tv),
      _logger(logger)
{
}

bool PPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO

    return true;
}

}  // namespace unnes
