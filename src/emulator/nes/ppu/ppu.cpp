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

/// TODO : use spans for these

void renderTileScanline(std::uint8_t* chrom, TV& tv, Logger& logger);

void renderTile(std::uint8_t* chrom, TV& tv, Logger& logger);

void renderTilesheet(std::uint8_t* chrom, TV& tv, Logger& logger);

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

    // TODO : delete this test code
    test::renderTilesheet(_cartridge->getChrRom().data(), _tv, _logger);
}

bool PPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO : really handle a clock tick.

    return true;
}

void test::renderTileScanline(std::uint8_t* chrom, TV& tv, Logger& logger)
{
    const std::uint8_t left = chrom[0];
    const std::uint8_t right = chrom[8];

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

void test::renderTile(std::uint8_t* chrom, TV& tv, Logger& logger)
{
    for (size_t byteIndex = 0; byteIndex < 8; byteIndex++) {
        renderTileScanline(chrom + byteIndex, tv, logger);
    }

    tv.flushGraphics();
}

void test::renderTilesheet(std::uint8_t* chrom, TV& tv, Logger& logger)
{
    for (int tileRow = 0; tileRow < 30; tileRow++) {
        for (int pixelRow = 0; pixelRow < 8; pixelRow++) {
            for (size_t pixelColumn = 0; pixelColumn < 32; pixelColumn++) {
                renderTileScanline(chrom + tileRow * 16 * 32 + pixelColumn * 16 + pixelRow, tv, logger);
            }
            // tv.forceNextScanline();
        }
    }

    tv.flushGraphics();
}

}  // namespace unnes
