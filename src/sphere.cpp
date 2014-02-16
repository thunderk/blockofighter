/*
 * $Id: sphere.cpp,v 1.19 2002/07/19 18:59:46 msell Exp $
 *
 *
 * $Log: sphere.cpp,v $
 * Revision 1.19  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.18  2002/07/07 17:53:21  msell
 * Legoukon alku
 *
 * Revision 1.17  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.16  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.15  2002/06/27 14:39:48  msell
 * Toimiva maila :)
 * Pyörivät kappaleet siis antaa liike-energiaa liikkuville kappaleille (ei toisin päin vielä)
 *
 * Revision 1.14  2002/06/27 00:08:04  msell
 * Kimmotukset palloille myös pyöritettyihin mesheihin
 *
 * Revision 1.13  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.12  2002/06/23 20:12:19  msell
 * Parempi törmäystarkistus palloista mesheihin
 *
 * Revision 1.11  2002/06/20 22:50:12  msell
 * Meshit
 *
 * Revision 1.10  2002/06/20 00:21:19  jkaarlas
 * materiaali- ja tekstuurihommia edistetty
 *
 * Revision 1.9  2002/06/17 20:49:05  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.8  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.7  2002/06/15 17:18:37  msell
 * Toimiva törmäystarkastus kiinteille laatikoille
 *
 * Revision 1.6  2002/06/14 00:26:17  msell
 * 100 kimpoilevaa palloa ja vähän vaimennusta
 *
 * Revision 1.5  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.4  2002/06/11 23:23:03  msell
 * Törmäystarkistusta
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
 * $Date: 2002/07/19 18:59:46 $
 *
 */

#include "main.h"

#include <math.h>

#include "sphere.h"
#include "utils.h"
#include "3dutils.h"
#include "audio.h"
#include "vector.h"
#include "collision.h"
#include "glapi.h"


Sphere::Sphere(void){
	appearance = new SphereAppearance();
	Object::appearance = appearance;
	geometry = new SphereShape(this);
	Object::geometry = geometry;
}

void Sphere::setRadius(float r){
	if (r < 0) r = -r;
	this->r = r;
	appearance->setRadius(r);
	geometry->setRadius(r);
}

SphereAppearance::SphereAppearance(void){
	setRadius(1);
}

void SphereAppearance::setRadius(float r){
	if (r < 0) r = -r;
	this->r = r;
}

void Sphere::setColor(float red, float green, float blue){
	appearance->getMaterial()->setColor(red, green, blue, 1);
}

void SphereAppearance::draw(void){
	material.enable();
	createSphere(r);
}




SphereShape::SphereShape(Object *sphere) : Shape(sphere){
	setRadius(1);
}

void SphereShape::setRadius(float r){
	this->r = r;
}

float SphereShape::getRadius(void){
	return r;
}

bool SphereShape::checkCollision(Object *target){
	return target->geometry->checkCollisionPeer(this);
}

float SphereShape::calculateMomentOfInertia(float *rotationvector){
	return 2.0/3.0*r*r;
}

/*bool SphereShape::checkCollisionPeer(PlaneShape *target){
	float sourceposition[3], targetposition[3];
	object->getPosition(sourceposition);
	target->object->getPosition(targetposition);
	float height = target->height + targetposition[1];

	if (sourceposition[1] - r < height){
		//shotsound->play();
		float normal[3] = {0, 1, 0};

		float contactpoint[3] = {0, target->height, 0};
		collide(object, target->object, normal, contactpoint);
		return true;
	}

	return false;
}*/

bool SphereShape::checkCollisionPeer(SphereShape *target){
	/*float sourceposition[3], targetposition[3];
	object->getPosition(sourceposition);
	target->object->getPosition(targetposition);
	float impact[3];
	vectorSub(impact, sourceposition, targetposition);*/
	float impact[3] = {0, 0, 0};
	object->transformPoint(impact, impact);
	target->object->unTransformPoint(impact, impact);
	float distance2 = vectorDot(impact, impact);

	if (distance2 < (r + target->r)*(r + target->r)){
		/*float temp[3], temp2[3], temp3[3];
		object->getMomentum(temp2);
		target->object->getMomentum(temp3);
		vectorSub(temp, temp2, temp3);
		shotsound->setVolume(1.0-1/(1+vectorLength(temp)*0.5));
		shotsound->play();*/
		float normal[3];
		vectorNormalize(normal, impact);

		float contactpoint[3];
		vectorScale(contactpoint, normal, target->r);

		target->object->transformVector(normal, normal);
		target->object->transformPoint(contactpoint, contactpoint);

		addCollision(object, target->object, normal, contactpoint);

		//vectorAdd(contactnormal, normal);
		
		return true;
	}

	return false;
}

bool between(float x, float x1, float x2){
	if ((x >= x1 && x <=x2) || (x >= x2 && x <=x1)) return true;
	return false;
}

/*bool SphereShape::checkCollisionPeer(BoxShape *target){
	float sourceposition[3], targetposition[3];
	object->getPosition(sourceposition);
	target->object->getPosition(targetposition);
	float x1 = target->x1 + targetposition[0];
	float x2 = target->x2 + targetposition[0];
	float y1 = target->y1 + targetposition[1];
	float y2 = target->y2 + targetposition[1];
	float z1 = target->z1 + targetposition[2];
	float z2 = target->z2 + targetposition[2];
	float points[3][2] = {{x1, x2}, {y1, y2}, {z1, z2}};
	float p[2], op1[2], op2[2];
	float c, oc1, oc2;
	int i;
	float normal[3];
	float *normal2[3];
	//Faces
	for (i = 0; i < 3; i++){
		p[0] = points[i][0];
		p[1] = points[i][1];
		op1[0] = points[(i+1)%3][0];
		op1[1] = points[(i+1)%3][1];
		op2[0] = points[(i+2)%3][0];
		op2[1] = points[(i+2)%3][1];
		c = sourceposition[i];
		oc1 = sourceposition[(i+1)%3];
		oc2 = sourceposition[(i+2)%3];
		normal2[0] = &normal[i];
		normal2[1] = &normal[(i+1)%3];
		normal2[2] = &normal[(i+2)%3];

		if (between(oc1, op1[0], op1[1]) &&
				between(oc2, op2[0], op2[1])){
			if (c < p[0] && c+r > p[0]){
				*normal2[0] = -1;
				*normal2[1] = 0;
				*normal2[2] = 0;
				collide(object, target->object, normal);
				return true;
			}
			if (c > p[1] && c-r < p[1]){
				*normal2[0] = 1;
				*normal2[1] = 0;
				*normal2[2] = 0;
				collide(object, target->object, normal);
				return true;
			}
		}
	}

	//Edges
	for (i = 0; i < 3; i++){
		p[0] = points[i][0];
		p[1] = points[i][1];
		op1[0] = points[(i+1)%3][0];
		op1[1] = points[(i+1)%3][1];
		op2[0] = points[(i+2)%3][0];
		op2[1] = points[(i+2)%3][1];
		c = sourceposition[i];
		oc1 = sourceposition[(i+1)%3];
		oc2 = sourceposition[(i+2)%3];
		normal2[0] = &normal[i];
		normal2[1] = &normal[(i+1)%3];
		normal2[2] = &normal[(i+2)%3];
		float edges[4][2] = {
			{p[0], op1[0]},
			{p[1], op1[0]},
			{p[0], op1[1]},
			{p[1], op1[1]}};

		if (between(oc2, op2[0], op2[1])){
			int j;
			for (j = 0; j < 4; j++){
				float diff[2] = {c - edges[j][0], oc1 - edges[j][1]};
				if (diff[0]*diff[0] + diff[1]*diff[1] < r*r){
					*normal2[0] = diff[0];
					*normal2[1] = diff[1];
					*normal2[2] = 0;
					vectorNormalize(normal);
					collide(object, target->object, normal);
					return true;
				}
			}
		}
	}

	//Corners
	float corners[8][3] = {
		{x1, y1, z1},
		{x1, y1, z2},
		{x1, y2, z1},
		{x1, y2, z2},
		{x2, y1, z1},
		{x2, y1, z2},
		{x2, y2, z1},
		{x2, y2, z2}};
	for (i = 0; i < 8; i++){
		float *corner = corners[i];
		float difference[3];
		vectorSub(difference, sourceposition, corner);
		float length2 = vectorDot(difference, difference);
		if (length2 < r*r){
			float normal[3];
			vectorNormalize(normal, difference);
			collide(object, target->object, normal);
			return true;
		}
	}

	return false;
}*/



bool SphereShape::checkCollisionPeer(MeshShape *target){
	float position[3] = {0, 0, 0};
	object->transformPoint(position, position);
	target->object->unTransformPoint(position, position);
	Mesh *mesh = target->mesh;

	float normal[3];
	float contactpoint[3];

	if (checkSphereMeshCollision(position, r, mesh, normal, contactpoint)){
		target->object->transformVector(normal, normal);
		target->object->transformPoint(contactpoint, contactpoint);
		
		addCollision(object, target->object, normal, contactpoint);

		//vectorAdd(contactnormal, normal);

		return true;
	}
	return false;
}