# GeeBEmu: Gameboy emulator

This project tries to create an emulator for the original Nintendo Gameboy system.
It is written entirely in C, using Raylib to handle I/O.

## Building

The following dependencies will be needed:

- CMake v >= 3.22
- Any C compiler (gcc or clang are fine)

To compile the project, simply run the following commands:

```sh
cmake -S . -B build
cmake --build build --config Release
```

The project will be built in `build/bin`

## Todo

- CPU stuff
  - Implement all the opcodes
  - Finish Fetch / Decode / Execute cycle
  - Implement special flags like HALT
- Load cartridge
  - Power-Up sequence
- Graphics
  - Implement video functionality
- Audio

May add more in the future.
