#ifndef CHIP8_EMU_CPP_APP_HPP
#define CHIP8_EMU_CPP_APP_HPP

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include "emulator.hpp"
#include "conf.hpp"


class App {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event e{};

    Emulator chip8_emu;
    double screen_update_period;
    std::map<SDL_Keycode, std::string> keymap; // maps from pressed key to cpu key name

    bool running = false;

    void process_input();

public:
    explicit App(const AppConf& conf);

    void init_emulation(const RomConf &config);

    void run();

    ~App();
};


#endif //CHIP8_EMU_CPP_APP_HPP
