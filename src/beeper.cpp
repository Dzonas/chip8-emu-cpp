#include <cmath>
#include <stdexcept>
#include "beeper.hpp"

void audio_callback(void *userdata, Uint8 *stream, int len) {
  auto *beeper = (Beeper *)userdata;
  auto *stream_new = (Sint16 *)stream;
  beeper->generate_samples(stream_new, len / 2);
}

Beeper::~Beeper() {
  SDL_PauseAudioDevice(dev, 1);
  SDL_CloseAudioDevice(dev);
}

void Beeper::generate_samples(Sint16 *stream, int len) {
  for (int i = 0; i < len; i++, sample++) {
	double time = (double)sample / (double)SAMPLE_RATE;
	stream[i] = (Sint16)(AMPLITUDE * sin(2.0f * M_PI * 441.0f * time)); // render 441 HZ sine wave
  }
}

void Beeper::init() {
  desired.freq = 44100;
  desired.format = AUDIO_S16SYS;
  desired.channels = 1;
  desired.samples = 2048;
  desired.callback = audio_callback;
  desired.userdata = this;
  dev = SDL_OpenAudioDevice(nullptr, 0, &desired, &obtained, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
  if (dev == 0)
	throw std::runtime_error(SDL_GetError());
}

void Beeper::play() {
  if (!playing) {
	SDL_PauseAudioDevice(dev, 0);
	playing = true;
  }
}

void Beeper::stop() {
  if (playing) {
	SDL_PauseAudioDevice(dev, 1);
	playing = false;
  }
}
