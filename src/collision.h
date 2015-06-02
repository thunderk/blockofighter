#ifndef __COLLISION_H_INCLUDED__
#define __COLLISION_H_INCLUDED__

#include "mesh.h"
#include "world.h"

#define COLLISIONGROUP_NONE 0
#define COLLISIONGROUP_ARENA 1
#define COLLISIONGROUP_MAN1 2
#define COLLISIONGROUP_MAN1HAND 3
#define COLLISIONGROUP_MAN2 4
#define COLLISIONGROUP_MAN2HAND 5
#define COLLISIONGROUP_PARTICLE 6

#define COLLISIONFRICTION 0.9

void initCollisions(void);
// void addCollisionObject(Object *object, int group);
void addCollisionLink(int source, int target);
void removeCollisionLink(int source, int target);
bool isCollisionLink(int source, int target);

class Contact {
public:
  Object *object1, *object2;
  float normal[3];
  float position[3];
};

extern Contact *contacts;
extern int contactcount;

// Contact point is world-relative and must be transformed
// into coordinate system of both objects
void addCollision(Object *source, Object *target, float *normal,
                  float *contactpoint);
bool handleCollision(Contact *contact);
bool handleLink(ObjectLink *link);

bool checkSphereMeshCollision(float *sphereposition, float r, Mesh *mesh,
                              float *normal, float *contactpoint);
bool checkPointMeshCollision(float *position, Mesh *mesh, float *normal,
                             float *contactpoint);
bool checkEdgeMeshCollision(float *p1, float *p2, Mesh *mesh, float *normal,
                            float *contactpoint);

#endif
