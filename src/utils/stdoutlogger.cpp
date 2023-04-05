#include "stdoutlogger.h"

#include <fmt/core.h>

namespace unnes
{

void StdOutLogger::write(const std::string_view message) const
{
    fmt::print("{}\n", std::string(message.begin(), message.end()));
}

}  // namespace unnes
