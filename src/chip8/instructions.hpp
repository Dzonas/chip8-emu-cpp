#ifndef CHIP8_EMU_CPP_INSTRUCTIONS_HPP
#define CHIP8_EMU_CPP_INSTRUCTIONS_HPP

#include "cpu.hpp"

namespace Chip8 {
    class Instruction {
    public:
        static void i_0000(Chip8::CPU& cpu, unsigned short opcode);
        static void i_00E0(Chip8::CPU& cpu, unsigned short opcode);
        static void i_00EE(Chip8::CPU& cpu, unsigned short opcode);
        static void i_1nnn(Chip8::CPU& cpu, unsigned short opcode);
        static void i_2nnn(Chip8::CPU& cpu, unsigned short opcode);
        static void i_3xkk(Chip8::CPU& cpu, unsigned short opcode);
        static void i_4xkk(Chip8::CPU& cpu, unsigned short opcode);
        static void i_5xy0(Chip8::CPU& cpu, unsigned short opcode);
        static void i_6xkk(Chip8::CPU& cpu, unsigned short opcode);
        static void i_7xkk(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy0(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy1(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy2(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy3(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy4(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy5(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy6(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xy7(Chip8::CPU& cpu, unsigned short opcode);
        static void i_8xyE(Chip8::CPU& cpu, unsigned short opcode);
        static void i_9xy0(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Annn(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Bnnn(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Cxkk(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Dxyn(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Ex9E(Chip8::CPU& cpu, unsigned short opcode);
        static void i_ExA1(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx07(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx0A(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx15(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx18(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx1E(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx29(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx33(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx55(Chip8::CPU& cpu, unsigned short opcode);
        static void i_Fx65(Chip8::CPU& cpu, unsigned short opcode);
    };
}

#endif //CHIP8_EMU_CPP_INSTRUCTIONS_HPP
