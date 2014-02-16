/*
 * $Id: fight.h,v 1.17 2002/07/22 01:14:14 msell Exp $
 *
 *
 * $Log: fight.h,v $
 * Revision 1.17  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 * Revision 1.16  2002/07/21 15:03:12  msell
 * Äänet disabloitu
 *
 * Revision 1.15  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.14  2002/07/19 20:06:32  msell
 * Linux-porttausta
 *
 * Revision 1.13  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.12  2002/07/19 14:05:52  msell
 * Damagetextuurit näkyy
 *
 * Revision 1.11  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.10  2002/07/17 22:45:54  msell
 * Ääniä vähän
 *
 * Revision 1.9  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 * Revision 1.8  2002/07/15 15:22:08  msell
 * Parantelua
 *
 * Revision 1.7  2002/07/14 21:22:40  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.6  2002/07/08 22:53:38  msell
 * Säätöä
 *
 * Revision 1.5  2002/07/07 15:29:07  msell
 * Törmäyksien parantelua
 *
 * Revision 1.4  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.3  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.2  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 * Revision 1.1  2002/05/16 18:42:07  msell
 * Vektorifunctioita ja kamera
 *
 *
 *
 * $Date: 2002/07/22 01:14:14 $
 *
 */

#ifndef __FIGHT_H_INCLUDED__
#define __FIGHT_H_INCLUDED__

#include <SDL.h>
#include "audio.h"
#include "legoman.h"

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

