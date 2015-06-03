#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__

class Shape;
class SphereShape;
class MeshShape;

#include "object.h"

/*
 * Abstract class for object geometry
 */
class Shape {
protected:
  Object *object;

public:
  Shape(Object *object);

  virtual float calculateMomentOfInertia(float *rotationvector) = 0;

  virtual bool checkCollision(Object *target);

  virtual bool checkCollisionPeer(Shape *target);
  virtual bool checkCollisionPeer(SphereShape *target);
  virtual bool checkCollisionPeer(MeshShape *target);
};

#endif
