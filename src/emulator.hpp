#ifndef CHIP8_EMU_CPP_EMULATOR_HPP
#define CHIP8_EMU_CPP_EMULATOR_HPP

#include <chrono>
#include <string>
#include <map>
#include "chip8/cpu.hpp"
#include "conf.hpp"

class Emulator {
    double cycle_counter = 0;
    double timer_counter = 0;
    double emulation_period = 0.0;
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
    Chip8::CPU cpu;

    void load_config(const RomConf &config);
    void set_key(const std::string &key, bool value);
    void run(std::chrono::duration<double> delta);
};


#endif //CHIP8_EMU_CPP_EMULATOR_HPP
