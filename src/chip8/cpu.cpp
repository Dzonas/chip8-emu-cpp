#include <algorithm>
#include "cpu.hpp"
#include "instructions.hpp"

unsigned short Chip8::CPU::get_opcode() {
  try {
	unsigned short big = mem.at(PC);
	unsigned short small = mem.at(PC + 1);

	return (big << 8u) + small;
  } catch (const std::out_of_range &e) {
	throw std::runtime_error("tried to access out of memory");
  }
}

void Chip8::CPU::cycle() {
  unsigned short opcode = get_opcode();
  execute(opcode);
}

using FP = void(Chip8::CPU &, unsigned short);

void Chip8::CPU::execute(unsigned short opcode) {
  FP *fp = nullptr;

  switch ((opcode & 0xF000u) >> 12u) {
  case 0x0: {
	switch (opcode) {
	case 0x0000:fp = Instruction::i_0000;
	  break;
	case 0x00E0:fp = Instruction::i_00E0;
	  break;
	case 0x00EE:fp = Instruction::i_00EE;
	  break;
	default:break;
	}
	break;
  }
  case 0x1:fp = Instruction::i_1nnn;
	break;
  case 0x2:fp = Instruction::i_2nnn;
	break;
  case 0x3:fp = Instruction::i_3xkk;
	break;
  case 0x4:fp = Instruction::i_4xkk;
	break;
  case 0x5: {
	switch (opcode & 0x000Fu) {
	case 0x0:fp = Instruction::i_5xy0;
	  break;
	default:break;
	}
	break;
  }
  case 0x6:fp = Instruction::i_6xkk;
	break;
  case 0x7:fp = Instruction::i_7xkk;
	break;
  case 0x8: {
	switch (opcode & 0x000Fu) {
	case 0x0:fp = Instruction::i_8xy0;
	  break;
	case 0x1:fp = Instruction::i_8xy1;
	  break;
	case 0x2:fp = Instruction::i_8xy2;
	  break;
	case 0x3:fp = Instruction::i_8xy3;
	  break;
	case 0x4:fp = Instruction::i_8xy4;
	  break;
	case 0x5:fp = Instruction::i_8xy5;
	  break;
	case 0x6:fp = Instruction::i_8xy6;
	  break;
	case 0x7:fp = Instruction::i_8xy7;
	  break;
	case 0xE:fp = Instruction::i_8xyE;
	  break;
	default:break;
	}
	break;
  }
  case 0x9:fp = Instruction::i_9xy0;
	break;
  case 0xA:fp = Instruction::i_Annn;
	break;
  case 0xB:fp = Instruction::i_Bnnn;
	break;
  case 0xC:fp = Instruction::i_Cxkk;
	break;
  case 0xD:fp = Instruction::i_Dxyn;
	break;
  case 0xE: {
	switch (opcode & 0x00FFu) {
	case 0x9E:fp = Instruction::i_Ex9E;
	  break;
	case 0xA1:fp = Instruction::i_ExA1;
	  break;
	default:break;
	}
	break;
  }
  case 0xF: {
	switch (opcode & 0x00FFu) {
	case 0x07:fp = Instruction::i_Fx07;
	  break;
	case 0x0A:fp = Instruction::i_Fx0A;
	  break;
	case 0x15:fp = Instruction::i_Fx15;
	  break;
	case 0x18:fp = Instruction::i_Fx18;
	  break;
	case 0x1E:fp = Instruction::i_Fx1E;
	  break;
	case 0x29:fp = Instruction::i_Fx29;
	  break;
	case 0x33:fp = Instruction::i_Fx33;
	  break;
	case 0x55:fp = Instruction::i_Fx55;
	  break;
	case 0x65:fp = Instruction::i_Fx65;
	  break;
	default:break;
	}
	break;
  }
  default:break;
  }

  if (fp)
	fp(*this, opcode);
  else
	throw std::runtime_error(&"unknown opcode "[opcode]);
}

void Chip8::CPU::load_rom(const std::vector<unsigned char> &rom) {
  if (rom.size() >= MEMORY_SIZE - 0x200) {
	throw std::runtime_error("rom size is too large");
  } else {
	std::copy(rom.begin(), rom.end(), mem.begin() + 0x200);
  }
}

void Chip8::CPU::update_timers() {
  if (DT > 0)
	DT -= 1;
  if (ST > 0)
	ST -= 1;
}

bool &Chip8::CPU::key(unsigned int id) {
  if (id >= 16)
	throw std::runtime_error("no such key");

  return keyboard[id];
}

const std::array<bool, Chip8::SCREEN_WIDTH * Chip8::SCREEN_HEIGHT> &Chip8::CPU::get_display() {
  return display;
}

Chip8::CPU::CPU(bool load_store_quirk, bool shift_quirk, bool wrapping) :
	load_store_quirk(load_store_quirk), shift_quirk(shift_quirk), wrapping(wrapping) {
  std::copy(Chip8::FONTS.cbegin(), Chip8::FONTS.cend(), mem.begin());
}
