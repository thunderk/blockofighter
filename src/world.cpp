#include "world.h"

#include "object.h"
#include "collision.h"
#include "vector.h"

float GRAVITY = 9.81;

World::World(void) {
  childlist = NULL;
  linklist = NULL;
  maxparticles = 500;
  particles = new Particle *[maxparticles];
  particlecount = 0;
}

void World::prepare(void) {
  objectlist *node = childlist;
  childcount = 0;
  while (node != NULL) {
    Object *child = node->object;
    child->prepare();
    node = node->next;
    childcount++;
  }

  childs = new Object *[childcount];
  node = childlist;
  int i = 0;
  while (node != NULL) {
    Object *child = node->object;
    childs[i] = child;
    node = node->next;
    i++;
  }

  contacts = new Contact[MAXCONTACTS]; // childcount*childcount];
}

//#define GRAVITY 1

void World::setGravity(float grav) { GRAVITY = grav; };

void World::move(void) {
  int i, j;

  // Gravity
  float gravity[3];
  vectorSet(gravity, 0, 0, 0);
  for (i = 0; i < childcount; i++) {
    Object *object = childs[i];
    if (object->gravity) {
      gravity[1] = -object->getMass() * GRAVITY;
      object->addExternalForce(gravity);
    }
  }

  /*for (i = 0; i < particlecount; i++){
      Particle *object = particles[i];
      if (object->gravity){
          gravity[1] = -object->getMass()*GRAVITY;
          object->addExternalForce(gravity);
      }
  }*/

  // Collisions
  contactcount = 0;

  for (i = 0; i < childcount; i++) {
    Object *object1 = childs[i];
    int group1 = object1->getCollisionGroup();
    for (j = i + 1; j < childcount; j++) {
      Object *object2 = childs[j];
      int group2 = object2->getCollisionGroup();

      if (isCollisionLink(group1, group2)) {
        object2->geometry->checkCollision(object1);
      }
    }
  }

  /*for (i = 0; i < particlecount; i++){
      Particle *object1 = particles[i];
      int group1 = object1->getCollisionGroup();
      for (j = 0; j < childcount; j++){
          Object *object2 = childs[j];
          int group2 = object2->getCollisionGroup();

          if (isCollisionLink(group1, group2)){
              object2->geometry->checkCollision(object1);
          }
      }
  }*/

  // printf("Contacts: %i\n", contactcount);

  bool contactresponse;

  j = 0;
  do {
    contactresponse = false;

    // Links between objects
    objectlinklist *node = linklist;
    while (node != NULL) {
      ObjectLink *link = node->link;
      if (handleLink(link))
        contactresponse = true;
      node = node->next;
    }

    // Collision contact
    for (i = 0; i < contactcount; i++) {
      Contact *contact = &contacts[i];
      if (handleCollision(contact))
        contactresponse = true;
    }

    j++;
  } while (contactresponse && j < 10);

  /*j = 0;
  do{
      contactresponse = false;

      //Collision contact
      for (i = 0; i < contactcount; i++){
          Contact *contact = &contacts[i];
          if (handleCollision(contact)) contactresponse = true;
      }

      j++;
  } while (contactresponse && j < 10);*/

  /*j = 0;
  do{
      contactresponse = false;

      //Links between objects
      objectlinklist *node = linklist;
      while (node != NULL){
          ObjectLink *link = node->link;
          if (handleLink(link)) contactresponse = true;
          node = node->next;
      }

      j++;
  } while (contactresponse && j < 3);*/

  for (i = 0; i < childcount; i++) {
    childs[i]->move();
  }
  for (i = 0; i < particlecount; i++) {
    particles[i]->move();
  }
}

void World::draw(void) {
  int i;
  for (i = 0; i < childcount; i++)
    childs[i]->draw();
  for (i = 0; i < particlecount; i++)
    particles[i]->draw();
}

void World::addChild(Object *child) {
  objectlist *node = new objectlist;
  node->object = child;
  node->next = childlist;
  childlist = node;
}

void World::addParticle(Particle *particle) {
  if (particlecount < maxparticles) {
    particles[particlecount++] = particle;
  }
}

void World::removeParticle(Particle *particle) {
  int i;
  for (i = 0; i < particlecount; i++) {
    if (particles[i] == particle) {
      particles[i] = particles[particlecount - 1];
      particlecount--;
      break;
    }
  }
}

ObjectLink *World::addLink(Object *object1, Object *object2, float *point) {
  ObjectLink *link = new ObjectLink();
  link->object1 = object1;
  link->object2 = object2;
  if (point != NULL) {
    object1->unTransformPoint(link->point1, point);
    object2->unTransformPoint(link->point2, point);
    link->enabled = true;
  } else {
    link->enabled = false;
  }
  objectlinklist *node = new objectlinklist;
  node->link = link;
  node->next = linklist;
  linklist = node;
  return link;
}

void World::renewLink(ObjectLink *link, float *point) {
  link->object1->unTransformPoint(link->point1, point);
  link->object2->unTransformPoint(link->point2, point);
  link->enabled = true;
}
