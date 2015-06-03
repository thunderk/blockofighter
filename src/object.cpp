#include "main.h"

#include <stdlib.h>

#include "object.h"
#include "vector.h"
#include "collision.h"
#include "utils.h"
#include "fight.h"
#include "glapi.h"

Object::Object(void) {
  appearance = NULL;
  geometry = NULL;
  invmass = 0.0;
  setPosition(0, 0, 0);
  vectorSet(momentum, 0, 0, 0);

  invmomentofinertia = 0.0;
  matrixIdentity(rotation);
  vectorSet(angularmomentum, 0, 0, 0);

  setCollisionGroup(COLLISIONGROUP_NONE);
  gravity = false;
}

void Object::prepare(void) {
  if (appearance != NULL)
    appearance->prepare();
}

#define DT 0.01

void Object::move(void) { moveStep(DT); }

void Object::moveStep(float dt) {
  if (invmass == 0)
    return;

  if (vectorDot(momentum, momentum) > 1.0e+5)
    vectorSet(momentum, 0, 0, 0);
  if (vectorDot(angularmomentum, angularmomentum) > 1.0e+5)
    vectorSet(angularmomentum, 0, 0, 0);
  calculateStateVariables();

  float velocitydt[3];
  vectorScale(velocitydt, velocity, dt);
  vectorAdd(position, velocitydt);

  float rotationdt[9];
  if (vectorIsZero(angularmomentum)) {
    matrixIdentity(rotationdt);
  } else {
    float angularvelocitydt[3];
    vectorScale(angularvelocitydt, angularvelocity, dt);
    matrixCreateRotation(rotationdt, angularvelocitydt);
  }
  matrixMultiply(rotation, rotation, rotationdt);

  vectorScale(angularmomentum, 0.99);
}

void Object::calculateStateVariables(void) {
  getVelocity(velocity);

  if (vectorIsZero(angularmomentum)) {
    invmomentofinertia = 0;
  } else {
    invmomentofinertia =
        invmass * 1.0 / geometry->calculateMomentOfInertia(angularmomentum);
  }

  vectorScale(angularvelocity, angularmomentum, invmomentofinertia);
}

void Object::setPosition(float x, float y, float z) {
  position[0] = x;
  position[1] = y;
  position[2] = z;
}

void Object::getPosition(float *position) {
  vectorCopy(position, this->position);
}

void Object::getVelocity(float *velocity) {
  vectorCopy(velocity, momentum);
  vectorScale(velocity, invmass);
}

void Object::getVelocity(float *velocity, float *point) {
  getVelocity(velocity);

  float tangentialvelocity[3];
  getTangentialVelocity(tangentialvelocity, point);
  // float tv[3];
  // transformVector(tv, tangentialvelocity);
  vectorAdd(velocity, tangentialvelocity);
}

void Object::getTangentialVelocity(float *target, float *point) {
  if (vectorIsZero(angularmomentum)) {
    vectorSet(target, 0, 0, 0);
    return;
  }

  vectorCross(target, angularmomentum, point);
  vectorScale(target, invmomentofinertia);
}

void Object::getMomentum(float *momentum) {
  vectorCopy(momentum, this->momentum);
}

void Object::setMass(float mass) {
  if (mass == 0)
    this->invmass = 0;
  else
    this->invmass = 1.0 / mass;
}

float Object::getMass(void) {
  if (invmass == 0)
    return 0;
  return 1.0 / invmass;
}

void Object::setCollisionGroup(int group) { this->collisiongroup = group; }

int Object::getCollisionGroup(void) { return collisiongroup; }

void Object::addImpulse(float *impulse, float *contactpoint) {
  if (invmass == 0)
    return;
  float angularimpulse[3];
  vectorCross(angularimpulse, contactpoint, impulse);
  vectorAdd(angularmomentum, angularimpulse);

  vectorAdd(momentum, impulse);

  float t1[3], t2[3];
  vectorAdd(t1, contactpoint, position);
  vectorNormalize(t2, impulse);
  vectorAdd(t2, t1);

  // addGraphicsVector(t1, t2, vectorLength(impulse));
}

void Object::addExternalForce(float *force) {
  float impulse[3];
  vectorScale(impulse, force, DT);

  float contact[3] = {0, 0, 0};
  this->addImpulse(impulse, contact);
}

void Object::transformPoint(float *newpoint, float *oldpoint) {
  vectorMatrixMultiply(newpoint, oldpoint, rotation);
  vectorAdd(newpoint, position);
}

void Object::unTransformPoint(float *newpoint, float *oldpoint) {
  vectorSub(newpoint, oldpoint, position);
  float rotmat[9];
  matrixTranspose(rotmat, rotation);
  vectorMatrixMultiply(newpoint, newpoint, rotmat);
}

void Object::transformVector(float *newvector, float *oldvector) {
  vectorMatrixMultiply(newvector, oldvector, rotation);
}

void Object::unTransformVector(float *newvector, float *oldvector) {
  float rotmat[9];
  matrixTranspose(rotmat, rotation);
  vectorMatrixMultiply(newvector, oldvector, rotmat);
}

void Object::hitForce(float speed, float *speed2, Object *source) {
  float tolerance = 1.0;
  if (speed > tolerance) {
    Sound *sound;
    if (rand() & 1)
      sound = softhitsound1;
    else
      sound = softhitsound2;
    float volume = (speed - tolerance) * 2;
    if (volume > 1)
      volume = 1;
    sound->setVolume(volume);
    sound->play(30 + random(70));
  }
}

void Object::setGravity(bool enabled) { gravity = enabled; }

void Object::draw(void) {
  glPushMatrix();
  glTranslatef(position[0], position[1], position[2]);

  GLfloat glmatrix[16] = {rotation[0], rotation[1], rotation[2], 0,
                          rotation[3], rotation[4], rotation[5], 0,
                          rotation[6], rotation[7], rotation[8], 0,
                          0,           0,           0,           1};
  glMultMatrixf(glmatrix);

  if (appearance != NULL)
    appearance->draw();

  glPopMatrix();
}
