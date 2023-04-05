#pragma once

#include <memory>

#include "apu.h"
#include "cartridge.h"
#include "cpu.h"
#include "electronic_device.h"
#include "ppu.h"
#include "ram.h"
#include "rom.h"

namespace unnes
{

class Clock;
class Logger;

/// @brief The NES emulator! This class contains all NES hardware components,
class NES : public IElectronicDevice
{
    Logger& _logger;
    Clock _clock;
    CPU _cpu;
    PPU _ppu;
    APU _apu;
    RAM _ram;
    ROM _rom;
    std::unique_ptr<Cartridge> _cartridge { nullptr };

public:
    NES(Logger& logger);

    /// @brief Inserts a cartridge into the NES.
    ///
    /// @param romPath The path the ".nes" ROM in the filesystem.
    /// @return True if the cart was successfully inserted (the ROM loaded), false otherwise.
    [[nodiscard]] bool insertCart(const std::string_view romPath);
    void ejectCart();

    void turnOn() override;
    void turnOff() override;
    [[nodiscard]] bool isOn() const override;
    [[nodiscard]] bool update(double time) override;
};

}  // namespace unnes
