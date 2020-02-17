#ifndef CHIP8_EMU_CPP_APP_HPP
#define CHIP8_EMU_CPP_APP_HPP

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include "emulator.hpp"
#include "conf.hpp"
#include "beeper.hpp"

/**
 * \brief  Represents whole emulator applications.
 *
 * Handles SDL2 related stuff.
 */
class App {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Event e{};

  Emulator chip8_emu;
  Beeper beeper;
  double screen_update_period;
  std::map<SDL_Keycode, std::string> keymap; // maps from pressed key to cpu key name

  bool running = false;

  void process_input();

public:
  /**
   * \brief Creates app from configuration.
   *
   * Initializes SDL2 with video and audio, creates window and renderer, initializes Beeper, sets screen update period
   * from refresh rate and creates keymap from SDL2 key to cpu key. Throws runtime error when any of the SDL2 function
   * return error.
   *
   * \warning Constructor doesn't initialize emulation. In order for emulation to work correctly init_emulation
   * with proper configuration must be called.
   *
   * @param conf Application configuration struct.
   */
  explicit App(const AppConf &conf);

  /**
   * \brief Initializes emulation with configuration.
   *
   * This function must be called in order for emulation to work properly. Configuration can be modified by
   * changing the RomConf config struct.
   *
   * @param config Emulation configuration struct.
   */
  void init_emulation(const RomConf &config);

  /**
   * \brief Runs main loop of the application.
   *
   * Main loop consists of a few stages:
   * 1. Read input.
   * 2. Process input - either quit the application or set key in emulator.
   * 3. Draw to the screen.
   * 4. Run emulation cycle.
   * Main loop will run until SDL_Quit event is emitted.
   */
  void run();
  ~App();
};

#endif //CHIP8_EMU_CPP_APP_HPP
