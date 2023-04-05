#include "cpu.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes
{

CPU::CPU(Logger& logger)
    : _logger(logger)
{
}

bool CPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO

    return true;
}

}  // namespace unnes
