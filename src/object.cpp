/*
 * $Id: object.cpp,v 1.22 2002/07/18 23:05:31 msell Exp $
 *
 *
 * $Log: object.cpp,v $
 * Revision 1.22  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.21  2002/07/17 22:45:54  msell
 * Ääniä vähän
 *
 * Revision 1.20  2002/07/15 15:22:08  msell
 * Parantelua
 *
 * Revision 1.19  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.18  2002/07/14 21:22:39  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.17  2002/07/07 15:29:07  msell
 * Törmäyksien parantelua
 *
 * Revision 1.16  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.15  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.14  2002/06/27 14:39:48  msell
 * Toimiva maila :)
 * Pyörivät kappaleet siis antaa liike-energiaa liikkuville kappaleille (ei toisin päin vielä)
 *
 * Revision 1.13  2002/06/27 00:08:04  msell
 * Kimmotukset palloille myös pyöritettyihin mesheihin
 *
 * Revision 1.12  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.11  2002/06/17 20:49:05  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.10  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.9  2002/06/15 17:18:37  msell
 * Toimiva törmäystarkastus kiinteille laatikoille
 *
 * Revision 1.8  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.7  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 * Revision 1.6  2002/06/07 21:16:51  msell
 * Fysiikkaenginen alkua
 *
 * Revision 1.5  2002/06/05 18:39:05  msell
 * Jotain pientä
 *
 * Revision 1.4  2002/06/05 15:00:41  msell
 * Palikoihin lisää detailia, facet jaetaan halutun kokosiin osiin
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
 * $Date: 2002/07/18 23:05:31 $
 *
 */

#include "main.h"

#include <stdlib.h>

#include "object.h"
#include "vector.h"
#include "collision.h"
#include "utils.h"
#include "fight.h"
#include "glapi.h"

Object::Object(void){
	appearance = NULL;
	geometry = NULL;
	invmass = 0.0;
	setPosition(0, 0, 0);
	vectorSet(momentum, 0, 0, 0);

	invmomentofinertia = 0.0;
	matrixIdentity(rotation);
	vectorSet(angularmomentum, 0, 0, 0);

	setCollisionGroup(COLLISIONGROUP_NONE);
	gravity = false;
}

void Object::prepare(void){
	if (appearance != NULL) appearance->prepare();
}

#define DT 0.01

void Object::move(void){
	moveStep(DT);
}

void Object::moveStep(float dt){
	if (invmass == 0) return;


	if (vectorDot(momentum, momentum) > 1.0e+5) vectorSet(momentum, 0, 0, 0);
	if (vectorDot(angularmomentum, angularmomentum) > 1.0e+5) vectorSet(angularmomentum, 0, 0, 0);
	calculateStateVariables();

	
	float velocitydt[3];
	vectorScale(velocitydt, velocity, dt);
	vectorAdd(position, velocitydt);

	float rotationdt[9];
	if (vectorIsZero(angularmomentum)){
		matrixIdentity(rotationdt);
	} else{
		float angularvelocitydt[3];
		vectorScale(angularvelocitydt, angularvelocity, dt);
		matrixCreateRotation(rotationdt, angularvelocitydt);
	}
	matrixMultiply(rotation, rotation, rotationdt);

	vectorScale(angularmomentum, 0.99);
}

void Object::calculateStateVariables(void){
	getVelocity(velocity);

	if (vectorIsZero(angularmomentum)){
		invmomentofinertia = 0;
	} else{
		invmomentofinertia = invmass * 1.0 / geometry->calculateMomentOfInertia(angularmomentum);
	}

	vectorScale(angularvelocity, angularmomentum, invmomentofinertia);
}

void Object::setPosition(float x, float y, float z){
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Object::getPosition(float *position){
	vectorCopy(position, this->position);
}

void Object::getVelocity(float *velocity){
	vectorCopy(velocity, momentum);
	vectorScale(velocity, invmass);
}

void Object::getVelocity(float *velocity, float *point){
	getVelocity(velocity);

	float tangentialvelocity[3];
	getTangentialVelocity(tangentialvelocity, point);
	//float tv[3];
	//transformVector(tv, tangentialvelocity);
	vectorAdd(velocity, tangentialvelocity);
}

void Object::getTangentialVelocity(float *target, float *point){
	if (vectorIsZero(angularmomentum)){
		vectorSet(target, 0, 0, 0);
		return;
	}

	vectorCross(target, angularmomentum, point);
	vectorScale(target, invmomentofinertia);
}

void Object::getMomentum(float *momentum){
	vectorCopy(momentum, this->momentum);
}

void Object::setMass(float mass){
	if (mass == 0) this->invmass = 0;
	else this->invmass = 1.0 / mass;
}

float Object::getMass(void){
	if (invmass == 0) return 0;
	return 1.0 / invmass;
}

void Object::setCollisionGroup(int group){
	this->collisiongroup = group;
}

int Object::getCollisionGroup(void){
	return collisiongroup;
}

void Object::addImpulse(float *impulse, float *contactpoint){
	if (invmass == 0) return;
	float angularimpulse[3];
	vectorCross(angularimpulse, contactpoint, impulse);
	vectorAdd(angularmomentum, angularimpulse);

	vectorAdd(momentum, impulse);

	float t1[3], t2[3];
	vectorAdd(t1, contactpoint, position);
	vectorNormalize(t2, impulse);
	vectorAdd(t2, t1);

	//addGraphicsVector(t1, t2, vectorLength(impulse));
}

void Object::addExternalForce(float *force){
	float impulse[3];
	vectorScale(impulse, force, DT);

	float contact[3] = {0, 0, 0};
	this->addImpulse(impulse, contact);
}

void Object::transformPoint(float *newpoint, float *oldpoint){
	vectorMatrixMultiply(newpoint, oldpoint, rotation);
	vectorAdd(newpoint, position);
}

void Object::unTransformPoint(float *newpoint, float *oldpoint){
	vectorSub(newpoint, oldpoint, position);
	float rotmat[9];
	matrixTranspose(rotmat, rotation);
	vectorMatrixMultiply(newpoint, newpoint, rotmat);
}

void Object::transformVector(float *newvector, float *oldvector){
	vectorMatrixMultiply(newvector, oldvector, rotation);
}

void Object::unTransformVector(float *newvector, float *oldvector){
	float rotmat[9];
	matrixTranspose(rotmat, rotation);
	vectorMatrixMultiply(newvector, oldvector, rotmat);
}


void Object::hitForce(float speed, float *speed2, Object *source){
	float tolerance = 1.0;
	if (speed > tolerance){
		Sound *sound;
		if (rand()&1) sound = softhitsound1;
		else sound = softhitsound2;
		float volume = (speed-tolerance)*2;
		if (volume > 1) volume = 1;
		sound->setVolume(volume);
		sound->play(30 + random(70));
	}
}




void Object::setGravity(bool enabled){
	gravity = enabled;
}

void Object::draw(void){
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	
	GLfloat glmatrix[16] = {
		rotation[0], rotation[1], rotation[2], 0,
		rotation[3], rotation[4], rotation[5], 0,
		rotation[6], rotation[7], rotation[8], 0,
		0          , 0          , 0          , 1};
	glMultMatrixf(glmatrix);

	if (appearance != NULL) appearance->draw();

	glPopMatrix();
}
