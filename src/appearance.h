/*
 * $Id: appearance.h,v 1.11 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: appearance.h,v $
 * Revision 1.11  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.10  2002/07/15 22:03:23  msell
 * MultiAppearance
 *
 * Revision 1.9  2002/07/07 17:53:21  msell
 * Legoukon alku
 *
 * Revision 1.8  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.7  2002/06/20 00:21:01  jkaarlas
 * materiaali- ja tekstuurihommia edistetty
 *
 * Revision 1.6  2002/06/17 20:49:04  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.5  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.4  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.3  2002/06/03 23:20:43  msell
 * no message
 *
 * Revision 1.2  2002/06/03 23:06:38  msell
 * no message
 *
 * Revision 1.1  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __APPEARANCE_H_INCLUDED__
#define __APPEARANCE_H_INCLUDED__

#include "main.h"

#include "material.h"

/*
 * Abstract class for drawing objects
 */
class Appearance{
private:
public:
  Material material;

  Appearance(void);

  Material* getMaterial(void);
  void setMaterial(Material mat);

	virtual void prepare(void);
	virtual void draw(void) = 0;
};


struct appearancelist{
	Appearance *data;
	appearancelist *next;
};

class MultiAppearance : public Appearance{
private:
	appearancelist *appearances;

public:
	MultiAppearance(void);
	void addAppearance(Appearance *appearance);

	void prepare(void);
	void draw(void);
};

#endif

