#ifndef __AUDIO_H_INCLUDED__
#define __AUDIO_H_INCLUDED__

#ifdef AUDIO_FMOD
#include <fmod.h>
#endif

class Sound;

typedef void (*STOPCALLBACK)(Sound *sound);

#define SOUNDTYPE_AUTODETECT 0
#define SOUNDTYPE_MODULE 1
#define SOUNDTYPE_STREAM 2
#define SOUNDTYPE_SAMPLE 3

#define BGSONG DATAPATH "boom.mp3"

class Sound {
private:
#ifdef AUDIO_FMOD
  int type;
  FMUSIC_MODULE *module;
  FSOUND_STREAM *stream;
  FSOUND_SAMPLE *sample;
  int channel;
#endif
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
