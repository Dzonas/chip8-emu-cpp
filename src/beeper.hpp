#ifndef CHIP8_EMU_CPP_BEEPER_HPP
#define CHIP8_EMU_CPP_BEEPER_HPP

#include <SDL_audio.h>

const int AMPLITUDE = 28000;
const int SAMPLE_RATE = 44100;

void audio_callback(void *userdata, Uint8 *stream, int len);

/**
 * \brief Handles beep sound present in Chip8.
 */
class Beeper {
  SDL_AudioSpec desired{};
  SDL_AudioSpec obtained{};
  SDL_AudioDeviceID dev{};
  int sample = 0;
  bool playing = false;

public:
  /**
   * \brief Generates sound samples for given length.
   *
   * Generates sine wave with given amplitude, sample rate and length.
   *
   * @param stream destination SDL2 audio stream
   * @param len length of stream to fill
   */
  void generate_samples(Sint16 *stream, int len);
  /**
   * \brief Initializes audio device and spec.
   */
  void init();
  /**
   * Unpauses audio device to start playing sound.
   */
  void play();
  /**
   * Pauses audio device to stop playing sound.
   */
  void stop();
  ~Beeper();
};

#endif //CHIP8_EMU_CPP_BEEPER_HPP
