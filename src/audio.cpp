#include "main.h"

#include <string.h>
#include <stdio.h>

#include "audio.h"

#define SOUND_FADENONE 0
#define SOUND_FADEIN 1
#define SOUND_FADEOUT 2

struct soundlist {
  Sound *sound;
  soundlist *next;
};

soundlist *allsounds = NULL;

Sound::Sound(Sound *source) {
  memcpy(this, source, sizeof(Sound));
  soundlist *node = new soundlist;
  node->sound = this;
  node->next = allsounds;
  allsounds = node;
}

Sound::Sound(char *filename) {
  load(filename, SOUNDTYPE_AUTODETECT, false);
  // printf("%s: %p, %p, %p, %p\n", filename, this, stream, sample, module);
}

Sound::Sound(char *filename, int type) { load(filename, type, false); }

Sound::Sound(char *filename, bool loops) {
  load(filename, SOUNDTYPE_AUTODETECT, loops);
  // printf("%s: %p, %p, %p, %p\n", filename, this, stream, sample, module);
}

Sound::Sound(char *filename, int type, bool loops) {
  load(filename, type, loops);
}

bool endsWith(char *str1, char *str2) {
  char *str3 = str1 + strlen(str1) - strlen(str2);
#ifdef WIN32
  if (stricmp(str3, str2))
    return false;
#else
  if (strcasecmp(str3, str2))
    return false;
#endif
  else
    return true;
}

void Sound::load(char *filename, int type, bool loops) {
  this->filename = filename;
  if (type == SOUNDTYPE_AUTODETECT) {
    if (endsWith(filename, "mp3") || endsWith(filename, "mp2") ||
        endsWith(filename, "ogg"))
      type = SOUNDTYPE_STREAM;

    if (endsWith(filename, "wav") || endsWith(filename, "raw"))
      type = SOUNDTYPE_SAMPLE;

    if (endsWith(filename, "s3m") || endsWith(filename, "xm") ||
        endsWith(filename, "it") || endsWith(filename, "mid") ||
        endsWith(filename, "rmi") || endsWith(filename, "sgr") ||
        endsWith(filename, "mod"))
      type = SOUNDTYPE_MODULE;
  }
#ifdef AUDIO_FMOD
  sample = NULL;
  module = NULL;
  stream = NULL;
  this->type = type;
  if (type == SOUNDTYPE_MODULE) {
    module = FMUSIC_LoadSong(filename);
    this->loops = false;
  } else if (type == SOUNDTYPE_SAMPLE) {
    if (loops) {
      sample =
          FSOUND_Sample_Load(FSOUND_FREE, filename, FSOUND_LOOP_NORMAL, 0, 0);
      FSOUND_Sample_SetMode(sample, FSOUND_LOOP_NORMAL);
    } else {
      sample = FSOUND_Sample_Load(FSOUND_FREE, filename, FSOUND_LOOP_OFF, 0, 0);
      FSOUND_Sample_SetMode(sample, FSOUND_LOOP_OFF);
    }
    this->loops = loops;
  } else if (type == SOUNDTYPE_STREAM) {
    if (loops) {
      stream = FSOUND_Stream_Open(filename, FSOUND_LOOP_NORMAL, 0, 0);
    } else {
      stream = FSOUND_Stream_Open(filename, FSOUND_LOOP_OFF, 0, 0);
    }
    this->loops = loops;
  }
#endif
  stopcallback = NULL;
  soundlist *node = new soundlist;
  node->sound = this;
  node->next = allsounds;
  allsounds = node;
  minduration = 0;
  setVolume(1.0);
}

bool Sound::play() {
  // printf("Playing %s: %p, %p, %p, %p\n", filename, this, stream, sample,
  // module);
  if (minduration > 0)
    return false;
  running = true;
  finished = false;
  fademode = SOUND_FADENONE;
  minduration = 0;
#ifdef AUDIO_FMOD
  if (type == SOUNDTYPE_MODULE) {
    FMUSIC_PlaySong(module);
    FMUSIC_SetMasterVolume(module, (int)(volume * 256));
  } else if (type == SOUNDTYPE_SAMPLE) {
    channel = FSOUND_PlaySound(FSOUND_FREE, sample);
    FSOUND_SetVolume(channel, (int)(volume * 256));
    if (!loops) {
      running = false;
      finished = false;
    }
  } else if (type == SOUNDTYPE_STREAM) {
    channel = FSOUND_Stream_Play(FSOUND_FREE, stream);
    FSOUND_SetVolume(channel, (int)(volume * 256));
  }
#endif
  // printf("Done: %f\n", volume);
  return true;
}

void Sound::play(int minduration) {
  if (play())
    this->minduration = minduration;
}

void Sound::stop() {
#ifdef AUDIO_FMOD
  if (type == SOUNDTYPE_MODULE) {
    FMUSIC_StopSong(module);
  } else if (type == SOUNDTYPE_SAMPLE) {
    FSOUND_StopSound(channel);
  } else if (type == SOUNDTYPE_STREAM) {
    FSOUND_Stream_Stop(stream);
  }
#endif
}

void Sound::setVolume(float volume) {
#ifdef AUDIO_FMOD
  if (type == SOUNDTYPE_MODULE) {
    FMUSIC_SetMasterVolume(module, (int)(volume * 256));
  } else if (type == SOUNDTYPE_SAMPLE) {
    FSOUND_SetVolume(channel, (int)(volume * 256));
  } else if (type == SOUNDTYPE_STREAM) {
    FSOUND_SetVolume(channel, (int)(volume * 256));
  }
#endif
  this->volume = volume;
}

#ifdef AUDIO_FMOD
signed char streamendcallback(FSOUND_STREAM *stream, void *buff, int len,
                              int param) {
  Sound *sound = (Sound *)param;
  sound->setFinished();
  return true;
}
#endif

void Sound::setStopCallback(STOPCALLBACK callback) {
  stopcallback = callback;
#ifdef AUDIO_FMOD
  if (type == SOUNDTYPE_MODULE) {
  } else if (type == SOUNDTYPE_SAMPLE) {
    // NOT SUPPORTED
  } else if (type == SOUNDTYPE_STREAM) {
    // FSOUND_Stream_SetEndCallback(stream,
    // (FSOUND_STREAMCALLBACK)streamendcallback, (int)this);
  }
#endif
}

void Sound::setFinished(void) { finished = true; }

bool Sound::isFinished(void) {
#ifdef AUDIO_FMOD
  if (type == SOUNDTYPE_MODULE) {
    if (FMUSIC_IsFinished(module))
      return true;
  } else if (type == SOUNDTYPE_SAMPLE) {
    // NOT SUPPORTED
  } else if (type == SOUNDTYPE_STREAM) {
    if (finished)
      return true;
  }
#endif
  return false;
}

void Sound::update(void) {
  if (running) {
    if (isFinished()) {
      running = false;
      if (stopcallback != NULL)
        stopcallback(this);
    } else {
      if (fademode == SOUND_FADEIN) {
        if (fadepos < fadetarget) {
          fadepos++;
          setVolume((float)fadepos / fadetarget);
        } else
          fademode = SOUND_FADENONE;
      }
      if (fademode == SOUND_FADEOUT) {
        if (fadepos < fadetarget) {
          fadepos++;
          setVolume(1.0 - (float)fadepos / fadetarget);
        } else {
          fademode = SOUND_FADENONE;
          stop();
        }
      }
    }
  }
  if (minduration > 0)
    minduration--;
}

void Sound::fadeIn(int length) {
  fademode = SOUND_FADEIN;
  fadepos = 0;
  fadetarget = length;
}

void Sound::fadeOut(int length) {
  if (fademode == SOUND_FADEIN) {
    float percent = 1.0 - (float)fadepos / fadetarget;
    fadepos = (int)(fadetarget * percent);
  }
  fadepos = 0;
  fadetarget = length;
  fademode = SOUND_FADEOUT;
}

void initAudio(void) {
#ifdef AUDIO_FMOD
  FSOUND_Init(44100, 32, 0);
#endif
}

void uninitAudio(void) {
#ifdef AUDIO_FMOD
  FSOUND_Close();
#endif
}

void updateAudio(void) {
  soundlist *node = allsounds;
  while (node != NULL) {
    Sound *sound = node->sound;
    sound->update();
    node = node->next;
  }
}
