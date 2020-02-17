#ifndef CHIP8_EMU_CPP_CPU_HPP
#define CHIP8_EMU_CPP_CPU_HPP

#include <array>
#include <vector>
#include <stdexcept>

namespace Chip8 {
const unsigned int MEMORY_SIZE = 4096;
const unsigned int N_REGISTERS = 16;
const unsigned int STACK_SIZE = 16;
const unsigned int KEYBOARD_SIZE = 16;
const unsigned int FONT_WIDTH = 5;
const unsigned int FONT_CHARACTERS = 16;
const unsigned int SCREEN_WIDTH = 64;
const unsigned int SCREEN_HEIGHT = 32;
const unsigned int PC_INIT = 0x200;
const double TIMER_PERIOD = 1.0 / 60.0; // 1 / Hz

const std::array<unsigned char, FONT_WIDTH * FONT_CHARACTERS> FONTS = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10, 0xF0, 0x80, 0xF0, 0xF0,
        0x10, 0xF0, 0x10, 0xF0, 0x90, 0x90, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80,
        0xF0, 0x90, 0xF0, 0xF0, 0x10, 0x20, 0x40, 0x40, 0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0,
        0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0, 0xF0, 0x80, 0x80, 0x80,
        0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80, 0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80,
};

/**
 * It's CPU obviously
 */
class CPU {
  friend class Instruction; // Friend class containing instruction functions

  std::array<unsigned char, MEMORY_SIZE> mem = {0};
  std::array<unsigned char, N_REGISTERS> reg = {0};
  std::array<unsigned short, STACK_SIZE> stack = {0};
  std::array<bool, KEYBOARD_SIZE> keyboard = {false};
  std::array<bool, SCREEN_WIDTH * SCREEN_HEIGHT> display = {false};

  unsigned short PC = PC_INIT; // program counter
  unsigned short I = 0; // index pointer

  unsigned char DT = 0; // delay timer
  unsigned char ST = 0; // sound timer
  unsigned char SP = 0; // stack pointer

  unsigned short get_opcode();
  void execute(unsigned short opcode);

public:
  bool load_store_quirk;
  bool shift_quirk;
  bool wrapping;

  explicit CPU(bool load_store_quirk = false, bool shift_quirk = false, bool wrapping = true);
  void load_rom(const std::vector<unsigned char> &rom);
  void cycle();
  void update_timers();
  bool &key(unsigned int id);
  const std::array<bool, SCREEN_WIDTH * SCREEN_HEIGHT> &get_display();
  unsigned char sound_timer() const { return ST; }
};
}

#endif //CHIP8_EMU_CPP_CPU_HPP
