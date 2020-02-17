#include <fstream>
#include "emulator.hpp"

void Emulator::run(std::chrono::duration<double> delta) {
  cycle_counter += delta.count() / emulation_period;
  timer_counter += delta.count() / Chip8::TIMER_PERIOD;

  while ((unsigned int)cycle_counter > 0) {
	cpu.cycle();
	cycle_counter--;
  }

  while ((unsigned int)timer_counter > 0) {
	cpu.update_timers();
	timer_counter--;
  }
}

void Emulator::load_config(const RomConf &config) {
  std::ifstream rom(config.rom_location, std::ifstream::binary);
  if (!rom.is_open())
	throw std::runtime_error("unable to open rom file at: " + config.rom_location);
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(rom), {});
  rom.close();

  emulation_period = config.emulation_period;

  cpu.load_store_quirk = config.load_store_quirk;
  cpu.shift_quirk = config.shift_quirk;
  cpu.wrapping = config.wrapping;

  cpu.load_rom(buffer);
}

void Emulator::set_key(const std::string &key, const bool value) {
  try {
	cpu.key(keymap.at(key)) = value;
  } catch (std::out_of_range &) {
	throw std::runtime_error("unknown key");
  }
}
