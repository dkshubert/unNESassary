#pragma once

#include <type_traits>

namespace unnes
{

template <class T>
struct Point {
    static_assert(std::is_arithmetic_v<T>, "Point requires an arithmetic template argument.");

    T _x;
    T _y;
};

}  // namespace unnes