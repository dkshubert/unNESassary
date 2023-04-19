#pragma once

#include <cstdint>

namespace unnes
{

namespace screen
{

constexpr std::uint16_t kWidthPixels { 256 };
constexpr std::uint16_t kHeightPixels { 240 };

}  // namespace screen

namespace sprite
{
    constexpr std::uint8_t kLengthPixels { 8 };
}

namespace tilesheet
{
    constexpr std::byte kWidth { static_cast<std::byte>(screen::kWidthPixels / sprite::kLengthPixels) };
    constexpr std::byte kHeight { static_cast<std::byte>(screen::kHeightPixels / sprite::kLengthPixels) };
}

}  // namespace unnes