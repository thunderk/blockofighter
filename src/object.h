#ifndef __OBJECT_H_INCLUDED__
#define __OBJECT_H_INCLUDED__

class Object;

#define EPSILON 1.0e-20

#include <stdlib.h>

#include "shape.h"
#include "appearance.h"

struct objectlist {
  Object *object;
  objectlist *next;
};

class Object {
public:
  float invmass;

  /* Linear movement:
   * position          <-> paikka        (x)
   * velocity          <-> nopeus        (v)
   * momentum          <-> liikemäärä    (p)
   * force             <-> voima         (F)
   *   x' = v
   *   p' = F
   *   p  = mv
   *   F  = ma
   *   v' = a
   */

  float position[3];
  // derivative: velocity = momentum / mass

  float momentum[3]; //, oldmomentum[3];
  // derivative: force

  // float force[3]; //Temporary properties
  // float externalforce[3];

  /* Angular movement:
   * rotation             <-> orientaatio                         (R)
   * angular velocity     <-> kulmanopeus                         (w)
   * angular momentum     <-> pyörimisliikemäärä, vääntömomentti  (L)
   * torque               <-> voiman momentti                     (M,T)
   * moment of inertia    <-> hitausmomentti                      (J,I)
   * angular acceleration <-> kulmakiihtyvyys                     (a)
   *      L = J*w
   *     R' = Star(L) * R
   *      T = J*a
   *     w' = a
   *     L' = T
   */

  float invmomentofinertia;

  float rotation[9];
  // derivative: StarOperation(angularvelocity) * rotation

  float angularmomentum[3];
  // angular momentum = angular velocity * moment of inertia
  // derivative: torque = angular acceleration * moment of inertia

  // float torque[3]; //Temporary property

  void moveStep(float dt);
  // void applyForces(float dt);

  void calculateStateVariables(void);

  int collisiongroup;

  void addImpulse(float *impulse, float *contactpoint);

  Appearance *appearance;
  Shape *geometry;

  bool gravity;

  Object(void);

  virtual void prepare(void);
  virtual void move(void);
  virtual void draw(void);

  void setPosition(float x, float y, float z);
  void getPosition(float *position);

  // Gets velocity from object and return it in "velocity"
  void getVelocity(float *velocity);

  // Gets velocity from object for point "point" with
  // tangential speed and return it in "velocity"
  void getVelocity(float *velocity, float *point);

  void getTangentialVelocity(float *target, float *point);

  void getMomentum(float *momentum);
  // void getForce(float *force);
  void setMass(float mass);
  float getMass(void);
  void setCollisionGroup(int group);
  int getCollisionGroup(void);

  void transformPoint(float *newpoint, float *oldpoint);
  void unTransformPoint(float *newpoint, float *oldpoint);
  void transformVector(float *newvector, float *oldvector);
  void unTransformVector(float *newvector, float *oldvector);

  void addExternalForce(float *force);

  void setGravity(bool enabled);

  virtual void hitForce(float speed, float *speed2, Object *source);

  friend class ObjectLink;
  // friend void collide(Object *source, Object *target, float *normal, float
  // *contactpoint);
  friend bool checkCollisions(Object *object, float *contactnormal);

  // Temporary state variables
  float velocity[3];
  float angularvelocity[3];
};

#endif
