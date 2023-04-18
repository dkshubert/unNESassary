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
    constexpr std::uint8_t kWidth { screen::kWidthPixels / sprite::kLengthPixels };
    constexpr std::uint8_t kHeight { screen::kHeightPixels / sprite::kLengthPixels };
}

}  // namespace unnes