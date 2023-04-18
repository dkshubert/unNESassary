#include "ppu.h"

#include <fmt/core.h>

#include <cassert>
#include <thread>

#include "cartridge.h"
#include "logger.h"
#include "tv.h"

namespace unnes
{

namespace test
{

/// TODO : use a span
void renderTile(std::uint8_t* chrom, TV& tv, Logger& logger);

}  // namespace test

PPU::PPU(TV& tv, Logger& logger)
    : _tv(tv),
      _logger(logger)
{
}

void PPU::connectCartridge(Cartridge* cartridge)
{
    assert(cartridge);
    _cartridge = cartridge;

    // TODO : delete this test code that loops through the sprite sheet and displays each tile, one
    // by one
    for (int i = 0; i < 20; i++) {
        test::renderTile(_cartridge->getChrRom().data() + 16 * i, _tv, _logger);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

bool PPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO : really handle a clock tick.

    return true;
}

void test::renderTile(std::uint8_t* chrom, TV& tv, Logger& logger)
{
    for (size_t byteIndex = 0; byteIndex < 8; byteIndex++) {
        const std::uint8_t left = chrom[byteIndex];
        const std::uint8_t right = chrom[8 + byteIndex];

        for (size_t pixelIndex = 0; pixelIndex < 8; pixelIndex++) {
            const std::uint8_t mask = 0b10000000 >> pixelIndex;

            // clang-format off
            const int pixel {
                ( ( ( mask & left ) << 1 ) | ( ( mask & right ) ) ) >> (7 - pixelIndex)
            };
            // clang-format on

            logger.write(LogLevel::trace,
                         fmt::format("left: {}, right: {}, pixel: {}", left, right, pixel));
            const float f { static_cast<int>(pixel) / 3.0f };
            tv.incrementScanline({ ._r = f, ._g = f, ._b = f });
        }
    }

    tv.flushGraphics();
}

}  // namespace unnes
