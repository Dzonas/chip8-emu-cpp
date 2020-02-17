#ifndef CHIP8_EMU_CPP_CONF_HPP
#define CHIP8_EMU_CPP_CONF_HPP

#include <filesystem>
#include <json.hpp>
#include <map>
#include <SDL2/SDL_keycode.h>
#include <array>
#include <string>

const double DEFAULT_EMULATION_PERIOD = 1.0 / 500.0; // 1 / Hz
const bool DEFAULT_LOAD_STORE_QUIRK = false;
const bool DEFAULT_SHIFT_QUIRK = false;
const bool DEFAULT_WRAPPING = true;

const int DEFAULT_SCREEN_WIDTH = 1280;
const int DEFAULT_SCREEN_HEIGHT = 640; // half the width
const double DEFAULT_REFRESH_RATE = 60; // Hz

const std::array<std::string, 16>
    DEFAULT_KEYS{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"}; // default key mapping

/**
 * \brief Configuration struct for emulator.
 */
struct RomConf {
  double emulation_period = DEFAULT_EMULATION_PERIOD; //!< Time between calling cpu's cycle function in seconds.
  bool load_store_quirk = DEFAULT_LOAD_STORE_QUIRK; //!< Load store quirk flag.
  bool shift_quirk = DEFAULT_SHIFT_QUIRK; //!< Shift quirk flag.
  bool wrapping = DEFAULT_WRAPPING; //!< Wrapping flag.
  std::string rom_location; //!< Rom location relative to root directory.

  /**
   * \brief Creates emulation configuration from json data.
   *
   * If any of the members, except rom_location, are missing, they're replaced with defaults. If rom_location
   * is missing throws runtime error.
   *
   * @param rom_data json object containing configuration
   * @param resources_path path to resources directory
   */
  RomConf(nlohmann::json rom_data, std::filesystem::path resources_path);
};

/**
 * \brief Configuration struct for SDL2 application.
 */
struct AppConf {
  int screen_width = DEFAULT_SCREEN_WIDTH; //!< Screen width in pixels.
  int screen_height = DEFAULT_SCREEN_HEIGHT; //!< Screen height in pixels.
  double refresh_rate = DEFAULT_REFRESH_RATE; //!< Screen refresh rate in Hz.
  std::map<std::string, std::string> keymap; //!< Keymap from Chip8 default key to user chosen key

  /**
   * \brief Creates AppConf from json data.
   *
   * If any of the members are missing, they are initialized with defaults. Only requirement is to provide either
   * no keymap or all keys in such keymap, otherwise throws runtime error.
   *
   * @param app_data json object
   */
  explicit AppConf(nlohmann::json app_data);
};

#endif //CHIP8_EMU_CPP_CONF_HPP
