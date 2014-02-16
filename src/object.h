/*
 * $Id: object.h,v 1.20 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: object.h,v $
 * Revision 1.20  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.19  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.18  2002/07/17 22:45:54  msell
 * Ääniä vähän
 *
 * Revision 1.17  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.16  2002/07/07 23:05:22  msell
 * Osien liimaaminen toisiinsa (kesken)
 *
 * Revision 1.15  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.14  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.13  2002/06/27 14:39:48  msell
 * Toimiva maila :)
 * Pyörivät kappaleet siis antaa liike-energiaa liikkuville kappaleille (ei toisin päin vielä)
 *
 * Revision 1.12  2002/06/27 00:08:04  msell
 * Kimmotukset palloille myös pyöritettyihin mesheihin
 *
 * Revision 1.11  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.10  2002/06/15 22:56:37  msell
 * Säätöä
 *
 * Revision 1.9  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.8  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 * Revision 1.7  2002/06/07 21:16:51  msell
 * Fysiikkaenginen alkua
 *
 * Revision 1.6  2002/06/05 18:39:05  msell
 * Jotain pientä
 *
 * Revision 1.5  2002/06/05 15:00:41  msell
 * Palikoihin lisää detailia, facet jaetaan halutun kokosiin osiin
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

#ifndef __OBJECT_H_INCLUDED__
#define __OBJECT_H_INCLUDED__

class Object;

#define EPSILON 1.0e-20

#include <stdlib.h>

#include "shape.h"
#include "appearance.h"

struct objectlist{
	Object *object;
	objectlist *next;
};

class Object{
public:
	float invmass;

	/* Linear movement:
	 * position          <-> paikka        (x)
	 * velocity          <-> nopeus        (v)
	 * momentum          <-> liikemäärä    (p)
	 * force             <-> voima         (F)
	 *   x' = v
	 *   p' = F
	 *   p  = mv
	 *   F  = ma
	 *   v' = a
	 */

	float position[3];
	//derivative: velocity = momentum / mass

	float momentum[3];//, oldmomentum[3];
	//derivative: force

	//float force[3]; //Temporary properties
	//float externalforce[3];


	/* Angular movement:
	 * rotation             <-> orientaatio                         (R)
	 * angular velocity     <-> kulmanopeus                         (w)
	 * angular momentum     <-> pyörimisliikemäärä, vääntömomentti  (L)
	 * torque               <-> voiman momentti                     (M,T)
	 * moment of inertia    <-> hitausmomentti                      (J,I)
	 * angular acceleration <-> kulmakiihtyvyys                     (a)
	 *      L = J*w
	 *     R' = Star(L) * R
	 *      T = J*a
	 *     w' = a
	 *     L' = T
	 */

	float invmomentofinertia;

	float rotation[9];
	//derivative: StarOperation(angularvelocity) * rotation

	float angularmomentum[3];
	//angular momentum = angular velocity * moment of inertia
	//derivative: torque = angular acceleration * moment of inertia

	//float torque[3]; //Temporary property


	void moveStep(float dt);
	//void applyForces(float dt);

	void calculateStateVariables(void);

	int collisiongroup;

	void addImpulse(float *impulse, float *contactpoint);

	Appearance *appearance;
	Shape *geometry;

	bool gravity;



	Object(void);

	virtual void prepare(void);
	virtual void move(void);
	virtual void draw(void);

	void setPosition(float x, float y, float z);
	void getPosition(float *position);

	//Gets velocity from object and return it in "velocity"
	void getVelocity(float *velocity);

	//Gets velocity from object for point "point" with
	//tangential speed and return it in "velocity"
	void getVelocity(float *velocity, float *point);

	void getTangentialVelocity(float *target, float *point);

	void getMomentum(float *momentum);
	//void getForce(float *force);
	void setMass(float mass);
	float getMass(void);
	void setCollisionGroup(int group);
	int getCollisionGroup(void);

	void transformPoint(float *newpoint, float *oldpoint);
	void unTransformPoint(float *newpoint, float *oldpoint);
	void transformVector(float *newvector, float *oldvector);
	void unTransformVector(float *newvector, float *oldvector);

	void addExternalForce(float *force);

	void setGravity(bool enabled);



	virtual void hitForce(float speed, float *speed2, Object *source);

	






	friend class ObjectLink;
	//friend void collide(Object *source, Object *target, float *normal, float *contactpoint);
	friend bool checkCollisions(Object *object, float *contactnormal);






	//Temporary state variables
	float velocity[3];
	float angularvelocity[3];
};

#endif

