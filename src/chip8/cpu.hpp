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
 * \brief Represents Chip8's "CPU"
 */
class CPU {
  /** \brief Friend class containing all instructions for Chip8. */
  friend class Instruction;

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

  /**
   * \brief Gets opcode for current cycle.
   *
   * Merges two 8-bit numbers to create 16-bit opcode. More significant part is at the PC address and less significant
   * is at PC + 1 address. If PC or PC+1 point outside of memory runtime error is thrown.
   *
   * @return 16-bit opcode
   */
  unsigned short get_opcode();

  /**
   * \brief Execute given opcode.
   *
   * Matches instruction for given opcode and immediately executes it. Throws runtime error when given opcode
   * is unknown. Some of the instructions may throw runtime errors. Available instructions are in Chip8::Instruction
   * class.
   *
   * @param opcode 16-bit unsigned number
   */
  void execute(unsigned short opcode);

public:
  /** \brief Load store quirk flag. When set uses quirked behavior of instructions Fx55 and Fx65. */
  bool load_store_quirk;
  /** \brief Shift quirk flag. When set uses quirked behavior of instructions 8xy6 and 8xyE. */
  bool shift_quirk;
  /** \brief Wrapping flag. When set pixels outside of the screen are wrapped around to show on the screen.*/
  bool wrapping;

  /**
   * \brief Initializes CPU.
   *
   * Apart from setting fields to initial values, copies over font data required for some roms.
   *
   * @param load_store_quirk initial load store quirk flag
   * @param shift_quirk initial shift quirk flag
   * @param wrapping initial wrapping flag
   */
  explicit CPU(bool load_store_quirk = false, bool shift_quirk = false, bool wrapping = true);

  /**
   * \brief Load rom into the memory.
   *
   * Copies rom into memory starting at address 0x200. Addresses in range 0x000 to 0x1FF are reserved. Throws
   * runtime error if rom won't fit into memory.
   *
   * @param rom array of 8-bit numbers representing a rom
   */
  void load_rom(const std::vector<unsigned char> &rom);

  /**
   * \brief Executes one cpu cycle.
   *
   * CPU's cycle consists of: reading two bytes from memory, merging them to get opcode, matching instruction to
   * this opcode and executing matched instruction.
   *
   * \note This method should be run at chosen frequency e.g. to ensure proper gameplay for a given rom.
   *
   * \warning This method doesn't update delay and sound timers, which should be run at 60 Hz always.
   */
  void cycle();

  /**
   * \brief Updates values of delay and sound timers.
   *
   * Decrements values in DT and ST registers until they reach 0. This method expects to be run at 60 Hz, because
   * ST and DT registers are used for time measurement and sound playing.
   *
   * \note This method is supposed to be called always at 60 Hz no matter the frequency at which the CPU is run.
   */
  void update_timers();

  /**
   * \brief Get/Set key.
   *
   * Returns a reference to bool telling if key is pressed or not. Id parameter represents key number. Chip8 has
   * 16-key keyboard that means id must be in range 0-15 inclusive.
   *
   * @param id value in range 0-15 inclusive
   * @return is key pressed
   */
  bool &key(unsigned int id);

  /**
   * \brief Get reference to display.
   *
   * Returns const reference to a array representing Chip8's display. Each value in the array represents a pixel
   * starting from top-left corner. If value of a pixel is true it means it is on, otherwise it's off.
   *
   * @return Reference to array representing the display.
   */
  const std::array<bool, SCREEN_WIDTH * SCREEN_HEIGHT> &get_display();

  /**
   * Get sound timer value.
   *
   * @return Value stored in ST register.
   */
  unsigned char sound_timer() const { return ST; }
};
}

#endif //CHIP8_EMU_CPP_CPU_HPP
