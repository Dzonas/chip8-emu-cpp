# CHIP-8 emulator written in C++
This is my toy project - a CHIP-8 emulator. Work in progress.

![main window](https://github.com/Dzonas/chip8-emu-cpp/blob/master/screenshots/main_window.png)

# Requirements
- C++17 compiler/standard library 
- CMake >= 3.13
- SDL2

# Building
In project root directory:
```
mkdir build
cd build
cmake ..
cmake --build . --target chip8_emu_cpp
```

# Running
In project root directory:
```
build/src/chip8_emu_cpp <ROM_NAME>
```
where ROM_NAME is name of the file to run in the resources/roms directory.

# TODO
- [ ] Improve argument handling
- [x] Configuration file (resolution, keymap etc.)
- [x] Sound
- [ ] Documentation
- [ ] Tests

# Reference
1. <http://mattmik.com/files/chip8/mastering/chip8.html>
2. <http://devernay.free.fr/hacks/chip8/C8TECH10.HTM>
3. <https://github.com/tomdaley92/kiwi-8/issues/9>
4. <https://www.zophar.net/pdroms/chip8/chip-8-games-pack.html>
