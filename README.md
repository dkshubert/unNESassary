# unNESassary
Yet another NES emulator. This is a project started purely for fun to cross off two childhood/teenage dreams off of my bucket list:

- Writing an emulator
- Beating Ninja Gaiden

I figured if I could beat Ninja Gaiden with an emulator I'd written myself, that would really be doing a suplex to those longstanding feelings of gaming inadequacy.

## Requirements

The following system dependencies are currently required to build this project:

- CMake
- conan
- openGL
- clang-format
- doxygen

Currently I'm only using GNU tools and testing on Linux, though I plan on making it easier to build for other platforms. I'm not writing any platform specific code; GLFW is doing most of the hard work in this department, as it's doing the grunt work of creating windows and drawing graphics, all safely tucked behind generic abstractions.

## Building

There's a bunch of helper scripts in the [tools](./tools) directory to assist in building. `build.sh` is a good one to run a quick, incremental build (assuming you have the above list of requirements installed).

```bash
./tools/build.sh
```

If you haven't used conan before, you might see an error like this:

> ERROR: The default build profile '~/.conan2/profiles/default' doesn't exist.

This can be fixed by running...

```bash
conan profile detect
```

There's also a vaguely named (but convenient) `everything.sh` script that I've been using to do a complete code formatting, build, documentation generation, application test run to rapidly test changes.

## Current Project Status

I'm still very much in the scaffolding stage of this project. Nothing works, and I'm just getting started loading ROMs. There's a list of [TODOs](./TODOs.md) that I'm keeping active until I get basic emulation working, at which point I plan on cutting over to the github issue tracker and getting more methodical about the individual bugs as they arise. Currently, however, the project is in such a state of newness that being overly formal about issue tracking seems like a waste of time.
