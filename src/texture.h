/*
 * $Id: texture.h,v 1.8 2002/07/19 20:33:29 msell Exp $
 *
 *
 * $Log: texture.h,v $
 * Revision 1.8  2002/07/19 20:33:29  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.7  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.6  2002/06/27 21:43:50  jkaarlas
 * lisätty setId-funktio
 *
 * Revision 1.5  2002/06/20 00:21:01  jkaarlas
 * materiaali- ja tekstuurihommia edistetty
 *
 * Revision 1.4  2002/06/19 22:45:29  jkaarlas
 * nyt nämä menee järkevästi
 *
 * Revision 1.3  2002/06/15 22:52:32  jkaarlas
 * tekstuurimanageri ja työkalupakki
 *
 * 
 *
 * $Date: 2002/07/19 20:33:29 $
 *
 */

#ifndef __TEXTURE_H_INCLUDED__
#define __TEXTURE_H_INCLUDED__

#include <SDL_image.h>
#include "main.h"
class Texture{

public:

  Texture(void);
  Texture(int id);
  ~Texture(void);

  bool loadImage(char* path);
  bool loadImage(char* path, float *trans);
  void enable(void);
  void disable(void);
  bool isEnabled(void);
  int getId(void);
  void setId(int id);
  bool isValidId(void);
	void reload(void);
  
  //int* getOGLTexture(void);
  //int* getModifiableOGLTexture(void);

private:

  int textureId;
  //int* modTexture;
  bool enabled;

	SDL_Surface *texture;
	int format;
};

#endif

