#ifndef CHIP8_EMU_CPP_EMULATOR_HPP
#define CHIP8_EMU_CPP_EMULATOR_HPP

#include <chrono>
#include "chip8/cpu.hpp"
#include "conf.hpp"

class Emulator {
    double cycle_counter = 0;
    double timer_counter = 0;
    double emulation_period = 0.0;

public:
    Chip8::CPU cpu;

    void load_config(const Conf &config);
    void run(std::chrono::duration<double> delta);
};


#endif //CHIP8_EMU_CPP_EMULATOR_HPP
