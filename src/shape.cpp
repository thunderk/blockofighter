/*
 * $Id: shape.cpp,v 1.7 2002/07/04 21:05:41 msell Exp $
 *
 *
 * $Log: shape.cpp,v $
 * Revision 1.7  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.6  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.5  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.4  2002/06/20 22:50:12  msell
 * Meshit
 *
 * Revision 1.3  2002/06/15 17:18:37  msell
 * Toimiva törmäystarkastus kiinteille laatikoille
 *
 * Revision 1.2  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.1  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 *
 *
 *
 * $Date: 2002/07/04 21:05:41 $
 *
 */

#include "shape.h"

Shape::Shape(Object *object){
	this->object = object;
}

bool Shape::checkCollision(Object *target){
	return false;
}
bool Shape::checkCollisionPeer(Shape *target){
	return false;
}
bool Shape::checkCollisionPeer(SphereShape *target){
	return false;
}
bool Shape::checkCollisionPeer(MeshShape *target){
	return false;
}
