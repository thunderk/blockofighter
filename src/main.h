/*
 * $Id: main.h,v 1.13 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: main.h,v $
 * Revision 1.13  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.12  2002/07/19 20:06:32  msell
 * Linux-porttausta
 *
 * Revision 1.11  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.10  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 * Revision 1.9  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.8  2002/07/14 21:22:39  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.7  2002/07/08 22:53:38  msell
 * Säätöä
 *
 * Revision 1.6  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.5  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.4  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.3  2002/05/17 12:30:26  msell
 * no message
 *
 * Revision 1.2  2002/05/16 18:41:16  msell
 * Vektorifunctioita ja kamera
 *
 * Revision 1.1  2002/05/15 14:36:39  msell
 * Yksinkertainen SDL-runko (Kääntyy toistaiseksi vain windowsissa).
 * Mukana myös musiikinsoitto fmodilla.
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__


#ifdef WIN32
#pragma warning(disable:4244) //Disable: conversion from 'double' to 'double', possible loss of data
#pragma warning(disable:4305) //Disable: truncation from 'const double' to 'double'
#endif

#include <SDL.h>

#define DATAPATH "data/"
extern bool keys[SDLK_LAST];

void exitProgram(int code);
void changeResolution(int width, int height, bool fullscreen);
extern int screenwidth, screenheight;

extern int debugcounter;
#ifdef DEBUG
#define DP printf("%s: %i (Debug counter: %i)\n",__FILE__,__LINE__,debugcounter++);
#else
#define DP
#endif

#endif

