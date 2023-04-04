#pragma once

#include <source_location>
#include <string_view>

namespace unnes
{

enum class LogLevel
{
    all = 7,
    reserved = 6,
    trace = 5,
    debug = 4,
    info = 3,
    warn = 2,
    error = 1,
    off = 0
};

class Logger
{
private:
    LogLevel _level = LogLevel::info;

protected:
    Logger() = default;
    virtual ~Logger() = default;

    virtual void write(const std::string_view message) const = 0;

public:
    void setLevel(LogLevel level);
    void write(
        LogLevel level,
        const std::string_view message,
        const std::source_location location = std::source_location::current()) const;
};

} // namespace unnes
