#include "ram.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes {

RAM::RAM(Logger& logger) : _logger(logger) {}

void RAM::handleClockTick(std::uint64_t tickNum) {
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO
}

}  // namespace unnes
