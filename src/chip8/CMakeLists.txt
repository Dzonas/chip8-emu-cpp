add_library(chip8_lib STATIC cpu.cpp cpu.hpp instructions.cpp instructions.hpp)
target_include_directories(chip8_lib PUBLIC ./)