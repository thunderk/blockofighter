#ifndef __FIGHT_H_INCLUDED__
#define __FIGHT_H_INCLUDED__

#include <SDL.h>
#include "audio.h"
#include "legoman.h"
#include "camera.h"

#define ARENASIZE 10
#define ARENAHEIGHT 10

extern Sound *fightmusic;
extern Sound *hitsound1;
extern Sound *softhitsound1, *softhitsound2;
extern Sound *jumpsound;
extern Sound *fallsound1, *fallsound2;

extern bool dead;

extern Legoman *winner;

void initFight(void);
void gameOver(Legoman *loser);
void startFight(void);
void calculateFight(int framecount);
void drawFight(int framecount);

void handleKeydownFight(SDLKey key);
void addGraphicsVector(float *p1, float *p2, float size);

#endif
