/*
 * $Id: menu.h,v 1.6 2002/07/21 22:50:39 msell Exp $
 *
 *
 * $Log: menu.h,v $
 * Revision 1.6  2002/07/21 22:50:39  msell
 * no message
 *
 * Revision 1.5  2002/07/19 21:17:07  msell
 * bugifixi
 *
 * Revision 1.4  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.3  2002/07/19 20:06:32  msell
 * Linux-porttausta
 *
 * Revision 1.2  2002/07/17 20:32:47  msell
 * Detail-optio toimii
 *
 * Revision 1.1  2002/07/16 17:16:35  msell
 * Fontit ja valikot
 *
 *
 *
 * $Date: 2002/07/21 22:50:39 $
 *
 */

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

