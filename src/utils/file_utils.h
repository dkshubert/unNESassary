#pragma once

#include <concepts>
#include <fstream>
#include <type_traits>

namespace unnes
{

template <class T>
concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

template <TriviallyCopyable T>
[[nodiscard]] T read(std::ifstream& stream)
{
    T output;
    stream.read(reinterpret_cast<char*>(&output), sizeof(T));
    return output;
}

}  // namespace unnes
