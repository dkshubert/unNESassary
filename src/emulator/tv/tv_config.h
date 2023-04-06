#pragma once

#include <cstdint>

namespace unnes
{

struct TvConfig {
    std::uint16_t _refreshRateHz { 60 };  // TODO: use an NTSC/PAL enum

    // Note : These width/height fields are signed because glfwCreateWindow takes signed values.
    // Pretty weird, IMO, but keeping consistent types here prevents a cast later on, ¯\_(ツ)_/¯
    std::int32_t _windowWidthPixels { 1024 };
    std::int32_t _windowHeightPixels { 768 };
};

}  // namespace unnes
