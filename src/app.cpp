#include <stdexcept>
#include <thread>
#include "chip8/cpu.hpp"
#include "app.hpp"

App::App(const AppConf& conf) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(SDL_GetError());

    window = SDL_CreateWindow("Chip8 emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              conf.screen_width, conf.screen_height, SDL_WINDOW_SHOWN);
    if (!window)
        throw std::runtime_error(SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());

    if (SDL_RenderSetLogicalSize(renderer, Chip8::SCREEN_WIDTH, Chip8::SCREEN_HEIGHT) < 0)
        throw std::runtime_error(SDL_GetError());

    screen_update_period = 1.0 / conf.refresh_rate;

    for (const auto& key : conf.keymap) {
        SDL_Keycode key_code = SDL_GetKeyFromName(key.second.c_str());
        if (key_code == SDLK_UNKNOWN)
            throw std::runtime_error(SDL_GetError());
        keymap[key_code] = key.first;
    }
}

App::~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::run() {
    running = true;
    auto start = std::chrono::high_resolution_clock::now();

    while (running) {
        process_input();

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        auto display = chip8_emu.cpu.get_display();
        std::vector<SDL_Point> points_to_draw;

        for (unsigned int y = 0; y < Chip8::SCREEN_HEIGHT; y++) {
            for (unsigned int x = 0; x < Chip8::SCREEN_WIDTH; x++) {
                if (display[y * Chip8::SCREEN_WIDTH + x]) {
                    points_to_draw.push_back(SDL_Point {static_cast<int>(x), static_cast<int>(y)});
                }
            }
        }

        SDL_RenderDrawPoints(renderer, points_to_draw.data(), points_to_draw.size());

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta = end - start;
        start = std::chrono::high_resolution_clock::now();
        chip8_emu.run(delta);

        SDL_RenderPresent(renderer);

        std::this_thread::sleep_for(std::chrono::duration<double>(screen_update_period));
    }

}
void App::process_input() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            running = false;
        else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            try {
                std::string changed_key = keymap.at(e.key.keysym.sym);
                bool key_value = e.type == SDL_KEYDOWN;
                chip8_emu.set_key(changed_key, key_value);
            } catch (std::out_of_range &) {
                // dont do anything
            }
        }
    }
}

void App::init_emulation(const RomConf &config) {
    chip8_emu.load_config(config);
}
