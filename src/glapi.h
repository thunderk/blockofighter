/*
 * $Id: glapi.h,v 1.6 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: glapi.h,v $
 * Revision 1.6  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.5  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.4  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.3  2002/06/04 16:28:32  msell
 * #pragma once
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

#ifndef __GLAPI_H_INCLUDED__
#define __GLAPI_H_INCLUDED__

#include <SDL_opengl.h>

void setupOpengl(int width, int height);

#endif


