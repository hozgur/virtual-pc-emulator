# Virtual PC Emulator

This project is a **virtual PC emulator** built on a simple 32-bit register and 24-bit addressing CPU. It includes basic system components such as memory mapping, I/O registers, and video output.

## 📦 Contents

- `emulator.h`: CPU and messaging structure
- `memory_map.h`: Memory and I/O address definitions
- `video_controller.c`: Text-mode video memory and terminal output
- `call_ret_example.c`: Program loader demonstrating CALL & RET instructions
- `main.c`: Main function that starts the program
- `CMakeLists.txt`: CMake configuration for building

## 🔧 Build Instructions

```bash
mkdir build
cd build
cmake ..
make
./virtual_pc
```

> You need `gcc` and `cmake` installed to build.

## 🎮 Video Memory

The text-mode video RAM is 80x25 in size. The `video_render_text_terminal()` function prints the contents to the terminal.

## 💻 Example Program

`call_ret_example.c` performs the following operations:

- Loads `10` into register A
- Calls a subroutine
- The subroutine adds `Z` to `A` (`Z = 5`)
- Returns with the `RET` instruction
- Stops the processor with the `HLT` instruction

Output:
```
Program is running...
Program ended. A = 15
```

---

© 2025 Hakan Özgür. All rights reserved.
