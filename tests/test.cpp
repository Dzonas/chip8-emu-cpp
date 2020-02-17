#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "cpu.hpp"

TEST_CASE ("DRAW + FONT TEST") {
  Chip8::CPU cpu;
  std::vector<unsigned char> rom = {0xA0, 0x05, 0xD0, 0x05}; // draw "1" at (0, 0)
  cpu.load_rom(rom);

  for (unsigned int i = 0; i < rom.size(); i++)
	cpu.cycle();

  auto display = cpu.get_display();
  std::vector<unsigned char> data;

  for (unsigned int i = 0; i < 5; i++) {
	unsigned char v = 0;
	for (unsigned int j = 0; j < 8; j++) {
	  auto index = i * Chip8::SCREEN_WIDTH + j;
	  bool pixel = display[index];
	  v = (v << 1u) | pixel;
	}
	data.push_back(v);
  }

  REQUIRE(data[0] == 0x20);
  REQUIRE(data[1] == 0x60);
  REQUIRE(data[2] == 0x20);
  REQUIRE(data[3] == 0x20);
  REQUIRE(data[4] == 0x70);

  // TODO test wrapping
  // TODO test no wrapping
  // TODO test without fonts
  // TODO separate font test from draw test
}