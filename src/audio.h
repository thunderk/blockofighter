#ifndef __AUDIO_H_INCLUDED__
#define __AUDIO_H_INCLUDED__

#include "SDL_mixer.h"

class Sound;

typedef void (*STOPCALLBACK)(Sound *sound);

#define SOUNDTYPE_AUTODETECT 0
#define SOUNDTYPE_STREAM 1
#define SOUNDTYPE_SAMPLE 2

#define BGSONG DATAPATH "boom.mp3"

class Sound {
private:
  Mix_Chunk *chunk;
  Mix_Music *music;
  int channel;

  bool loops;
  bool finished;
  bool running;
  float volume;
  STOPCALLBACK stopcallback;
  bool isFinished(void);

  int fadepos, fadetarget;
  int fademode;

  int minduration;

  char *filename;

public:
  Sound(Sound *source);
  Sound(char *filename);
  Sound(char *filename, int type);
  Sound(char *filename, bool loops);
  Sound(char *filename, int type, bool loops);
  void load(char *filename, int type, bool loops);
  bool play(void);

  // Plays sound for at least minduration frames until sound
  // can be played again. Doesn't prevent stopping of the sound
  void play(int minduration);
  void stop();
  void setStopCallback(STOPCALLBACK callback);
  void setVolume(float volume);
  void fadeIn(int length);
  void fadeOut(int length);

  // Do not use methods below
  void setFinished(void);
  void update(void);
};

void initAudio(void);
void uninitAudio(void);
void updateAudio(void);

#endif
