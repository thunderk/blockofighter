/*
 * $Id: material.h,v 1.8 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: material.h,v $
 * Revision 1.8  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.7  2002/07/10 22:22:04  jkaarlas
 * getColor
 *
 * Revision 1.6  2002/06/27 21:43:29  jkaarlas
 * lisätty setTexture-funktio
 *
 * Revision 1.5  2002/06/20 00:21:01  jkaarlas
 * materiaali- ja tekstuurihommia edistetty
 *
 * Revision 1.4  2002/06/19 22:45:29  jkaarlas
 * nyt nämä menee järkevästi
 *
 * Revision 1.3  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.2  2002/06/03 23:06:38  msell
 * no message
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

#include <SDL_image.h>
#include "texture.h"

class Material{
private:
  Texture* texture;
	float color[4];
  bool enabled;

public:
	Material(void);
	bool loadTexture(char *path);
  void freeTexture(void);

	void setColor(float red, float green, float blue, float alpha);
	const float* getColor(void);
	void enable(void);
  void disable(void);
  bool isEnabled(void);
  Texture* getTexture(void);
  void setTexture(Texture* tex);
  
};

#endif

