#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include <SDL.h>

#include "texture.h"
#include "audio.h"

extern int detail;

extern Texture *tuxtexture;

void initMenu(void);
void calculateMenu(int framecount);
void drawMenu(int framecount);
void menuRestart(void);

#endif
