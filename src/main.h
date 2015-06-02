#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

#ifdef WIN32
#pragma warning(disable : 4244) // Disable: conversion from 'double' to
                                // 'double', possible loss of data
#pragma warning(                                                               \
    disable : 4305) // Disable: truncation from 'const double' to 'double'
#endif

#include "SDL.h"

#ifdef DEBUG
#define _DEBUG
#endif

#ifdef HAVE_CONFIG_H
#include <config.h>
#else
#define HAVE_TIME_H
#ifdef WIN32
#define VERSION "W32"
#define HAVE_FMOD_H
#endif
#endif

#define DATAPATH "data/"
extern bool keys[SDLK_LAST];

void exitProgram(int code);
void changeResolution(int width, int height, bool fullscreen);
extern int screenwidth, screenheight;

void setSpeedFactor(float factor);

extern int debugcounter;
#ifdef DEBUG
#define DP                                                                     \
  printf("%s: %i (Debug counter: %i)\n", __FILE__, __LINE__, debugcounter++);
#else
#define DP
#endif

#endif
