#include "utils/logger.h"

#include <fmt/core.h>

namespace unnes
{

void Logger::setLevel(LogLevel level) { _level = level; }

void Logger::write(LogLevel level,                  //
                   const std::string_view message,  //
                   const std::source_location location) const
{
    if (_level >= level) {
        write(                                //
            fmt::format(                      //
                "{} ({}): {}",                //
                location.function_name(),     //
                location.line(),              //
                std::string(message.begin(),  //
                            message.end()))   //
        );
    }
}

}  // namespace unnes
