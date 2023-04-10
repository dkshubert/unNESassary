# unNESassary
Yet another NES emulator, using modern C++. This is a project started purely for fun, with the aim of crossing off two childhood/teenage dreams from my bucket list:

- Writing an emulator
- Beating Ninja Gaiden

I figured if I could beat Ninja Gaiden with an emulator I'd written myself, that would really be doing a suplex to those longstanding feelings of gaming inadequacy.

## Requirements

The following system dependencies are currently required to build this project:

- Docker

If you can run `docker run hello-world` and you see the expected `Hello from Docker!` output, you should be ready to build!

**NOTE:** Currently I'm only using GNU tools and testing on Linux and Windows Subsystem for Linux 2 (WSL2), though I plan on making it easier to build for other platforms. I'm not writing any platform specific code; GLFW is doing most of the hard work in this department, as it's doing the grunt work of creating windows and drawing graphics, all safely tucked behind generic abstractions.

## Building

There's a bunch of helper scripts in the [tools](./tools) directory to assist in building, formatting, documentation generation, etc. `build.sh` is a good one to run a quick, incremental build.

```bash
./tools/build.sh
```

## General Design Philosophy

These are my primary concerns when making any change to this project:

- Emulation fidelity will be improved.
- Performance will be improved, at no cost to emulation fidelity.
- Code safety or correctness can be improved. By "safety", I mean specifically...
  - memory safety
  - type safety
  - elimination of undefined behavior
  - thread safety (this is a single threaded app, but interactions with system HW still results in some parallelism)
- Portability can be improved
- The C++ Core Guidelines suggests an alternative approach.
- Code can be simplified, keeping with the conditions above.
- Code readability/understandability can be increased, keeping with the conditions above.

Any feedback that furthers any of the above goals is appreciated!

## Current Project Status

I'm still very much in the scaffolding stage of this project. Nothing works, and I'm just getting started loading ROMs. There's a list of [TODOs](./TODOs.md) that I'm keeping active until I get basic emulation working, at which point I plan on cutting over to the github issue tracker and getting more methodical about the individual bugs as they arise. Currently, however, the project is in such a state of newness that being overly formal about issue tracking seems like a waste of time.
