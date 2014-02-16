/*
 * $Id: graphics.h,v 1.9 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: graphics.h,v $
 * Revision 1.9  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.8  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.7  2002/06/28 14:51:40  jkaarlas
 * transparenttilatausta korjailtu
 *
 * Revision 1.6  2002/06/27 21:42:32  jkaarlas
 * lisätty transparentin tekstuurin lataus
 *
 * Revision 1.5  2002/06/17 20:49:04  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.4  2002/06/17 20:24:20  jkaarlas
 * pahimmat bugit korjattu
 *
 * Revision 1.3  2002/06/17 16:51:38  jkaarlas
 * realloc korjattu
 *
 * Revision 1.2  2002/06/16 01:05:18  jkaarlas
 * vähän lihaa luiden ympärille näihinkin
 *
 * 
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __GRAPHICS_H_INCLUDED__
#define __GRAPHICS_H_INCLUDED__

#ifdef WIN32
#pragma warning ( disable : 4700 )
#endif

#include "main.h"
#include "texture.h"
#include "glapi.h"

const int ID_ARRAY_INIT_SIZE = 16;
const int ID_ARRAY_GROW = 8;

#define DRUID GraphicsDruid::getInstance()
#define DIE_DRUID_DIE GraphicsDruid::destroy()
typedef unsigned char byte;
typedef struct jpeg_pixel{
    Uint8 red;
    Uint8 green;
    Uint8 blue;
}jpeg_pixel;



class GraphicsDruid{

private:

  static GraphicsDruid* instance;
  int* idArray;
  int textureCount;
  int reserved;
  
  GraphicsDruid(void);
  ~GraphicsDruid(void);
  
  static void init(void);
  static void destroy(void);

public:
  
  static GraphicsDruid &getInstance(void);
	int loadTexture(SDL_Surface *texture, int id = -1, int format = GL_RGB);
  int loadTexture(char* path, int id = -1);
  int loadTranspTexture(char* path, float* transpColor, int id = -1);
  void freeTexture(int id);
  void freeAll(void);
  int getNewTextureID(int id);

};

#endif

