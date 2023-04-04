#include "apu.h"

#include <fmt/core.h>

#include "logger.h"

namespace unnes {

APU::APU(Logger& logger) : _logger(logger) {}

void APU::handleClockTick(std::uint64_t tickNum) {
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO
}

}  // namespace unnes
