#include "main.h"

#include <math.h>

#include "particle.h"
#include "vector.h"
#include "utils.h"
#include "world.h"
#include "objectfactory.h"
#include "collision.h"
#include "glapi.h"

Particle::Particle(World *world, Mesh *mesh) : MeshObject(mesh) {
  this->world = world;
}

Contact *contact = new Contact();

int bloodcount;

void Particle::move(void) {
  /*if (position[1] + momentum[1] < 0.5){
      currentparticle->velocity.x*=0.8;
      currentparticle->velocity.y=fabs(currentparticle->velocity.y)*0.8;
      currentparticle->velocity.z*=0.8;
      currentparticle->bounces++;
  }
  currentparticle->position.x+=currentparticle->velocity.x;
  currentparticle->position.y+=currentparticle->velocity.y;
  currentparticle->position.z+=currentparticle->velocity.z;
  currentparticle->angle.x+=currentparticle->velocity.x*50;
  currentparticle->angle.y+=currentparticle->velocity.y*50;
  currentparticle->angle.z+=currentparticle->velocity.z*50;
  currentparticle->velocity.y-=0.003;
  if (currentparticle->bounces==3) dieParticle(currentparticle);*/
  momentum[1] -= 0.02;
  int i;
  vectorSet(contact->normal, 0, 1, 0);
  contact->object2 = NULL;
  // UNUSED//bool die = false;
  for (i = 0; i < mesh->vertexcount; i++) {
    float point[3];
    transformPoint(point, mesh->vertices[i].position);
    if (point[1] < 0) {
      contact->object1 = this;
      vectorCopy(contact->position, point);
      handleCollision(contact);
      /*float impulse[3];
      getMomentum(impulse);
      impulse[0] = 0;
      impulse[1] = fabs(impulse[1]);
      impulse[2] = 0;
      vectorScale(impulse, 1.1);
      addImpulse(impulse, point);
      position[1] -= point[1];
      momentum[1] = impulse[1]*0.5;*/
    }
  }
  /*if (vectorLength(momentum) < 0.5) die = true;
  if (die) removeBlood(id);*/
  lifetime++;
  Object::move();

  if (lifetime > 300)
    removeBlood(id);
}

void Particle::hitForce(float speed, Object *source) {
  /*bounces++;
  if (bounces == 2){
      removeBlood(id);
  }*/
}

void Particle::create(float *position, float *velocity) {
  vectorCopy(this->position, position);
  vectorCopy(this->momentum, velocity);
  float rotate[3] = {randomf(2) - 1, randomf(2) - 1, randomf(2) - 1};
  vectorCopy(this->angularmomentum, rotate);
  bounces = 0;
  lifetime = 0;
  world->addParticle(this);
}

void Particle::destroy(void) { world->removeParticle(this); }

Particle **bloodparticles;

BloodAppearance::BloodAppearance(int *lifetime)
    : BasicBlockAppearance(1, 1, 1) {
  this->lifetime = lifetime;
  usematerial = false;
}

void BloodAppearance::draw(void) {
  glPushMatrix();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  float alpha = 1 - *lifetime * 0.003;
  if (alpha < 0)
    alpha = 0;

  glColor4f(1, 0, 0, alpha); // 1.0/(1+*lifetime*0.004));

  glScalef(0.5, 0.5, 0.5);
  BasicBlockAppearance::draw();

  glDisable(GL_BLEND);

  glPopMatrix();
}

World *bloodworld;

void initBloods(World *world) {
  bloodcount = 0;
  bloodparticles = new Particle *[MAXBLOOD];
  int i;
  Mesh *bloodmesh =
      createBox(-0.5, 0.5, -0.5 * BLOCKHEIGHT, 0.5 * BLOCKHEIGHT, -0.5, 0.5);
  for (i = 0; i < MAXBLOOD; i++) {
    bloodparticles[i] = new Particle(world, bloodmesh);
    bloodparticles[i]->appearance =
        new BloodAppearance(&(bloodparticles[i]->lifetime));
    bloodparticles[i]->setMass(1);
    bloodparticles[i]->prepare();
    // bloodparticles[i]->setGravity(true);
    // bloodparticles[i]->setCollisionGroup(COLLISIONGROUP_PARTICLE);
    // bloodparticles[i]->id = i;
  }
  bloodworld = world;
}

void createBlood(float *position, float *velocity) {
  if (bloodcount < MAXBLOOD) {
    Particle *currentparticle = bloodparticles[bloodcount];
    currentparticle->create(position, velocity);
    currentparticle->id = bloodcount;
    bloodcount++;
  }
}

void removeBlood(int id) {
  Particle *particle = bloodparticles[id];
  particle->destroy();
  bloodparticles[id] = bloodparticles[bloodcount - 1];
  bloodparticles[id]->id = id;
  bloodparticles[bloodcount - 1] = particle;
  bloodcount--;
}

void removeAllBlood() {
  while (bloodcount > 0) {
    removeBlood(0);
  }
}
