# Tasks

This is not comprehensive. I'm in the midst of a new-project flurry of doing a million tasks, so this list is going to be missing items for sure. Ranked in terms of priority, from highest to lowest priority, this is the set of tasks I'll be working in upcoming contributions:

- Finish opengl scanline renderer
- Create a stdout scanline renderer, to improve the design
- Add unit tests
- Implement cartridge ROM file loading
- Add a conf file that controls
  - window size
  - controller mappings + hotkeys
  - log level
  - last played ROM
- Figure out how to actually produce a debug build and make conan's dependencies still resolve correctly
- Support windows and mac builds
- Cleanup TODOs

## Stretch features

These features are for way in the future, after the basic emulation is set up and working decently well:

- Cloud save state + user config
- Tool Assisted Run (TAS) helpers for speed runners
  - Cloud saves of TAS runs, with user voting
  - Elegant replay viewers/editors
- Game Genie cheat code creator
  - Cloud saves of cheats for each ROM, with user voting
- cloud ROM hub for user created ROMs , with user voting
- stdout rendering of NES, and other goofy effects, like color palette hacking