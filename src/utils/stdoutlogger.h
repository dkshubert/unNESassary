#pragma once

#include "logger.h"

namespace unnes
{

class StdOutLogger : public Logger
{
public:
    StdOutLogger(LogLevel level);
    ~StdOutLogger() override = default;

protected:
    void write(std::string_view message) const override;
};

}  // namespace unnes
