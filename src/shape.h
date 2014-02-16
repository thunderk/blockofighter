/*
 * $Id: shape.h,v 1.12 2002/07/19 20:33:29 msell Exp $
 *
 *
 * $Log: shape.h,v $
 * Revision 1.12  2002/07/19 20:33:29  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.11  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.10  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.9  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.8  2002/06/20 22:50:12  msell
 * Meshit
 *
 * Revision 1.7  2002/06/15 17:18:37  msell
 * Toimiva törmäystarkastus kiinteille laatikoille
 *
 * Revision 1.6  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.5  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 * Revision 1.4  2002/06/07 21:16:51  msell
 * Fysiikkaenginen alkua
 *
 * Revision 1.3  2002/06/05 23:55:46  msell
 * Pallo
 *
 * Revision 1.2  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.1  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 *
 *
 * $Date: 2002/07/19 20:33:29 $
 *
 */

#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__

class Shape;
class SphereShape;
class MeshShape;

#include "object.h"

/*
 * Abstract class for object geometry
 */
class Shape{
protected:
	Object *object;

public:
	Shape(Object *object);


	virtual float calculateMomentOfInertia(float *rotationvector) = 0;

	virtual bool checkCollision(Object *target);

	virtual bool checkCollisionPeer(Shape *target);
	virtual bool checkCollisionPeer(SphereShape *target);
	virtual bool checkCollisionPeer(MeshShape *target);
};

#endif

