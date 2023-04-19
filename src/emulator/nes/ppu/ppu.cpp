#include "ppu.h"

#include <fmt/core.h>

#include <cassert>
#include <span>
#include <thread>

#include "cartridge.h"
#include "logger.h"
#include "tv.h"

namespace unnes
{

namespace test
{

// Add some helper functions to render pattern tables directly from character ROM.

void renderTileScanline(std::span<std::byte> chrom, TV& tv, Logger& logger);
void renderTile(std::span<std::byte> chrom, TV& tv, Logger& logger);
void renderTilesheet(std::span<std::byte> chrom, TV& tv, Logger& logger);

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
    test::renderTilesheet( _cartridge->getChrRom(), _tv, _logger);
}

bool PPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO : really handle a clock tick.

    return true;
}

void test::renderTileScanline(std::span<std::byte> chrom, TV& tv, Logger& logger)
{
    const std::byte left { chrom[0] };
    const std::byte right { chrom[8] };

    for (int pixelIndex { 7 }; pixelIndex >= 0; pixelIndex--) {
        // TODO: For sure this can be done more efficiently.
        static constexpr std::byte bit { 0b00000001 };
        const std::byte mask { bit << pixelIndex };
        const std::byte pixelLeft { (mask & left) >> pixelIndex };
        const std::byte pixelRight { (mask & right) >> pixelIndex };
        const std::byte pixel { (pixelLeft << 1) | pixelRight };

        logger.write(LogLevel::trace,
                        fmt::format("left: {}, right: {}, pixel: {}", left, right, pixel));
        const float f { static_cast<int>(pixel) / 3.0f };
        tv.incrementScanline({ ._r = f, ._g = f, ._b = f });
    }
}

void test::renderTile(std::span<std::byte> chrom, TV& tv, Logger& logger)
{
    for (size_t byteIndex { 0 }; byteIndex < 8; byteIndex++) {
        renderTileScanline(chrom.subspan(byteIndex), tv, logger);
    }

    tv.flushGraphics();
}

void test::renderTilesheet(std::span<std::byte> chrom, TV& tv, Logger& logger)
{
    for (size_t tileRow { 0 }; tileRow < 30; tileRow++) {
        for (size_t pixelRow { 0 }; pixelRow < 8; pixelRow++) {
            for (size_t pixelColumn { 0 }; pixelColumn < 32; pixelColumn++) {
                renderTileScanline(chrom.subspan(tileRow * 16 * 32 + pixelColumn * 16 + pixelRow), tv, logger);
            }
        }
    }

    tv.flushGraphics();
}

}  // namespace unnes
