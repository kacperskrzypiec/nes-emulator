# NES Emulator 🎮

An NES emulator written in C++ using SDL3, developed for my thesis project.

## Build 🔨
```
> git clone https://github.com/kacperskrzypiec/nes-emulator.git
> cd nes-emulator
> mkdir build
> cd build
> cmake .. -G "Ninja" -DPRODUCTION_BUILD=ON -DCMAKE_BUILD_TYPE=Release
> cmake --build .
```

To build the project using Visual Studio, simply open the cloned repository in it. I've included the `CMakeSettings.json` file with the necessary build configurations.

## Status 📝
Implementing the instruction decoder.

## Roadmap 🚀
- 🟨 CPU implementation
- ⬜ Cartridge loading (iNES format)
- ⬜ Mappers 0 and 1
- ⬜ PPU implementation
- ⬜ Keyboard and game controller input
- ⬜ Mapper 4 and possibly more
- ⬜ APU implementation
- ⬜ Pause, save and load state

## Sources 📚

- [NESdev](https://www.nesdev.org/wiki/NES_reference_guide)
- [NES / Famicom Architecture - A practical analysis by Rodrigo Copetti](https://www.copetti.org/writings/consoles/nes/)
- [6502 Instruction Set](https://www.masswerk.at/6502/6502_instruction_set.html)