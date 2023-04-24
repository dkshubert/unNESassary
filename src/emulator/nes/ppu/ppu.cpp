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

void renderTileScanline(std::span<std::byte> chrom, TV& tv);
void renderTile(std::span<std::byte> chrom, TV& tv);
void renderTilesheet(std::span<std::byte> chrom, TV& tv);

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
}

bool PPU::handleClockTick(std::uint64_t tickNum)
{
    _logger.write(LogLevel::trace, fmt::format("handling tickNum: {}", tickNum));

    // TODO : delete this test code
    test::renderTilesheet(_cartridge->getChrRom(), _tv);

    // TODO : really handle a clock tick.

    return true;
}

void test::renderTileScanline(std::span<std::byte> chrom, TV& tv)
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
        const float f { static_cast<int>(pixel) / 3.0f };

        tv.incrementScanline({ ._r = f, ._g = f, ._b = f });
    }
}

void test::renderTile(std::span<std::byte> chrom, TV& tv)
{
    for (size_t byteIndex { 0 }; byteIndex < 8; byteIndex++) {
        renderTileScanline(chrom.subspan(byteIndex), tv);
    }

    tv.flushGraphics();
}

void test::renderTilesheet(std::span<std::byte> chrom, TV& tv)
{
    for (size_t tileRow { 0 }; tileRow < 30; tileRow++) {
        for (size_t pixelRow { 0 }; pixelRow < 8; pixelRow++) {
            for (size_t pixelColumn { 0 }; pixelColumn < 32; pixelColumn++) {
                renderTileScanline(chrom.subspan(tileRow * 16 * 32 + pixelColumn * 16 + pixelRow),
                                   tv);
            }
        }
    }
}

}  // namespace unnes
