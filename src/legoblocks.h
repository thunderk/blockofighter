/*
 * $Id: legoblocks.h,v 1.14 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: legoblocks.h,v $
 * Revision 1.14  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.13  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.12  2002/07/17 20:32:47  msell
 * Detail-optio toimii
 *
 * Revision 1.11  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 * Revision 1.10  2002/07/16 00:42:43  msell
 * Uusia skyboxeja ja areenan säätöä
 *
 * Revision 1.9  2002/07/15 20:32:35  msell
 * Uudet valot ja ulkoasun parantelua
 *
 * Revision 1.8  2002/07/15 15:22:08  msell
 * Parantelua
 *
 * Revision 1.7  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.6  2002/06/20 00:21:01  jkaarlas
 * materiaali- ja tekstuurihommia edistetty
 *
 * Revision 1.5  2002/06/17 20:49:04  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.4  2002/06/05 18:39:05  msell
 * Jotain pientä
 *
 * Revision 1.3  2002/06/05 15:00:41  msell
 * Palikoihin lisää detailia, facet jaetaan halutun kokosiin osiin
 *
 * Revision 1.2  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.1  2002/06/03 23:06:38  msell
 * no message
 *
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __LEGOBLOCKS_H_INCLUDED__
#define __LEGOBLOCKS_H_INCLUDED__

//#include "mesh.h"
#include "object.h"
#include "material.h"
#include "mesh.h"

#define BLOCKHEIGHT 0.4

class BasicBlock : public MeshObject{
private:
	int width, height, depth;

public:
	BasicBlock(int width, int height, int depth);

	void setColor(float red, float green, float blue);
};


class BasicBlockAppearance : public Appearance{
private:
	int width, height, depth;
	int gllist;

protected:
	bool usematerial;

public:
	float displacement[3];

	BasicBlockAppearance(int width, int height, int depth);
	
	virtual void prepare(void);
	virtual void draw(void);
};

void drawDetailRectangle(float width, float height);

extern int knobgllist;
extern int knobdetail;
void initKnob(void);
void createKnob(int knobsegments = -1);



class HeadAppearance : public Appearance{
private:
	int gllist;

public:
	HeadAppearance(void);

	void prepare(void);
	void draw(void);
};



#define FLOWER_RED 1
#define FLOWER_YELLOW 2
#define FLOWER_WHITE 3

class FlowerAppearance : public Appearance{
private:
	int gllist;
	int color1, color2, color3;

public:
	FlowerAppearance(int color1, int color2, int color3);

	void prepare(void);
	void draw(void);
};



class LampAppearance : public Appearance{
private:
	int gllist;

public:
	LampAppearance(void);

	void prepare(void);
	void draw(void);
};


#endif
