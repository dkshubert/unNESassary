#include "stdout_logger.h"

#include <fmt/core.h>

namespace unnes
{

stdout_logger::stdout_logger(LogLevel level) { setLevel(level); }

void stdout_logger::write(const std::string_view message) const
{
    fmt::print("{}\n", std::string(message.begin(), message.end()));
}

}  // namespace unnes
