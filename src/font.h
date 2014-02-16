/*
 * $Id: font.h,v 1.3 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: font.h,v $
 * Revision 1.3  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.2  2002/07/19 14:05:52  msell
 * Damagetextuurit näkyy
 *
 * Revision 1.1  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __FONT_H_INCLUDED__
#define __FONT_H_INCLUDED__

#include "texture.h"

extern Texture *fonttexture;

//Top left = 0.0 , 0.0   Bottom right = 1.0 , 1.0
void drawChar(float x, float y, char ch, float size = 0.05);
void print(float x, float y, char *text, float size = 0.05);

#endif

