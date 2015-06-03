#ifndef __END_H_INCLUDED__
#define __END_H_INCLUDED__

#include <SDL.h>

#include "texture.h"
#include "audio.h"

void initEnd(void);
void endRestart(void);
void calculateEnd(int framecount);
void drawEnd(int framecount);

#endif
