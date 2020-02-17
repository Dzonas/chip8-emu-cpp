#ifndef CHIP8_EMU_CPP_BEEPER_HPP
#define CHIP8_EMU_CPP_BEEPER_HPP

#include <SDL_audio.h>

const int AMPLITUDE = 28000;
const int SAMPLE_RATE = 44100;

void audio_callback(void *userdata, Uint8 *stream, int len);

class Beeper {
  SDL_AudioSpec desired{};
  SDL_AudioSpec obtained{};
  SDL_AudioDeviceID dev{};
  int sample = 0;
  bool playing = false;

public:
  void generate_samples(Sint16 *stream, int len);
  void init();
  void play();
  void stop();
  ~Beeper();
};

#endif //CHIP8_EMU_CPP_BEEPER_HPP
