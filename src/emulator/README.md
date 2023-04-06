# Design Notes

The subfolders in this `emulator` directory each represent the distinct physical objects which which a gamer would interact. Specifically, a gamer puts a `cartridge` in an `nes` system, and turns on the `tv`, which align with the folders in this directory. There's a bit of a philisophical question whether or not the cartridge is part of the NES system itself when it's plugged in, especially considering that the cartridge does things like extend the RAM of the NES, implying that, while they're connected, they form a single system.

Since the NES and cartridge are designed to be able to be physically separated, however, I decided to separate their source files into separate folders, to as closely draw boundaries to the real world as possible.

The `IEmulatedDevice` interface is the common glue between these disparate physical consumer electronic devices, with each device implementing the interface.