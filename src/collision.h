/*
 * $Id: collision.h,v 1.15 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: collision.h,v $
 * Revision 1.15  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.14  2002/07/15 20:32:35  msell
 * Uudet valot ja ulkoasun parantelua
 *
 * Revision 1.13  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.12  2002/07/10 17:13:44  msell
 * Törmäystarkastelun parantelua
 *
 * Revision 1.11  2002/07/08 22:53:38  msell
 * Säätöä
 *
 * Revision 1.10  2002/07/08 18:28:47  msell
 * Törmäystä ja ukkoja
 *
 * Revision 1.9  2002/07/07 23:05:22  msell
 * Osien liimaaminen toisiinsa (kesken)
 *
 * Revision 1.8  2002/07/07 15:29:07  msell
 * Törmäyksien parantelua
 *
 * Revision 1.7  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.6  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.5  2002/06/27 14:39:48  msell
 * Toimiva maila :)
 * Pyörivät kappaleet siis antaa liike-energiaa liikkuville kappaleille (ei toisin päin vielä)
 *
 * Revision 1.4  2002/06/27 00:08:04  msell
 * Kimmotukset palloille myös pyöritettyihin mesheihin
 *
 * Revision 1.3  2002/06/23 20:12:19  msell
 * Parempi törmäystarkistus palloista mesheihin
 *
 * Revision 1.2  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.1  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __COLLISION_H_INCLUDED__
#define __COLLISION_H_INCLUDED__

#include "mesh.h"

#define COLLISIONGROUP_NONE      0
#define COLLISIONGROUP_ARENA     1
#define COLLISIONGROUP_MAN1      2
#define COLLISIONGROUP_MAN1HAND  3
#define COLLISIONGROUP_MAN2      4
#define COLLISIONGROUP_MAN2HAND  5
#define COLLISIONGROUP_PARTICLE  6

#define COLLISIONFRICTION 0.9

void initCollisions(void);
//void addCollisionObject(Object *object, int group);
void addCollisionLink(int source, int target);
void removeCollisionLink(int source, int target);
bool isCollisionLink(int source, int target);

class Contact{
public:
	Object *object1, *object2;
	float normal[3];
	float position[3];
};

extern Contact *contacts;
extern int contactcount;


//Contact point is world-relative and must be transformed
//into coordinate system of both objects
void addCollision(Object *source, Object *target,
									float *normal, float *contactpoint);
bool handleCollision(Contact *contact);
bool handleLink(ObjectLink *link);

bool checkSphereMeshCollision(float *sphereposition, float r, Mesh *mesh, float *normal, float *contactpoint);
bool checkPointMeshCollision(float *position, Mesh *mesh, float *normal, float *contactpoint);
bool checkEdgeMeshCollision(float *p1, float *p2, Mesh *mesh, float *normal, float *contactpoint);

#endif

