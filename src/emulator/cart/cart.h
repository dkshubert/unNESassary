#pragma once

#include <string>
#include <string_view>

namespace unnes {

class Logger;

class Cart {
    Logger& _logger;
    std::string _romPath;

   public:
    Cart(Logger& logger, const std::string_view romPath);
};

}  // namespace unnes
