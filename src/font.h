#ifndef __FONT_H_INCLUDED__
#define __FONT_H_INCLUDED__

#include "texture.h"

extern Texture *fonttexture;

// Top left = 0.0 , 0.0   Bottom right = 1.0 , 1.0
void drawChar(float x, float y, char ch, float size = 0.05);
void print(float x, float y, char *text, float size = 0.05);

#endif
