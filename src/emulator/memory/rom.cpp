#include "logger.h"
#include "rom.h"

namespace unnes
{

ROM::ROM(Logger& logger)
    : _logger(logger)
{
}

void ROM::handleClockTick()
{
    // TODO
}

} // unnes
