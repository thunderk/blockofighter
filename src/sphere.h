/*
 * $Id: sphere.h,v 1.11 2002/07/19 20:33:29 msell Exp $
 *
 *
 * $Log: sphere.h,v $
 * Revision 1.11  2002/07/19 20:33:29  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.10  2002/07/07 17:53:21  msell
 * Legoukon alku
 *
 * Revision 1.9  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.8  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.7  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.6  2002/06/20 22:50:12  msell
 * Meshit
 *
 * Revision 1.5  2002/06/15 17:18:37  msell
 * Toimiva törmäystarkastus kiinteille laatikoille
 *
 * Revision 1.4  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.3  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 * Revision 1.2  2002/06/07 21:16:51  msell
 * Fysiikkaenginen alkua
 *
 * Revision 1.1  2002/06/05 23:55:46  msell
 * Pallo
 *
 *
 *
 * $Date: 2002/07/19 20:33:29 $
 *
 */

#ifndef __SPHERE_H_INCLUDED__
#define __SPHERE_H_INCLUDED__

#include "object.h"
#include "material.h"
#include "mesh.h"


class SphereAppearance;

//Object for sphere

class Sphere : public Object{
private:
	float r;
	SphereAppearance *appearance;
	SphereShape *geometry;

public:
	Sphere(void);

	void setRadius(float r);
	void setColor(float red, float green, float blue);
};



//Appearance of sphere

class SphereAppearance : public Appearance{
private:
	float r;

public:
	SphereAppearance(void);
	
	void setRadius(float r);
	void draw(void);
};



//Geometry of sphere

class SphereShape : public Shape{
private:
	float r;

public:
	SphereShape(Object *sphere);

	void setRadius(float r);
	float getRadius(void);

	float calculateMomentOfInertia(float *rotationvector);

	bool checkCollision(Object *target);

	bool checkCollisionPeer(SphereShape *target);
	bool checkCollisionPeer(MeshShape *target);

	friend class Sphere;
	friend class MeshShape;
};

#endif

