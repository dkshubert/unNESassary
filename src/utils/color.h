#pragma once

#include <type_traits>

namespace unnes
{

template <class T>
struct Color {
    static_assert(std::is_arithmetic_v<T>, "Color requires an arithmetic template argument.");

    T _r;
    T _g;
    T _b;
};

}  // namespace unnes