#ifndef __OBJECTFACTORY_H_INCLUDED__
#define __OBJECTFACTORY_H_INCLUDED__

#include "mesh.h"

MeshObject *createPyramid(float width, float height);
MeshObject *createSpherePool(float width, float height);

Mesh *createBox(float x1, float x2, float y1, float y2, float z1, float z2);
Mesh *loadAscModel(char *filename, float scale, float *offset);
Mesh *loadAscModel(char *filename, float scale);
void drawTrophy(void);

#endif
