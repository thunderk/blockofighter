/*
 * $Id: run.h,v 1.9 2002/07/22 01:14:14 msell Exp $
 *
 *
 * $Log: run.h,v $
 * Revision 1.9  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 * Revision 1.8  2002/07/19 20:33:29  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.7  2002/07/17 20:32:48  msell
 * Detail-optio toimii
 *
 * Revision 1.6  2002/07/16 17:16:35  msell
 * Fontit ja valikot
 *
 * Revision 1.5  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.4  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
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
 * $Date: 2002/07/22 01:14:14 $
 *
 */

#ifndef __RUN_H_INCLUDED__
#define __RUN_H_INCLUDED__

#define MENUMODE 1
#define FIGHTMODE 2
#define ENDMODE 3

void initScenes(void);
void changeGameMode(int newmode);
void calculateFrame(int framecount);
void drawFrame(int framecount);
void initTextures(void);
void setDetail(int detail);

#endif

