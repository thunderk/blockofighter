/*
 * $Id: camera.cpp,v 1.5 2002/07/22 01:14:14 msell Exp $
 *
 *
 * $Log: camera.cpp,v $
 * Revision 1.5  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 * Revision 1.4  2002/06/17 20:49:04  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.3  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.2  2002/06/03 23:06:38  msell
 * no message
 *
 * Revision 1.1  2002/05/16 18:42:07  msell
 * Vektorifunctioita ja kamera
 *
 *
 *
 * $Date: 2002/07/22 01:14:14 $
 *
 */

#include "main.h"

#include "camera.h"
#include "vector.h"
#include "glapi.h"

Camera::Camera(void){
	right = &matrix[0];
	up = &matrix[3];
	forward = &matrix[6];

	vectorSet(position, 0, 2, 2);
	vectorSet(target, 0, 0, 0);
	vectorSet(up, 0, 1, 0);

	calculateMatrix();
}

void Camera::setPosition(float position[3]){
	vectorCopy(this->position, position);
}

void Camera::setPosition(float x, float y, float z){
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
}

void Camera::getPosition(float *position){
	vectorCopy(position, this->position);
}

void Camera::setTarget(float target[3]){
	vectorCopy(this->target, target);
}

void Camera::getTarget(float *target){
	vectorCopy(target, this->target);
}

void Camera::setUp(float up[3]){
	vectorCopy(this->up, up);
}

void Camera::getMatrix(float *matrix){
	vectorCopy(&matrix[0], &this->matrix[0]);
	vectorCopy(&matrix[3], &this->matrix[3]);
	vectorCopy(&matrix[6], &this->matrix[6]);
}

void Camera::moveRight(float amount){
	float movevector[3];
	vectorScale(movevector, right, amount);
	vectorAdd(position, movevector);
	//vectorAdd(target, movevector);
	calculateMatrix();
}

void Camera::moveUp(float amount){
	float movevector[3];
	vectorScale(movevector, up, amount);
	vectorAdd(position, movevector);
	//vectorAdd(target, movevector);
	calculateMatrix();
}

void Camera::moveForward(float amount){
	float movevector[3];
	vectorScale(movevector, forward, amount);
	vectorAdd(position, movevector);
	//vectorAdd(target, movevector);
	calculateMatrix();
}

void Camera::glUpdate(void){
	//glLoadIdentity();

	gluLookAt(position[0], position[1], position[2],
						target[0], target[1], target[2],
						up[0], up[1], up[2]);
}

void Camera::calculateMatrix(void){
	vectorSub(forward, target, position);
	vectorNormalize(forward);
	vectorCross(right, forward, up);
}
