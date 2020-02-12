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

const std::array<std::string, 16> DEFAULT_KEYS {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};

struct RomConf {
    double emulation_period = DEFAULT_EMULATION_PERIOD;
    bool load_store_quirk = DEFAULT_LOAD_STORE_QUIRK;
    bool shift_quirk = DEFAULT_SHIFT_QUIRK;
    bool wrapping = DEFAULT_WRAPPING;
    std::string rom_location;

    RomConf(nlohmann::json rom_data, std::filesystem::path resources_path);
};

struct AppConf {
    int screen_width = DEFAULT_SCREEN_WIDTH;
    int screen_height = DEFAULT_SCREEN_HEIGHT;
    double refresh_rate = DEFAULT_REFRESH_RATE;
    std::map<std::string, std::string> keymap; // maps from chip8 key to user chosen key

    explicit AppConf(nlohmann::json app_data);
};

#endif //CHIP8_EMU_CPP_CONF_HPP
