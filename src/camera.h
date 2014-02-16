/*
 * $Id: camera.h,v 1.4 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: camera.h,v $
 * Revision 1.4  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.3  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.2  2002/06/03 23:06:38  msell
 * no message
 *
 * Revision 1.1  2002/05/16 18:42:07  msell
 * Vektorifunctioita ja kamera
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

class Camera{
private:
	float position[3];
	float target[3];
	float matrix[9];
	float *right, *up, *forward;

	void calculateMatrix(void);

public:
	Camera(void);

	void setPosition(float position[3]);
	void setPosition(float x, float y, float z);
	void getPosition(float *position);
	void setTarget(float target[3]);
	void getTarget(float *target);
	void setUp(float up[3]);
	void getMatrix(float *matrix);

	void moveRight(float amount);
	void moveUp(float amount);
	void moveForward(float amount);

	void glUpdate(void);
};

#endif

