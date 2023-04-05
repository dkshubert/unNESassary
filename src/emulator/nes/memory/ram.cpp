#include "ram.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes
{

RAM::RAM(Logger& logger)
    : _logger(logger)
{
}

bool RAM::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO

    return true;
}

}  // namespace unnes
