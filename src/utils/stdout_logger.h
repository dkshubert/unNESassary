#pragma once

#include "logger.h"

namespace unnes
{

class stdout_logger : public Logger
{
public:
    stdout_logger(LogLevel level);
    ~stdout_logger() override = default;

protected:
    void write(std::string_view message) const override;
};

}  // namespace unnes
