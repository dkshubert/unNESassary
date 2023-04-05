#include "rom.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes
{

ROM::ROM(Logger& logger)
    : _logger(logger)
{
}

void ROM::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO
}

}  // namespace unnes
