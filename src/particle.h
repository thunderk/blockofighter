#ifndef __PARTICLE_H_INCLUDED__
#define __PARTICLE_H_INCLUDED__

class Particle;
class BloodAppearance;

#include "object.h"
#include "legoblocks.h"
#include "world.h"

class Particle : public MeshObject {
private:
  int bounces;
  bool enabled;

  World *world;

  bool alive;

public:
  int lifetime;
  int id;

  Particle(World *world, Mesh *mesh);

  void move(void);

  void hitForce(float speed, Object *source);

  void create(float *position, float *velocity);
  void destroy(void);
};

#define MAXBLOOD 500

class BloodAppearance : public BasicBlockAppearance {
private:
  int *lifetime;

public:
  BloodAppearance(int *lifetime);

  void draw(void);
};

void initBloods(World *world);
void createBlood(float *position, float *velocity);
void removeBlood(int id);
void removeAllBlood();

#endif
