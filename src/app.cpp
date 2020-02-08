#include <stdexcept>
#include <thread>
#include "chip8/cpu.hpp"
#include "app.hpp"

App::App() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(SDL_GetError());

    window = SDL_CreateWindow("Chip8 emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
        throw std::runtime_error(SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());

    if (SDL_RenderSetLogicalSize(renderer, Chip8::SCREEN_WIDTH, Chip8::SCREEN_HEIGHT) < 0)
        throw std::runtime_error(SDL_GetError());
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
        auto hmm = chip8_emu.cpu.get_display();

        for (unsigned int y = 0; y < Chip8::SCREEN_HEIGHT; y++) {
            for (unsigned int x = 0; x < Chip8::SCREEN_WIDTH; x++) {
                if (hmm[y * Chip8::SCREEN_WIDTH + x]) {
                    SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta = end - start;
        start = std::chrono::high_resolution_clock::now();
        chip8_emu.run(delta);

        SDL_RenderPresent(renderer);

        std::this_thread::sleep_for(std::chrono::duration<double>(SCREEN_UPDATE_PERIOD));
    }

}

void App::process_input() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
            running = false;
        else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            unsigned char id;
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    id = 0;
                    break;
                case SDLK_2:
                    id = 1;
                    break;
                case SDLK_3:
                    id = 2;
                    break;
                case SDLK_4:
                    id = 3;
                    break;
                case SDLK_q:
                    id = 4;
                    break;
                case SDLK_w:
                    id = 5;
                    break;
                case SDLK_e:
                    id = 6;
                    break;
                case SDLK_r:
                    id = 7;
                    break;
                case SDLK_a:
                    id = 8;
                    break;
                case SDLK_s:
                    id = 9;
                    break;
                case SDLK_d:
                    id = 10;
                    break;
                case SDLK_f:
                    id = 11;
                    break;
                case SDLK_z:
                    id = 12;
                    break;
                case SDLK_x:
                    id = 13;
                    break;
                case SDLK_c:
                    id = 14;
                    break;
                case SDLK_v:
                    id = 15;
                    break;
                default:
                    return;
            }

            chip8_emu.cpu.key(id) = e.type == SDL_KEYDOWN;
        }
    }
}

void App::init_emulation(const Conf &config) {
    chip8_emu.load_config(config);
}
