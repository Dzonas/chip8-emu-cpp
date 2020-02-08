#ifndef CHIP8_EMU_CPP_APP_HPP
#define CHIP8_EMU_CPP_APP_HPP

#include <SDL2/SDL.h>
#include "emulator.hpp"
#include "conf.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640; // half the width
const double SCREEN_UPDATE_PERIOD = 1.0 / 60.0; // 1 / Hz

class App {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event e{};

    Emulator chip8_emu;
    bool running = false;

    void process_input();

public:
    App();

    void init_emulation(const Conf &config);

    void run();

    ~App();
};


#endif //CHIP8_EMU_CPP_APP_HPP
