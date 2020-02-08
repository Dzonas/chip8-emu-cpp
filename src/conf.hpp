#ifndef CHIP8_EMU_CPP_CONF_HPP
#define CHIP8_EMU_CPP_CONF_HPP

#include <filesystem>
#include <json.hpp>

const double DEFAULT_EMULATION_PERIOD = 1.0 / 500.0; // 1 / Hz
const bool DEFAULT_LOAD_STORE_QUIRK = false;
const bool DEFAULT_SHIFT_QUIRK = false;
const bool DEFAULT_WRAPPING = true;

struct Conf {
    double emulation_period = DEFAULT_EMULATION_PERIOD;
    bool load_store_quirk = DEFAULT_LOAD_STORE_QUIRK;
    bool shift_quirk = DEFAULT_SHIFT_QUIRK;
    bool wrapping = DEFAULT_WRAPPING;
    std::string rom_location;

    explicit Conf(nlohmann::json rom_data, std::filesystem::path resources_path);
};

#endif //CHIP8_EMU_CPP_CONF_HPP
