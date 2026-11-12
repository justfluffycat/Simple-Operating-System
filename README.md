# Operating System Emulator in C

A minimalist terminal-based emulator replicating Steve Wozniak's legendary **Woz Monitor** for the Apple-I.

## How to compile & run

Open your terminal or command prompt in the directory containing `system_emu.c` and run:

### Linux / macOS (GCC)
```bash
gcc system_emu.c -o system_emu
./system_emu
```

### Windows (MinGW/GCC)
```bash
gcc system_emu.c -o system_emu.exe
system_emu.exe
```

## Quick Command Guide
Once running (\ prompt):
- Inspect Memory (.):0300. (View bytes starting at 0300)
- Modify Memory (:):0300: A9 00 8D 00 02 (Write hex values)
- Run Program (R):0300R (Simulate execution)
- Exit: Type EXIT
