#ifndef CHIP8_EMU_CPP_INSTRUCTIONS_HPP
#define CHIP8_EMU_CPP_INSTRUCTIONS_HPP

#include "cpu.hpp"

namespace Chip8 {
/**
 * \brief Class representing available instructions in Chip8's "CPU".
 *
 * Each opcode represents one instruction performed by the CPU. This class contains all of the available instructions
 * for Chip8.
 */
class Instruction {
public:
  /**
   * \brief No operation.
   *
   * Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_0000(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Clear display.
   *
   * Sets all "pixels" to false. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_00E0(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Return from subroutine.
   *
   * Subtracts 1 from stack pointer, then sets program counter to value at the top of the stack + 2.
   * Throws runtime error when stack pointer is equal to 0.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_00EE(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Jump to address nnn.
   *
   * Sets program counter to nnn.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_1nnn(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Call a subroutine at nnn.
   *
   * Puts program counter at the top of the stack, then increments stack pointer. Program counter is then set to nnn.
   * Throws runtime error when stack pointer's value is larger than stack size.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_2nnn(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Skip next instruction if Vx==kk.
   *
   * If value in register x is equal to value kk then program counter is incremented 4 times, otherwise 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_3xkk(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Skip next instruction if Vx!=kk.
   *
   * If value in register x is not equal to value kk then program counter is incremented 4 times, otherwise 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_4xkk(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Skip next instruction if Vx==Vy.
   *
   * If value in register x is equal to value in register y then program counter is incremented 4 times,
   * otherwise 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_5xy0(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to kk.
   *
   * Value in register x is set to kk. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_6xkk(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Add Vx to kk.
   *
   * Adds value in register x to value kk. Result is stored in register x. Program counter is incremented
   * 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_7xkk(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to Vy.
   *
   * Value in register x is set to value in register y. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy0(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to bitwise OR on Vx and Vy.
   *
   * Performs bitwise OR on values in register x and y, then result is stored in register x. Program counter is
   * incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy1(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to bitwise AND on Vx and Vy.
   *
   * Performs bitwise AND on values in register x and y, then result is stored in register x.  Program counter is
   * incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy2(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to bitwise XOR on Vx and Vy.
   *
   * Performs bitwise XOR on values in register x and y, then result is stored in register x.  Program counter is
   * incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy3(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to Vx + Vy.
   *
   * Adds value in register x to value in register y with wrapping. Result is stored in register x. If addition
   * overflowed, then register 0xF is set to 1, otherwise 0. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy4(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to Vx - Vy.
   *
   * Subtracts value in register vy from value in register x. Result is stored in register x. If subtraction
   * required borrow, then register 0xF is set to 0, otherwise 1. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy5(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Shifts right value in either Vx or Vy.
   *
   * Non-quirked behavior:
   * Shifts right by 1 a value in register y and then it is stored in register x. Register 0xF is set to least
   * significant bit of register y before the shift (either 0 or 1).
   *
   * Quirked behavior:
   * Shifts right by 1 a value in register x and then it is stored in register x. Register 0xF is set to least
   * significant bit of register y before the shift (either 0 or 1).
   *
   * In both cases program counter is incremented 2 times.
   *
   * \warning Behavior of this instruction depends on cpu's shift quirk flag.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy6(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set Vx to Vy - Vx.
   *
   * Subtracts value in register x from value in register y. Result is stored in register x. If subtraction
   * required borrow, then register 0xF is set to 0, otherwise 1. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xy7(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Shifts left value in either Vx or Vy.
   *
   * Non-quirked behavior:
   * Shifts left by 1 a value in register y and then it is stored in register x. Register 0xF is set to most
   * significant bit of register y before the shift (either 0 or 1).
   *
   * Quirked behavior:
   * Shifts left by 1 a value in register x and then it is stored in register x. Register 0xF is set to most
   * significant bit of register y before the shift (either 0 or 1).
   *
   * In both cases program counter is incremented 2 times.
   *
   * \warning Behavior of this instruction depends on cpu's shift quirk flag.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_8xyE(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Skip next instruction if Vx!=Vy.
   *
   * If value in register x is not equal to value in register y, then program counter is incremented 4 times, otherwise
   * 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_9xy0(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Set I to nnn.
   *
   * The value in register I is set to value nnn. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_Annn(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Jump to nnn + V0.
   *
   * Program counter is set to destination address given by the sum of a value nnn and a value in 0x0 register.
   * Throws runtime error when program counter points outside of memory (value too large).
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_Bnnn(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Setx Vx to RND AND kk
   *
   * Random number in range 0-255 inclusive is generated, which is bitwise AND'ed with value kk. Result is stored
   * in register x. Program counter is incremented 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_Cxkk(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Draws n-row sprite at location (x, y) on the screen.
   *
   * 8-pixel wide and n pixels long sprite is drawn at location (x, y) on the screen. (x, y) coordinates represent
   * top left corner of the sprite. Each pixel of the sprite is XOR'ed with the pixel already on the
   * screen at the same location. After the draw operation, if any of the previous pixels was on and current pixel
   * is off the flag in the 0xF register is set to 1. Otherwise it is set to 0. If wrapping flag is set, then pixels
   * which are supposed to be drawn outside of the display are wrapped around. Otherwise they aren't drawn at all.
   * Program counter is incremented 2 times.
   *
   * \note Behavior of this function depends on cpu's wrapping flag.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_Dxyn(Chip8::CPU &cpu, unsigned short opcode);

  /**
   * \brief Skip next instruction if key Vx is pressed.
   *
   * Status of a key, which number is stored in x register, is read. If key is pressed then program counter is
   * incremented 4 times, otherwise 2 times.
   *
   * @param cpu instance on which the instruction will be executed
   * @param opcode 16-bit number representing instruction code
   */
  static void i_Ex9E(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Skip next instruction if key Vx is not pressed.
  *
  * Status of a key, which number is stored in x register, is read. If key is not pressed then program counter is
  * incremented 4 times, otherwise 2 times.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_ExA1(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Set Vx to DT.
  *
  * Value in register x is set to value in delay timer. Program counter is incremented 2 times.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx07(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Wait for keypress and store pressed key in Vx.
  *
  * Polls each key and checks if any of them is pressed. If so, pressed key number is stored in x register and
  * program counter is incremented 2 times. Otherwise program counter is not incremented, which means that this
  * instruction will block until any key is pressed.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx0A(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Set DT to Vx.
  *
  * Value in delay timer register is set to value in x register. Program counter is incremented 2 times.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx15(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Set ST to Vx.
  *
  * Value in sound timer register is set to value in x register. Program counter is incremented 2 times.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx18(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Add I to Vx.
  *
  * Adds value in I register to value in x register. Result is stored in I register. Program counter is incremented
  * 2 times.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx1E(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Set I to location of sprite in Vx.
  *
  * Value in I register is set to location of a sprite representing a hexadecimal digit stored in x register. Program
  * counter is incremented 2 times. Throws runtime error if x register doesn't contain valid hexadecimal digit.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx29(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Convert Vx to BCD.
  *
  * Converts value in register x to BCD representation and stores it at locations: I, I+1, I+2. Program counter
  * is incremented 2 times.Throws runtime error if tries to save number outside of memory.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx33(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Store registers V0 through VF starting at address I.
  *
  * Each value in registers 0x0 to 0xF are stored at addresses I through I+0xF. If load store flag is not set, then
  * value in I register is set to address I + 0xF + 0x1, otherwise it is not changed. Program counter is incremented
  * 2 times. Throws runtime error if tries to save number outside of memory.
  *
  * \warning Behavior of this instruction depends on cpu's load store quirk flag.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx55(Chip8::CPU &cpu, unsigned short opcode);

  /**
  * \brief Read registers V0 through VF starting at address I.
  *
  * Each value in registers 0x0 to 0xF are set to values at addresses I through I+0xF. If load store flag is not set,
  * then value in I register is set to address I + 0xF + 0x1, otherwise it is not changed. Program counter is incremented
  * 2 times. Throws runtime error if tries to save number outside of memory.
  *
  * \warning Behavior of this instruction depends on cpu's load store quirk flag.
  *
  * @param cpu instance on which the instruction will be executed
  * @param opcode 16-bit number representing instruction code
  */
  static void i_Fx65(Chip8::CPU &cpu, unsigned short opcode);
};
}

#endif //CHIP8_EMU_CPP_INSTRUCTIONS_HPP
