#ifndef __SPHERE_H_INCLUDED__
#define __SPHERE_H_INCLUDED__

#include "object.h"
#include "material.h"
#include "mesh.h"

class SphereAppearance;

// Object for sphere

class Sphere : public Object {
private:
  float r;
  SphereAppearance *appearance;
  SphereShape *geometry;

public:
  Sphere(void);

  void setRadius(float r);
  void setColor(float red, float green, float blue);
};

// Appearance of sphere

class SphereAppearance : public Appearance {
private:
  float r;

public:
  SphereAppearance(void);

  void setRadius(float r);
  void draw(void);
};

// Geometry of sphere

class SphereShape : public Shape {
private:
  float r;

public:
  SphereShape(Object *sphere);

  void setRadius(float r);
  float getRadius(void);

  float calculateMomentOfInertia(float *rotationvector);

  bool checkCollision(Object *target);

  bool checkCollisionPeer(SphereShape *target);
  bool checkCollisionPeer(MeshShape *target);

  friend class Sphere;
  friend class MeshShape;
};

#endif
