/*
 * $Id: objectfactory.h,v 1.7 2002/07/22 01:14:14 msell Exp $
 *
 *
 * $Log: objectfactory.h,v $
 * Revision 1.7  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 * Revision 1.6  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.5  2002/07/14 21:22:39  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.4  2002/07/11 18:33:06  jkaarlas
 * ascloaderi palauttaa nyt meshin
 *
 * Revision 1.3  2002/06/26 22:30:02  jkaarlas
 * lisätty asc-loaderi
 *
 * Revision 1.2  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.1  2002/06/20 22:50:12  msell
 * Meshit
 *
 *
 *
 * $Date: 2002/07/22 01:14:14 $
 *
 */

#ifndef __OBJECTFACTORY_H_INCLUDED__
#define __OBJECTFACTORY_H_INCLUDED__

#include "mesh.h"

MeshObject* createPyramid(float width, float height);
MeshObject* createSpherePool(float width, float height);


Mesh* createBox(float x1, float x2, float y1, float y2, float z1, float z2);
Mesh* loadAscModel(char* filename, float scale, float* offset);
Mesh* loadAscModel(char* filename, float scale);
void drawTrophy(void);

#endif

