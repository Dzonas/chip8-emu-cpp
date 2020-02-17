#include <cstdlib>
#include "instructions.hpp"

void Chip8::Instruction::i_00E0(Chip8::CPU &cpu, [[maybe_unused]] unsigned short opcode) {
  cpu.display = {false};
  cpu.PC += 2;
}

void Chip8::Instruction::i_00EE(Chip8::CPU &cpu, [[maybe_unused]] unsigned short opcode) {
  if (cpu.SP == 0)
	throw std::runtime_error("stack underflow");

  cpu.SP -= 1;
  cpu.PC = static_cast<unsigned short>(cpu.stack[cpu.SP] + 2);
}

void Chip8::Instruction::i_1nnn(Chip8::CPU &cpu, unsigned short opcode) {
  cpu.PC = static_cast<unsigned short>(opcode & 0x0FFFu);
}

void Chip8::Instruction::i_2nnn(Chip8::CPU &cpu, unsigned short opcode) {
  if (cpu.SP > 0xF)
	throw std::runtime_error("stack overflow");

  cpu.stack[cpu.SP] = cpu.PC;
  cpu.SP += 1;
  cpu.PC = static_cast<unsigned short>(opcode & 0x0FFFu);
}

void Chip8::Instruction::i_3xkk(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto k = static_cast<unsigned char>(opcode & 0x00FFu);
  if (cpu.reg[x] == k)
	cpu.PC += 4;
  else
	cpu.PC += 2;
}

void Chip8::Instruction::i_4xkk(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto k = static_cast<unsigned char>(opcode & 0x00FFu);
  if (cpu.reg[x] != k)
	cpu.PC += 4;
  else
	cpu.PC += 2;
}

void Chip8::Instruction::i_5xy0(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);
  if (cpu.reg[x] == cpu.reg[y])
	cpu.PC += 4;
  else
	cpu.PC += 2;
}

void Chip8::Instruction::i_6xkk(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto k = static_cast<unsigned char>(opcode & 0x00FFu);
  cpu.reg[x] = k;
  cpu.PC += 2;
}

void Chip8::Instruction::i_7xkk(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto k = static_cast<unsigned char>(opcode & 0x00FFu);
  cpu.reg[x] += k;
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy0(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  cpu.reg[x] = cpu.reg[y];
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy1(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  cpu.reg[x] |= cpu.reg[y];
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy2(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  cpu.reg[x] &= cpu.reg[y];
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy3(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  cpu.reg[x] ^= cpu.reg[y];
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy4(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  if (cpu.reg[x] > std::numeric_limits<unsigned char>::max() - cpu.reg[y])
	cpu.reg[0xF] = 1;
  else
	cpu.reg[0xF] = 0;

  cpu.reg[x] += cpu.reg[y];
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy5(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  if (cpu.reg[x] >= cpu.reg[y])
	cpu.reg[0xF] = 1;
  else
	cpu.reg[0xF] = 0;

  cpu.reg[x] -= cpu.reg[y];
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy6(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  unsigned short y;

  if (!cpu.shift_quirk)
	y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);
  else
	y = x;

  cpu.reg[0xF] = static_cast<unsigned char>(cpu.reg[y] & 1u);
  cpu.reg[x] = cpu.reg[y] >> 1u;

  cpu.PC += 2;
}

void Chip8::Instruction::i_8xy7(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  if (cpu.reg[y] >= cpu.reg[x])
	cpu.reg[0xF] = 1;
  else
	cpu.reg[0xF] = 0;

  cpu.reg[x] = cpu.reg[y] - cpu.reg[x];
  cpu.PC += 2;
}

void Chip8::Instruction::i_8xyE(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  unsigned short y;

  if (!cpu.shift_quirk)
	y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);
  else
	y = x;

  cpu.reg[0xF] = static_cast<unsigned char>((cpu.reg[y] & 0x80u) >> 7u);
  cpu.reg[x] = cpu.reg[y] << 1u;

  cpu.PC += 2;
}

void Chip8::Instruction::i_9xy0(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned short>((opcode & 0x00F0u) >> 4u);

  if (cpu.reg[x] != cpu.reg[y])
	cpu.PC += 4;
  else
	cpu.PC += 2;
}

void Chip8::Instruction::i_Annn(Chip8::CPU &cpu, unsigned short opcode) {
  cpu.I = static_cast<unsigned short>(opcode & 0x0FFFu);
  cpu.PC += 2;
}

void Chip8::Instruction::i_Bnnn(Chip8::CPU &cpu, unsigned short opcode) {
  auto dest = static_cast<unsigned short>((opcode & 0x0FFFu) + (unsigned short)cpu.reg[0]);
  if (dest >= 4096)
	throw std::runtime_error("tried to access out of memory");

  cpu.PC = dest;
}

void Chip8::Instruction::i_Cxkk(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned short>((opcode & 0x0F00u) >> 8u);
  auto k = static_cast<unsigned char>(opcode & 0x00FFu);
  cpu.reg[x] = static_cast<unsigned char>((static_cast<unsigned int>(std::rand()) % 255u)
	  & k); // NOLINT (in this case using std::rand is fine)
  cpu.PC += 2;
}

void Chip8::Instruction::i_Dxyn(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);
  auto y = static_cast<unsigned char>((opcode & 0x00F0u) >> 4u);
  auto n = static_cast<unsigned char>(opcode & 0x000Fu);

  if (cpu.I + n > Chip8::MEMORY_SIZE)
	throw std::runtime_error("tried to access sprite out of memory");

  unsigned char vf_flag = 0;

  for (unsigned row = 0; row < n; row++) {
	unsigned char sprite_row = cpu.mem[cpu.I + row];
	unsigned ny = cpu.reg[y] + row;

	if (cpu.wrapping)
	  ny %= Chip8::SCREEN_HEIGHT;
	else if (ny >= Chip8::SCREEN_HEIGHT)
	  continue;

	for (unsigned col = 0; col < 8; col++) {
	  unsigned nx = cpu.reg[x] + col;

	  if (cpu.wrapping)
		nx %= Chip8::SCREEN_WIDTH;
	  else if (nx >= Chip8::SCREEN_WIDTH)
		continue;

	  bool pixel = static_cast<bool>((unsigned)(sprite_row >> (7 - col)) & 1u);
	  unsigned pixel_pos = nx + ny * SCREEN_WIDTH;

	  bool prev_pixel = cpu.display[pixel_pos];
	  bool next_pixel = prev_pixel ^pixel;

	  if (prev_pixel && !next_pixel) {
		vf_flag = 1;
	  }

	  cpu.display[pixel_pos] = next_pixel;
	}
  }

  cpu.reg[0xF] = vf_flag;
  cpu.PC += 2;
}

void Chip8::Instruction::i_Ex9E(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);
  if (cpu.keyboard[cpu.reg[x]])
	cpu.PC += 4;
  else
	cpu.PC += 2;
}

void Chip8::Instruction::i_ExA1(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);
  if (!cpu.keyboard[cpu.reg[x]])
	cpu.PC += 4;
  else
	cpu.PC += 2;
}

void Chip8::Instruction::i_Fx07(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);
  cpu.reg[x] = cpu.DT;
  cpu.PC += 2;
}

void Chip8::Instruction::i_Fx0A(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);

  bool key_pressed = false;

  for (auto it = cpu.keyboard.cbegin(); it < cpu.keyboard.cend(); it++) {
	if (*it) {
	  key_pressed = true;
	  cpu.reg[x] = static_cast<unsigned char>(it - cpu.keyboard.cbegin());
	  break;
	}
  }

  if (key_pressed)
	cpu.PC += 2;
}

void Chip8::Instruction::i_Fx15(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);
  cpu.DT = cpu.reg[x];
  cpu.PC += 2;
}

void Chip8::Instruction::i_Fx18(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);
  cpu.ST = cpu.reg[x];
  cpu.PC += 2;
}

void Chip8::Instruction::i_Fx1E(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);
  cpu.I += (unsigned short)cpu.reg[x];
  cpu.PC += 2;
}

void Chip8::Instruction::i_Fx29(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);

  if (cpu.reg[x] > 0xF)
	throw std::runtime_error("unknown digit");

  cpu.I = static_cast<unsigned short>((unsigned short)cpu.reg[x] * 5);
  cpu.PC += 2;
}

void Chip8::Instruction::i_Fx33(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);

  if (cpu.I + 2 >= 4096)
	throw std::runtime_error("tried to save bcd number out of memory");

  cpu.mem[cpu.I] = static_cast<unsigned char>(cpu.reg[x] / 100);
  cpu.mem[cpu.I + 1u] = static_cast<unsigned char>((cpu.reg[x] / 10) % 10);
  cpu.mem[cpu.I + 2u] = static_cast<unsigned char>(cpu.reg[x] % 10);
  cpu.PC += 2;
}

void Chip8::Instruction::i_Fx55(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);

  if (cpu.I + x >= 4096)
	throw std::runtime_error("tried to store registers out of memory");

  for (unsigned int i = 0; i <= x; i++) {
	cpu.mem[cpu.I + i] = cpu.reg[i];
  }

  if (!cpu.load_store_quirk) {
	cpu.I += x + 1;
  } else {
	// when quirk is enabled don't change I register
  }
  cpu.PC += 2;
}

void Chip8::Instruction::i_Fx65(Chip8::CPU &cpu, unsigned short opcode) {
  auto x = static_cast<unsigned char>((opcode & 0x0F00u) >> 8u);

  if (cpu.I + x >= 4096)
	throw std::runtime_error("tried to store registers out of memory");

  for (unsigned int i = 0; i <= x; i++) {
	cpu.reg[i] = cpu.mem[cpu.I + i];
  }

  if (!cpu.load_store_quirk) {
	cpu.I += x + 1;
  } else {
	// when quirk is enabled don't change I register
  }

  cpu.PC += 2;
}

void Chip8::Instruction::i_0000(Chip8::CPU &cpu, [[maybe_unused]] unsigned short opcode) {
  cpu.PC += 2;
}
