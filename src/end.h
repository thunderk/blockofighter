/*
 * $Id: end.h,v 1.1 2002/07/22 01:14:14 msell Exp $
 *
 *
 * $Log: end.h,v $
 * Revision 1.1  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 *
 *
 * $Date: 2002/07/22 01:14:14 $
 *
 */

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

