/*
 * $Id: world.h,v 1.6 2002/07/19 20:33:29 msell Exp $
 *
 *
 * $Log: world.h,v $
 * Revision 1.6  2002/07/19 20:33:29  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.5  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.4  2002/07/15 15:22:08  msell
 * Parantelua
 *
 * Revision 1.3  2002/07/10 17:13:44  msell
 * Törmäystarkastelun parantelua
 *
 * Revision 1.2  2002/07/07 23:05:22  msell
 * Osien liimaaminen toisiinsa (kesken)
 *
 * Revision 1.1  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 *
 *
 * $Date: 2002/07/19 20:33:29 $
 *
 */

#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

class World;
class ObjectLink;

#include "object.h"
#include "particle.h"

class ObjectLink{
public:
	Object *object1, *object2;
	float point1[3], point2[3];
	bool enabled;
};

struct objectlinklist{
	ObjectLink *link;
	objectlinklist *next;
};

#define MAXCONTACTS 100

class World{
private:
	objectlist *childlist;

	int childcount;
	Object **childs;


	int particlecount;
	int maxparticles;
	Particle **particles;


	objectlinklist *linklist;
public:
	World(void);

	void prepare(void);
	void move(void);
	void draw(void);

	void addChild(Object *child);

	void addParticle(Particle *particle);
	void removeParticle(Particle *particle);
	
	//Point is world-relative
	ObjectLink *addLink(Object *object1, Object *object2, float *point);
	void renewLink(ObjectLink *link, float *point);
};

#endif

