#ifndef CHIP8_EMU_CPP_EMULATOR_HPP
#define CHIP8_EMU_CPP_EMULATOR_HPP

#include <chrono>
#include <string>
#include <map>
#include "chip8/cpu.hpp"
#include "conf.hpp"

/**
 * \brief Handles emulation of the Chip8 CPU.
 */
class Emulator {
  double cycle_counter = 0; // number of cycles to execute
  double timer_counter = 0; // number of times timers need to be updated
  double emulation_period = 0.0; // time between next cycle in seconds
  std::map<std::string, unsigned int> keymap = { // maps from key name to key id
	  {"0", 0},
	  {"1", 1},
	  {"2", 2},
	  {"3", 3},
	  {"4", 4},
	  {"5", 5},
	  {"6", 6},
	  {"7", 7},
	  {"8", 8},
	  {"9", 9},
	  {"A", 10},
	  {"B", 11},
	  {"C", 12},
	  {"D", 13},
	  {"E", 14},
	  {"F", 15}
  };

public:
  /** \brief CPU to emulate */
  Chip8::CPU cpu;

  /**
   * \brief Loads emulation configuration.
   *
   * @param config configuration struct containing settings i.e. quirk flags, emulation period etc.
   */
  void load_config(const RomConf &config);

  /**
   * \brief Sets given key to value.
   *
   * @param key string representing a key
   * @param value is key set
   */
  void set_key(const std::string &key, bool value);

  /**
   * \brief Runs emulation cycle.
   *
   * Executes cpu's cycles and updates it's timers as many times as they should in time delta.
   *
   * @param delta time between calls of this function
   */
  void run(std::chrono::duration<double> delta);

  /**
   * \brief Gets if sound should be playing.
   *
   * @return is sound playing
   */
  bool sound_on() { return cpu.sound_timer() > 0; }
};

#endif //CHIP8_EMU_CPP_EMULATOR_HPP
