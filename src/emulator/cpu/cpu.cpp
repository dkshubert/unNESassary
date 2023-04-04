#include <fmt/core.h>

#include "cpu.h"
#include "logger.h"

namespace unnes
{

CPU::CPU(Logger& logger)
    : _logger(logger)
{
}

void CPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(
        LogLevel::trace,
        fmt::format("handling tickNum: {}", tickNum)
    );

    // TODO
}

} // unnes
