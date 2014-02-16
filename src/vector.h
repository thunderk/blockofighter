/*
 * $Id: vector.h,v 1.8 2002/07/19 20:33:29 msell Exp $
 *
 *
 * $Log: vector.h,v $
 * Revision 1.8  2002/07/19 20:33:29  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.7  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.6  2002/06/27 00:08:04  msell
 * Kimmotukset palloille myös pyöritettyihin mesheihin
 *
 * Revision 1.5  2002/06/23 20:12:19  msell
 * Parempi törmäystarkistus palloista mesheihin
 *
 * Revision 1.4  2002/06/17 12:42:46  msell
 * Hieman parempi törmäysmallinnus taas
 *
 * Revision 1.3  2002/06/11 23:23:03  msell
 * Törmäystarkistusta
 *
 * Revision 1.2  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.1  2002/05/16 18:42:07  msell
 * Vektorifunctioita ja kamera
 *
 *
 *
 * $Date: 2002/07/19 20:33:29 $
 *
 */

#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

#include "main.h"

void vectorSet(float *target, float x, float y, float z);
void vectorCopy(float *target, float *source);
void vectorAdd(float *target, float *source1, float *source2);
void vectorAdd(float *target, float *source);
void vectorSub(float *target, float *source);
void vectorSub(float *target, float *source1, float *source2);
void vectorNegative(float *target, float *source);
void vectorNegative(float *target);
void vectorScale(float *target, float *source, float scale);
void vectorScale(float *target, float scale);
float vectorDot(float *source1, float *source2);
float vectorNormalizedDot(float *source1, float *source2);
float vectorLength(float *source);
void vectorCross(float *target, float *source1, float *source2);
void vectorNormalize(float *target, float *source);
void vectorNormalize(float *target);
void vectorReflect(float *target, float *source, float *normal);
bool vectorIsZero(float *vector);
void vectorSaturate(float *target, float *source, float min, float max);
void vectorSaturate(float *vector, float min, float max);

//Projects vector source1 onto vector source2
void vectorProject(float *target, float *source1, float *source2);

void vectorMatrixMultiply(float *target, float *source, float *matrix);



void matrixSet(float *matrix,
							 float x1, float y1, float z1,
							 float x2, float y2, float z2,
							 float x3, float y3, float z3);
void matrixSet(float *matrix, float *r1, float *r2, float *r3);
void matrixCopy(float *target, float *source);
void matrixIdentity(float *matrix);
void matrixAdd(float *target, float *source1, float *source2);
void matrixAdd(float *target, float *source);
void matrixMultiply(float *target, float *source1, float *source2);
//void matrixMultiply(float *target, float *source);
void matrixRotate(float *matrix, float *vector);
void matrixCreateRotation(float *matrix, float *vector);
void matrixTranspose(float *target, float *source);

#endif

