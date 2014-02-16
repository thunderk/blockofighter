/*
 * $Id: audio.h,v 1.13 2002/07/21 15:12:16 msell Exp $
 *
 *
 * $Log: audio.h,v $
 * Revision 1.13  2002/07/21 15:12:16  msell
 * Äänet enabloitu :)
 *
 * Revision 1.12  2002/07/21 15:03:12  msell
 * Äänet disabloitu
 *
 * Revision 1.11  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.10  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.9  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.8  2002/07/14 21:22:40  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.7  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.6  2002/05/19 13:40:19  msell
 * Säätöä
 *
 * Revision 1.5  2002/05/18 12:29:35  msell
 * Valot ja äänijärjestelmän parantelua
 *
 * Revision 1.4  2002/05/16 18:41:16  msell
 * Vektorifunctioita ja kamera
 *
 * Revision 1.3  2002/05/15 21:07:23  msell
 * Äänisäätöä
 *
 * Revision 1.2  2002/05/15 15:21:00  msell
 * Äänisäätöä
 *
 * Revision 1.1  2002/05/15 14:36:39  msell
 * Yksinkertainen SDL-runko (Kääntyy toistaiseksi vain windowsissa).
 * Mukana myös musiikinsoitto fmodilla.
 *
 *
 *
 * $Date: 2002/07/21 15:12:16 $
 *
 */

#ifndef __AUDIO_H_INCLUDED__
#define __AUDIO_H_INCLUDED__


//#define AUDIO_NONE
#define AUDIO_FMOD
//Only FMOD and NONE is supported, choose one




#ifdef AUDIO_FMOD
#include <fmod.h>
#endif


class Sound;

typedef void(* STOPCALLBACK)(Sound *sound);

#define SOUNDTYPE_AUTODETECT 0
#define SOUNDTYPE_MODULE 1
#define SOUNDTYPE_STREAM 2
#define SOUNDTYPE_SAMPLE 3

#define BGSONG DATAPATH"boom.mp3"

class Sound{
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

	//Plays sound for at least minduration frames until sound
	//can be played again. Doesn't prevent stopping of the sound
	void play(int minduration);
	void stop();
	void setStopCallback(STOPCALLBACK callback);
	void setVolume(float volume);
	void fadeIn(int length);
	void fadeOut(int length);
	
	//Do not use methods below
	void setFinished(void);
	void update(void);
};

void initAudio(void);
void uninitAudio(void);
void updateAudio(void);

#endif

