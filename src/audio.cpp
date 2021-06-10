#include "main.h"

#include <string.h>
#include <stdio.h>
#include <functional>

#include "audio.h"

#define SOUND_FADENONE 0
#define SOUND_FADEIN 1
#define SOUND_FADEOUT 2

struct soundlist {
  Sound *sound;
  soundlist *next;
};

soundlist *allsounds = NULL;
Sound *current_music = NULL;

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
    if (endsWith(filename, "mp3") || endsWith(filename, "ogg"))
      type = SOUNDTYPE_STREAM;

    if (endsWith(filename, "wav") || endsWith(filename, "raw"))
      type = SOUNDTYPE_SAMPLE;
  }

  this->chunk = NULL;
  this->music = NULL;
  if (type == SOUNDTYPE_SAMPLE) {
    this->chunk = Mix_LoadWAV(filename);
    if (this->chunk) {
    } else {
      printf("Error while loading sample %s: %s\n", filename, Mix_GetError());
    }
  } else if (type == SOUNDTYPE_STREAM) {
    this->music = Mix_LoadMUS(filename);
    if (!this->music) {
      printf("Error while loading music %s: %s\n", filename, Mix_GetError());
    }
  }

  this->loops = loops;
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
  if (chunk) {
    channel = -1;
    /*channel = FSOUND_PlaySound(FSOUND_FREE, sample);
    FSOUND_SetVolume(channel, (int)(volume * 256));
    if (!loops) {
      running = false;
      finished = false;
    }*/
  } else if (music) {
    if (Mix_PlayMusic(music, loops)) {
      printf("Failed to play music\n");
    } else {
      current_music = this;
    }
    Mix_VolumeMusic((int)(volume * MIX_MAX_VOLUME));
  }
  // printf("Done: %f\n", volume);
  return true;
}

void Sound::play(int minduration) {
  if (play())
    this->minduration = minduration;
}

void Sound::stop() {
  if (chunk && channel >= 0) {
    Mix_HaltChannel(channel);
  } else if (music && current_music == this) {
    // FIXME only if it is THIS music playing
    Mix_HaltMusic();
  }
}

void Sound::setVolume(float volume) {
  if (chunk && channel >= 0) {
    Mix_Volume(channel, (int)(volume * MIX_MAX_VOLUME));
  } else if (music && current_music == this) {
    Mix_VolumeMusic((int)(volume * MIX_MAX_VOLUME));
  }
  this->volume = volume;
}

void streamendcallback(Sound* sound) {
  sound->setFinished();
}

void Sound::setStopCallback(STOPCALLBACK callback) {
  stopcallback = callback;
  if (chunk && channel >= 0) {
    // NOT SUPPORTED
  } else if (music) {
    //Mix_HookMusicFinished(std::bind(callback, this));
  }
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
  Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
}

void uninitAudio(void) {
  Mix_CloseAudio();
  Mix_Quit();
}

void updateAudio(void) {
  soundlist *node = allsounds;
  while (node != NULL) {
    Sound *sound = node->sound;
    sound->update();
    node = node->next;
  }
}
