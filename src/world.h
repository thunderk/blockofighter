#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

class World;
class ObjectLink;

#include "object.h"
#include "particle.h"

class ObjectLink {
public:
  Object *object1, *object2;
  float point1[3], point2[3];
  bool enabled;
};

struct objectlinklist {
  ObjectLink *link;
  objectlinklist *next;
};

#define MAXCONTACTS 100

class World {
private:
  objectlist *childlist;

  int childcount;
  Object **childs;

  int particlecount;
  int maxparticles;
  Particle **particles;

  objectlinklist *linklist;

public:
  World(void);

  void setGravity(float grav);

  void prepare(void);
  void move(void);
  void draw(void);

  void addChild(Object *child);

  void addParticle(Particle *particle);
  void removeParticle(Particle *particle);

  // Point is world-relative
  ObjectLink *addLink(Object *object1, Object *object2, float *point);
  void renewLink(ObjectLink *link, float *point);
};

#endif
