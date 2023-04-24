#pragma once

#include <cstddef>
#include <cstdint>

namespace unnes
{

/// @brief Houses the set of the CPU registers.
struct Registers {
    /// @brief The Accumulator register, houses arithmatic and logic results.
    std::byte _A { 0 };

    /// @brief Used for looping operations.
    std::byte _X { 0 };

    /// @see _X
    std::byte _Y { 0 };

    /// @brief The Program Counter. Technically this should be two bytes, but I'm betting it will be
    /// easier if it's a pointer to a byte, since that's ultimately what PC tracks.
    std::byte* _PC { nullptr };

    /// @brief The Stack Pointer.
    std::byte _SP { 0 };

    /// @brief The Status register.
    std::byte _P { 0 };
};

}  // namespace unnes
