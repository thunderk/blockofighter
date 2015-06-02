#include "main.h"

#include <math.h>

#include "legoman.h"
#include "object.h"
#include "sphere.h"
#include "world.h"
#include "legoblocks.h"
#include "vector.h"
#include "collision.h"
#include "objectfactory.h"
#include "utils.h"
#include "particle.h"
#include "fight.h"
#include "fonct.h"
#include "glapi.h"

BodyPart::BodyPart(Legoman *parent, float strength) {
  this->parent = parent;
  this->strength = strength;
  reset();
}

void BodyPart::reset(void) {
  this->energy = 1;
  this->attached = true;
  this->immortal = 0;
  vectorSet(position, 0, 0, 0);
  vectorSet(momentum, 0, 0, 0);
  matrixIdentity(rotation);
  vectorSet(angularmomentum, 0, 0, 0);
  vectorSet(velocity, 0, 0, 0);
  vectorSet(angularvelocity, 0, 0, 0);
}

void BodyPart::move(void) {
  if (immortal > 0)
    immortal--;
  Object::move();
}

void BodyPart::hitForce(float speed, float *speed2, Object *source) {
  if (parent->isHarmfulObject(source)) {
    float tolerance = 0.3;
    if (speed > tolerance) {
      Sound *sound;
      sound = hitsound1;
      float volume = (speed - tolerance) * 0.4;
      if (volume > 1)
        volume = 1;
      volume = 1;
      sound->setVolume(volume);
      sound->play(30 + random(120));

      int i;
      for (i = 0; i < (int)(speed - 0.5); i++) {
        float vel[3] = {randomf(2) - 1, randomf(3), randomf(2) - 1};
        vectorAdd(vel, speed2);
        createBlood(position, vel);
      }

      // makeDamage(0.1);
      if (this == parent->head && source == parent->opponent->head) {
        speed *= 0.1;
      }
      makeDamage(speed * 0.1);
    }
  } else {
    Object::hitForce(speed, speed2, source);
  }
}

void BodyPart::makeDamage(float amount) {
  if (strength == 0)
    return;
  if (energy == 0)
    return;
  if (!parent->opponent->isAlive())
    return;
  if (immortal > 0)
    return;

  energy -= amount / strength;
  if (energy < 0)
    energy = 0;
  if (energy == 0) {
    parent->releasePart(this);
  }
  immortal = 30;
}

bool BodyPart::isInContact() {
  if (!isAttached())
    return false;

  Object *obj = (Object *)this;
  int collgroup = obj->getCollisionGroup();

  for (int i = 0; i < contactcount; i++) {
    if (contacts[i].object1 == obj) {
      if (contacts[i].object2->getCollisionGroup() != collgroup)
        return true;
    } else if (contacts[i].object2 == obj) {
      if (contacts[i].object1->getCollisionGroup() != collgroup)
        return true;
    }
  }
  return false;
}

Sensor::Sensor() {}

void Sensor::attach(Object *object, float *relativeposition) {
  vectorCopy(this->relativeposition, relativeposition);
  this->object = object;
  update();
  update();
  update();
  update();
}

void Sensor::attach(Object *object) {
  float position[3] = {0, 0, 0};
  attach(object, position);
}

void Sensor::update(void) {
  vectorCopy(oldposition, position);
  vectorCopy(oldvelocity, velocity);

  object->transformPoint(position, relativeposition);

  vectorSub(velocity, position, oldposition);
  vectorSub(acceleration, velocity, oldvelocity);

  // printf("V: %f, %f, %f\n", velocity[0], velocity[1], velocity[2]);
}

void Sensor::getPosition(float *target) { vectorCopy(target, position); }

void Sensor::getVelocity(float *target) { vectorCopy(target, velocity); }

void Sensor::getAcceleration(float *target) {
  vectorCopy(target, acceleration);
}

// float rightHandOffset[3] = {-0.60, 0.45, 0.0};
float rightHandOffset[3] = {-0.40, 0.45, 0.0};
// float leftHandOffset[3] = {0.60, 0.46, 0.0};
float leftHandOffset[3] = {0.40, 0.46, 0.0};
// float leftPalmOffset[3] = {0.28, -0.3, -0.38};
float leftPalmOffset[3] = {0.08, -0.3, -0.38};
// float rightPalmOffset[3] = {-0.30, -0.3, -0.38};
float rightPalmOffset[3] = {-0.10, -0.3, -0.38};
float waistOffset[3] = {0.0, 0.2, 0.0};
float rightLegOffset[3] = {-0.15, 0.4, 0.0};
float leftLegOffset[3] = {0.1, 0.4, 0.0};

Legoman::Legoman(int side) {
  this->side = side;

  int collisiongroup = 0, collisiongrouphand = 0;
  if (side == PLAYER1) {
    collisiongroup = COLLISIONGROUP_MAN1;
    collisiongrouphand = COLLISIONGROUP_MAN1HAND;
  }
  if (side == PLAYER2) {
    collisiongroup = COLLISIONGROUP_MAN2;
    collisiongrouphand = COLLISIONGROUP_MAN2HAND;
  }

  float torsocolor[3], legcolor[3];

  if (side == PLAYER1) {
    vectorSet(torsocolor, 1, 0, 0);
    vectorSet(legcolor, 0, 0, 1);
  } else if (side == PLAYER2) {
    vectorSet(torsocolor, 0, 0, 1);
    vectorSet(legcolor, 1, 0, 0);
  }

  // Legs
  Mesh *geomLegMesh = createBox(-0.45, 0.45, -BLOCKHEIGHT * LEGHEIGHT / 2.0,
                                BLOCKHEIGHT * LEGHEIGHT / 2.0, -0.5, 0.5);
  // UNUSED//float tmpScale = 1.0;

  // Left leg
  {
    leftleg = new BodyPart(this, 3);
    Mesh *leftLegMesh =
        loadAscModel((char *)LEFTLEGASC, MODELSCALE, leftLegOffset);
    MeshShape *leftLegGeom = new MeshShape(leftleg, geomLegMesh);
    leftleg->geometry = leftLegGeom;
    leftleg->appearance = new MeshAppearance(leftLegMesh);
    // leftleg->appearance = new MeshAppearance(geomLegMesh);
    leftleg->appearance->material.setColor(legcolor[0], legcolor[1],
                                           legcolor[2], 1);
    vectorSet(leftleg->position, -0.6, BLOCKHEIGHT * (LEGHEIGHT / 2.0), 0);
    leftleg->setGravity(true);
    leftleg->setMass(LEGHEIGHT / 3.0);
    leftleg->setCollisionGroup(collisiongroup);
  }

  // Right leg
  {
    rightleg = new BodyPart(this, 3);
    Mesh *rightLegMesh =
        loadAscModel((char *)RIGHTLEGASC, MODELSCALE, rightLegOffset);
    MeshShape *rightLegGeom = new MeshShape(rightleg, geomLegMesh);
    rightleg->geometry = rightLegGeom;
    rightleg->appearance = new MeshAppearance(rightLegMesh);
    // rightleg->appearance = new MeshAppearance(geomLegMesh);
    rightleg->appearance->material.setColor(legcolor[0], legcolor[1],
                                            legcolor[2], 1);
    vectorSet(rightleg->position, 0.6, BLOCKHEIGHT * (LEGHEIGHT / 2.0), 0);
    rightleg->setGravity(true);
    rightleg->setMass(LEGHEIGHT / 3.0);
    rightleg->setCollisionGroup(collisiongroup);
  }

  // Waist
  {
    waist = new BodyPart(this, 0);
    Mesh *waistMesh = loadAscModel((char *)WAISTASC, MODELSCALE, waistOffset);
    MeshAppearance *waistappearance = new MeshAppearance(waistMesh);
    waistappearance->material.setColor(0, 1, 0, 1);

    Mesh *waistGeomMesh = createBox(-1 + 0.1, 1 - 0.1, 0,
                                    BLOCKHEIGHT * WAISTHEIGHT / 2.0, 0.1, 0.4);
    MeshShape *waistgeometry = new MeshShape(waist, waistGeomMesh);
    waist->geometry = waistgeometry;
    waist->appearance = waistappearance;
    // waist->appearance = new MeshAppearance(waistGeomMesh);
    vectorSet(waist->position, 0, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT / 2.0),
              0);
    waist->setGravity(true);
    waist->setMass(2 * WAISTHEIGHT / 3.0);
    waist->setCollisionGroup(collisiongroup);
  }

  // Torso
  {
    torso = new BodyPart(this, 3);
    Mesh *torsoMesh = loadAscModel((char *)TORSOASC, TORSOSCALE);
    // int i;
    // for (i = 0; i < torsoMesh->polygoncount; i++)
    // torsoMesh->polygons[i].smooth = false;
    MeshAppearance *torsoAppearance = new MeshAppearance(torsoMesh);
    torsoAppearance->material.setColor(torsocolor[0], torsocolor[1],
                                       torsocolor[2], 1);
    Mesh *torsoGeomMesh = createBox(-1, 1, -BLOCKHEIGHT * TORSOHEIGHT / 2.0,
                                    BLOCKHEIGHT * TORSOHEIGHT / 2.0, -0.5, 0.5);
    MeshShape *torsogeometry = new MeshShape(torso, torsoGeomMesh);
    torso->geometry = torsogeometry;
    torso->appearance = torsoAppearance;
    // torso->appearance = new MeshAppearance(torsoGeomMesh);
    vectorSet(torso->position, 0,
              BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT / 2.0), 0);
    torso->setGravity(true);
    torso->setMass(2 * TORSOHEIGHT / 3.0);
    torso->setCollisionGroup(collisiongroup);
  }

  // Hands
  // Mesh *handMeshGeom = createBox(-0.4, 0.4, -BLOCKHEIGHT*HANDHEIGHT/2.0,
  // BLOCKHEIGHT*HANDHEIGHT/2.0, -0.5, 0.5);
  Mesh *handMeshGeom = createBox(-0.2, 0.2, -BLOCKHEIGHT * HANDHEIGHT / 2.0,
                                 BLOCKHEIGHT * HANDHEIGHT / 2.0, -0.5, 0.5);

  // Left hand
  {
    lefthand = new BodyPart(this, 2);

    Mesh *leftHandMesh =
        loadAscModel((char *)LEFTARMASC, MODELSCALE, leftHandOffset);
    Mesh *leftPalmMesh =
        loadAscModel((char *)LEFTPALMASC, MODELSCALE, leftPalmOffset);
    MultiAppearance *a = new MultiAppearance();
    Appearance *arm = new MeshAppearance(leftHandMesh);
    Appearance *palm = new MeshAppearance(leftPalmMesh);
    arm->material.setColor(torsocolor[0], torsocolor[1], torsocolor[2], 1);
    palm->material.setColor(1, 1, 0, 1);
    a->addAppearance(arm);
    a->addAppearance(palm);
    MeshShape *lefthandgeometry = new MeshShape(lefthand, handMeshGeom);
    lefthand->geometry = lefthandgeometry;
    lefthand->appearance = a; // new MeshAppearance(leftHandMesh);
    // lefthand->appearance = new MeshAppearance(handMeshGeom);
    // lefthand->appearance->material.setColor(1, 0, 0, 1);
    vectorSet(lefthand->position, -1.3,
              BLOCKHEIGHT *
                  (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT - HANDHEIGHT / 2.0),
              0);
    lefthand->setGravity(true);
    lefthand->setMass(HANDHEIGHT / 3.0);
    lefthand->setCollisionGroup(collisiongrouphand);
  }

  // Right hand
  {
    righthand = new BodyPart(this, 2);
    Mesh *rightHandMesh =
        loadAscModel((char *)RIGHTARMASC, MODELSCALE, rightHandOffset);
    Mesh *rightPalmMesh =
        loadAscModel((char *)RIGHTPALMASC, MODELSCALE, rightPalmOffset);
    MultiAppearance *a = new MultiAppearance();
    Appearance *arm = new MeshAppearance(rightHandMesh);
    arm->material.setColor(torsocolor[0], torsocolor[1], torsocolor[2], 1);
    Appearance *palm = new MeshAppearance(rightPalmMesh);
    palm->material.setColor(1, 1, 0, 1);
    a->addAppearance(arm);
    a->addAppearance(palm);
    MeshShape *righthandgeometry = new MeshShape(righthand, handMeshGeom);
    righthand->geometry = righthandgeometry;
    righthand->appearance = a;
    // righthand->appearance = new MeshAppearance(handMeshGeom);
    vectorSet(righthand->position, 1.3,
              BLOCKHEIGHT *
                  (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT - HANDHEIGHT / 2.0),
              0);
    righthand->setGravity(true);
    righthand->setMass(HANDHEIGHT / 3.0);
    righthand->setCollisionGroup(collisiongrouphand);
  }

  // Head
  {
    head = new BodyPart(this, 2);
    Appearance *headappearance = new HeadAppearance();
    float r = BLOCKHEIGHT * HEADHEIGHT / 2;
    /*SphereAppearance *headappearance = new SphereAppearance();
    headappearance->setRadius(r);
    headappearance->material.setColor(1, 1, 0, 1);*/
    SphereShape *headgeometry = new SphereShape(head);
    headgeometry->setRadius(r);
    head->geometry = headgeometry;
    head->appearance = headappearance;
    vectorSet(head->position, 0,
              BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT +
                             HEADHEIGHT / 2 + 0.5),
              0);
    head->setGravity(true);
    head->setMass(4.0 / 3 * PI * r * r * r);
    head->setCollisionGroup(collisiongroup);
  }

  headsensor = new Sensor();
  torsosensor = new Sensor();

  headvisual = new DamageVisual(head, damageHead, false, -0.5, -2, 0.5, -1);

  torsovisual = new DamageVisual(torso, damageTorso, false, -0.5, -1, 0.5, 0);

  lefthandvisual =
      new DamageVisual(lefthand, damageHand, true, 0.4, -1, 0.9, 0);

  righthandvisual =
      new DamageVisual(righthand, damageHand, true, -0.4, -1, -0.9, 0);

  leftlegvisual = new DamageVisual(leftleg, damageLeg, true, 0, 0, 0.5, 1);

  rightlegvisual = new DamageVisual(rightleg, damageLeg, true, -0, 0, -0.5, 1);

  harmfulobjects = NULL;

  walkphase = 0;
  jumpphase = 0;
  hitside = 0;

  alive = true;
}

void Legoman::insertToWorld(World *world) {
  this->world = world;

  world->addChild(rightleg);
  world->addChild(leftleg);
  world->addChild(waist);
  world->addChild(torso);
  world->addChild(lefthand);
  world->addChild(righthand);
  world->addChild(head);
  float linkpoint[3];

  vectorSet(linkpoint, 0,
            BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT + HEADHEIGHT),
            0);
  headlinks[0] = world->addLink(head, torso, linkpoint);

  vectorSet(linkpoint, 0, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT),
            0);
  headlinks[1] = world->addLink(head, torso, linkpoint);

  vectorSet(linkpoint, 0, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT +
                                         HEADHEIGHT * 0.5),
            1);
  headlinks[2] = world->addLink(head, torso, linkpoint);

  head->attached = true;

  vectorSet(linkpoint, -1,
            BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT) - 0.5, 0);
  lefthandlinks[0] = world->addLink(torso, lefthand, linkpoint);

  vectorSet(linkpoint, -2,
            BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT) - 0.5, 0);
  lefthandlinks[1] = world->addLink(torso, lefthand, linkpoint);

  lefthand->attached = true;

  vectorSet(linkpoint, 1,
            BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT) - 0.5, 0);
  righthandlinks[0] = world->addLink(torso, righthand, linkpoint);

  vectorSet(linkpoint, 2,
            BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT) - 0.5, 0);
  righthandlinks[1] = world->addLink(torso, righthand, linkpoint);

  righthand->attached = true;

  vectorSet(linkpoint, -1, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT), -0.5);
  world->addLink(torso, waist, linkpoint);

  vectorSet(linkpoint, 1, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT), -0.5);
  world->addLink(torso, waist, linkpoint);

  vectorSet(linkpoint, -1, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT), 0.5);
  world->addLink(torso, waist, linkpoint);

  vectorSet(linkpoint, 1, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT), 0.5);
  world->addLink(torso, waist, linkpoint);

  waist->attached = true;

  vectorSet(linkpoint, -1, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT) - 0.5, 0);
  leftleglinks[0] = world->addLink(waist, leftleg, linkpoint);

  vectorSet(linkpoint, 0, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT) - 0.5, 0);
  leftleglinks[1] = world->addLink(waist, leftleg, linkpoint);

  lll = leftleglinks[1];

  leftleg->attached = true;

  vectorSet(linkpoint, 0, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT) - 0.5, 0);
  rightleglinks[0] = world->addLink(waist, rightleg, linkpoint);

  vectorSet(linkpoint, 1, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT) - 0.5, 0);
  rightleglinks[1] = world->addLink(waist, rightleg, linkpoint);

  rll = rightleglinks[0];

  rightleg->attached = true;

  leftleglinks[2] = world->addLink(waist, leftleg, NULL);
  leftleglink = leftleglinks[2];
  leftleglink->enabled = false;
  rightleglinks[2] = world->addLink(waist, rightleg, NULL);
  rightleglink = rightleglinks[2];
  rightleglink->enabled = false;

  lefthandlinks[2] = world->addLink(torso, lefthand, NULL);
  lefthandlink = lefthandlinks[2];
  lefthandlink->enabled = false;
  righthandlinks[2] = world->addLink(torso, righthand, NULL);
  righthandlink = righthandlinks[2];
  righthandlink->enabled = false;
}

void Legoman::heal(void) {
  headlinks[0]->enabled = true;
  headlinks[1]->enabled = true;
  headlinks[2]->enabled = true;
  lefthandlinks[0]->enabled = true;
  lefthandlinks[1]->enabled = true;
  lefthandlinks[2]->enabled = true;
  righthandlinks[0]->enabled = true;
  righthandlinks[1]->enabled = true;
  righthandlinks[2]->enabled = true;
  leftleglinks[0]->enabled = true;
  leftleglinks[1]->enabled = true;
  leftleglinks[2]->enabled = true;
  rightleglinks[0]->enabled = true;
  rightleglinks[1]->enabled = true;
  rightleglinks[2]->enabled = true;

  leftleglink->enabled = false;
  rightleglink->enabled = false;
  lefthandlink->enabled = false;
  righthandlink->enabled = false;

  leftleg->reset();
  rightleg->reset();
  waist->reset();
  torso->reset();
  lefthand->reset();
  righthand->reset();
  head->reset();
  vectorSet(leftleg->position, -0.6, BLOCKHEIGHT * (LEGHEIGHT / 2.0), 0);
  vectorSet(rightleg->position, 0.6, BLOCKHEIGHT * (LEGHEIGHT / 2.0), 0);
  vectorSet(waist->position, 0, BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT / 2.0),
            0);
  vectorSet(torso->position, 0,
            BLOCKHEIGHT * (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT / 2.0), 0);
  vectorSet(lefthand->position, -1.3,
            BLOCKHEIGHT *
                (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT - HANDHEIGHT / 2.0),
            0);
  vectorSet(righthand->position, 1.3,
            BLOCKHEIGHT *
                (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT - HANDHEIGHT / 2.0),
            0);
  vectorSet(head->position, 0,
            BLOCKHEIGHT *
                (LEGHEIGHT + WAISTHEIGHT + TORSOHEIGHT + HEADHEIGHT / 2 + 0.5),
            0);

  walkphase = 0;
  jumpphase = 0;

  headsensor->attach(head);
  torsosensor->attach(torso);

  alive = true;
}

void Legoman::lockPart(int part) {
  if (part & LEFTLEG && leftleg->energy > 0) {
    float linkpoint[3];
    vectorScale(linkpoint, &leftleg->rotation[3], -1);
    // vectorAdd(linkpoint, leftleg->position);
    vectorAdd(linkpoint, waist->position);
    vectorAdd(linkpoint, lll->point1);
    world->renewLink(leftleglink, linkpoint);
  }
  if (part & RIGHTLEG && rightleg->energy > 0) {
    float linkpoint[3];
    vectorScale(linkpoint, &rightleg->rotation[3], -1);
    // vectorAdd(linkpoint, rightleg->position);
    vectorAdd(linkpoint, waist->position);
    vectorAdd(linkpoint, rll->point1);
    world->renewLink(rightleglink, linkpoint);
  }
  if (part & LEFTHAND && lefthand->energy > 0) {
    float linkpoint[3];
    vectorScale(linkpoint, &lefthand->rotation[3], -1);
    vectorAdd(linkpoint, lefthand->position);
    world->renewLink(lefthandlink, linkpoint);
  }
  if (part & RIGHTHAND && righthand->energy > 0) {
    float linkpoint[3];
    vectorScale(linkpoint, &righthand->rotation[3], -1);
    vectorAdd(linkpoint, righthand->position);
    world->renewLink(righthandlink, linkpoint);
  }

  headsensor->attach(head);
  torsosensor->attach(torso);
}

void Legoman::addHarmfulObject(Object *object) {
  objectlist *node = new objectlist();
  node->object = object;
  node->next = harmfulobjects;
  harmfulobjects = node;
}

bool Legoman::isHarmfulObject(Object *object) {
  objectlist *node = harmfulobjects;
  while (node != NULL) {
    if (node->object == object)
      return true;
    node = node->next;
  }
  return false;
}

float Legoman::getInvMass(void) {
  float mass = torso->getMass() + waist->getMass();
  if (head->attached)
    mass += head->getMass();
  if (lefthand->attached)
    mass += lefthand->getMass();
  if (righthand->attached)
    mass += righthand->getMass();
  if (leftleg->attached)
    mass += leftleg->getMass();
  if (rightleg->attached)
    mass += rightleg->getMass();
  return 1.0 / mass;
}

void Legoman::addOpponent(Legoman *opponent) {
  this->opponent = opponent;
  opponent->addHarmfulObject(head);
  opponent->addHarmfulObject(lefthand);
  opponent->addHarmfulObject(righthand);
  opponent->addHarmfulObject(leftleg);
  opponent->addHarmfulObject(rightleg);
}

void Legoman::unlockPart(int part) {
  if (part & LEFTLEG) {
    leftleglink->enabled = false;
  }
  if (part & RIGHTLEG) {
    rightleglink->enabled = false;
  }
  if (part & LEFTHAND) {
    lefthandlink->enabled = false;
  }
  if (part & RIGHTHAND) {
    righthandlink->enabled = false;
  }
}

void Legoman::move(float *movement) {
  vectorAdd(leftleg->position, movement);
  vectorAdd(rightleg->position, movement);
  vectorAdd(waist->position, movement);
  vectorAdd(torso->position, movement);
  vectorAdd(lefthand->position, movement);
  vectorAdd(righthand->position, movement);
  vectorAdd(head->position, movement);
}

#define LEGSPEED 0.03

#define BALANCEANGLE (PI / 12)

void Legoman::balance(void) {
  if (!alive || !head->attached)
    return;

  float headpos[3], torsopos[3];
  headsensor->getPosition(headpos);
  torsosensor->getPosition(torsopos);
  float posdiff[3];
  vectorSub(posdiff, headpos, torsopos);
  float posdifflen = vectorLength(posdiff);
  float angle = acos(posdiff[1] / posdifflen);

  float headtarget[3];
  vectorSet(headtarget, 0, posdifflen, 0);
  vectorAdd(headtarget, torsopos);

  float force[3];
  vectorSub(force, headtarget, headpos);

  float headvel[3], torsovel[3];
  headsensor->getVelocity(headvel);
  torsosensor->getVelocity(torsovel);
  float veldiff[3];
  vectorSub(veldiff, headvel, torsovel);
  vectorScale(veldiff, 50);

  vectorSaturate(veldiff, 0, 10);

  vectorSub(force, veldiff);

  if (angle < BALANCEANGLE) {
    vectorScale(force, pow(1 - angle / BALANCEANGLE, 0.1));
    vectorScale(force, 100);
    head->addExternalForce(force);
  }

  if (walkdelay == 0) {
    if (walkphase > 0) {
      walkphase--;
      updateLegs();
    }
  }

  vectorScale(lefthand->angularmomentum, 0.98);
  vectorScale(righthand->angularmomentum, 0.98);
}

void Legoman::update(void) {
  if (walkdelay > 0) {
    walkdelay--;
  }

  /*if (jumpphase > 0){
          jumpphase--;
  }*/

  // if (torso->momentum[1] < 0 && isOnGround()){
  // if (torso->momentum[1] < 0 && (isStanding() || isOnGround())){
  if (leftleg->isInContact() || rightleg->isInContact() ||
      (torso->momentum[1] < 0 && isOnGround())) {
    jumpphase--;
    if (jumpphase == 0) {
      jumpenabled = true;
      leftleg->setGravity(true);
      rightleg->setGravity(true);
    }
  }

  if (hitside < 10)
    hitside += 2;
  // hitside = -hitside;
  /*if (hitside > 0){
      hitside = -hitside;
  }/* else{
      hitside = 0;
  }*/

  if (alive) {
    if (head->position[1] < 0) { // && torso->momentum[1] < 0){
      fallOff();
    }

    headsensor->update();
    torsosensor->update();

    balance();
  }
}

void Legoman::updateLegs(void) {
  float temp[3];
  float angle;

  walkphase = (int)sfmod(walkphase, PI / LEGSPEED);

  // Left leg
  angle = sfmod(walkphase * LEGSPEED, PI);
  if (angle > PI / 4)
    angle = PI / 2 - angle;
  if (angle < -PI / 4)
    angle = -PI / 2 - angle;
  vectorSet(temp, 0, -cos(angle), -sin(angle));
  vectorAdd(temp, lll->point1);
  vectorCopy(leftleglink->point1, temp);

  // Right leg
  angle = sfmod(walkphase * LEGSPEED + PI / 2, PI);
  if (angle > PI / 4)
    angle = PI / 2 - angle;
  if (angle < -PI / 4)
    angle = -PI / 2 - angle;
  vectorSet(temp, 0, -cos(angle), -sin(angle));
  vectorAdd(temp, rll->point1);
  vectorCopy(rightleglink->point1, temp);
}

void Legoman::walk(float amount) {
  walkdelay = 20;

  float sign;
  if (amount > 0)
    sign = 1;
  else
    sign = -1;

  walkphase += (int)sign;

  updateLegs();

  if (hitcounter && (jumpphase > 0)) {
    float axis[3];
    vectorScale(axis, &torso->rotation[0], -100.0 * amount);
    vectorAdd(torso->angularmomentum, axis);
    vectorSaturate(torso->angularmomentum, 0.0, 18.0);
  }

  if (!isStanding())
    return;

  float movement[3];
  float xdir[3], ydir[3], zdir[3];

  // vectorScale(ydir, &torso->rotation[3], 1);
  vectorSet(ydir, 0, 1, 0);
  vectorScale(zdir, &torso->rotation[6], -1);
  vectorCross(xdir, ydir, zdir);
  vectorNormalize(xdir);
  // vectorScale(xdir, &torso->rotation[0], 1);

  float oldmomentum[3];
  vectorCopy(oldmomentum, torso->momentum);

  float xmove[3], ymove[3], zmove[3];

  vectorProject(xmove, oldmomentum, xdir);
  vectorProject(ymove, oldmomentum, ydir);
  vectorProject(zmove, oldmomentum, zdir);

  vectorScale(xmove, 0.5);
  float wh = waist->position[1];
  if (wh < WAISTHEIGHT + 1.0 &&
      (!isOutOfRing() || leftleg->isInContact() || rightleg->isInContact())) {
    float hd = WAISTHEIGHT + 1.0 - wh;
    vectorScale(ymove, ydir, hd * 10);
  }
  float newz[3];
  vectorScale(newz, zdir, 6 * sign);
  float ztemp[3];
  vectorProject(ztemp, newz, ydir);
  vectorSub(newz, ztemp);
  vectorScale(newz, 0.8);
  vectorScale(zmove, 0.2);
  vectorAdd(zmove, newz);

  vectorCopy(movement, xmove);
  vectorAdd(movement, ymove);
  vectorAdd(movement, zmove);

  // if (!isOnGround() || isOutOfRing()) return;

  vectorCopy(torso->momentum, movement);
  vectorScale(movement, torso->invmass * waist->getMass());
  vectorCopy(waist->momentum, movement);

  // TK: pour conserver le moment éventuel d'un saut
  torso->momentum[1] = MAX(oldmomentum[1], torso->momentum[1]);

// Wythel pour faire des saltos
/*	if (jumpphase == 2 && hitcounter){
            float axis[3];
            vectorScale(axis, &torso->rotation[0], amount*-500);
            vectorAdd(torso->angularmomentum, axis);
    }*/

#if 0
	float speed = vectorDot(oldmomentum, movement);
	float speedadd = 1;
	float maxspeed = 5;
	/*speed += speedadd;
	if (speed > maxspeed) speed = maxspeed;
	if (speed + speedadd > maxspeed){
		speedadd = maxspeed - speed;
	}

	vectorScale(movement, speedadd);
	if (waist->position[1] < WAISTHEIGHT + 1.0){
		movement[1] = 3;
	}
	vectorAdd(torso->momentum, movement);*/

		/*float proj[3];
		vectorProject(proj, oldmomentum, movement);
		float len = vectorLength(proj);
		vectorAdd(movement, proj);
		vectorSaturate(movement, 0, 
		
		movement[1] = 300;
		//torso->addExternalForce(movement);
	}*/
	
	/*float linkpoint[3];
	vectorScale(linkpoint, &leftleg->rotation[3], -1);
	vectorAdd(linkpoint, leftleg->position);*/

		/*float movement[3];
	float temp[3];
	vectorScale(temp, &torso->rotation[3], amount*0.1);
	vectorScale(movement, &torso->rotation[6], amount);
	vectorAdd(movement, temp);

	if (walkphase == 0){
		walkphase = 40;
		vectorAdd(leftleg->momentum, movement);
	}
	if (walkphase == 20){
		walkphase = 19;
		vectorAdd(rightleg->momentum, movement);
	}*/

	/*float axis[3];
	vectorScale(axis, &leftleg->rotation[0], amount);

	if (walkphase == 0){
		//walkphase = 40;
		vectorAdd(leftleg->angularmomentum, axis);
		vectorAdd(rightleg->angularmomentum, axis);
	}*/
	/*if (walkphase == 0){
		walkphase = 1;
		vectorAdd(rightleg->momentum, movement);
	}*/
	/*float axis[3];
	float movement[3];

	if (walkphase == 0){
		unlockPart(LEFTLEG);

		vectorScale(axis, &leftleg->rotation[0], 5);
		vectorAdd(leftleg->angularmomentum, axis);
		
		float temp[3];
		vectorScale(temp, &torso->rotation[6], -10);
		vectorScale(movement, &torso->rotation[3], 5);
		vectorAdd(movement, temp);
		vectorAdd(torso->momentum, movement);
		vectorAdd(leftleg->momentum, movement);

		walkphase = 40;
	}*/

#endif
}

void Legoman::turn(float amount) {
  float axis[3];

  if (isStanding()) {
    vectorScale(axis, &torso->rotation[3], amount);
    vectorCopy(torso->angularmomentum, axis);
  } else {
    vectorScale(axis, &torso->rotation[3], amount * 0.3);
    vectorAdd(torso->angularmomentum, axis);
  }

  if (hitcounter && (jumpphase == 2)) {
    vectorScale(axis, &torso->rotation[6], amount * 2.0);
    vectorAdd(torso->angularmomentum, axis);
  }

  vectorSaturate(torso->angularmomentum, 0.0, 18.0);
}

void Legoman::hit(void) {
  if (!lefthand->attached && !righthand->attached)
    return;
  /*float leftdot = vectorDot(&lefthand->rotation[3], &torso->rotation[6]);
  float rightdot = vectorDot(&righthand->rotation[3], &torso->rotation[6]);
  if (leftdot < rightdot){
      hitside = LEFTHAND;
  } else{
      hitside = RIGHTHAND;
  }*/

  if (hitside >= 10)
    hitside -= 9;
  else
    hitside -= 2;

  if ((hitside & 1) && !lefthand->attached)
    hitside++;
  if (!(hitside & 1) && !righthand->attached)
    hitside++;

  float axis[3];
  if (hitside & 1) {
    // vectorScale(axis, &lefthand->rotation[0], 20.0);
    // du bras à l'horizontal
    vectorScale(axis, &lefthand->rotation[0],
                20.0 / (1 + 3.0 * fabs(lefthand->rotation[1])));
    vectorCopy(lefthand->angularmomentum, axis);
  } else {
    // vectorScale(axis, &righthand->rotation[0], 20.0);
    vectorScale(axis, &righthand->rotation[0],
                20.0 / (1 + 3.0 * fabs(righthand->rotation[1])));
    vectorCopy(righthand->angularmomentum, axis);
  }
}

void Legoman::jump(void) {
  if (!leftleg->attached && !rightleg->attached)
    return;
  if (jumpenabled &&
      (!isOutOfRing() || leftleg->isInContact() || rightleg->isInContact())) {
    float r = BLOCKHEIGHT * HEADHEIGHT / 2;
    float strength = (2 * LEGHEIGHT + 2 * WAISTHEIGHT + 2 * TORSOHEIGHT +
                      2 * HANDHEIGHT + 4.0 * PI * r * r * r) /
                     3.0 * getInvMass();
    float jumpvector[3] = {0, 100.0 / strength, 0};

    jumpvector[0] =
        3.0 * ((float)opponent->torso->position[0] - (float)torso->position[0]);
    jumpvector[2] =
        3.0 * ((float)opponent->torso->position[2] - (float)torso->position[2]);

    if (hitcounter) {
      jumpvector[0] *= 3.0;
      jumpvector[2] *= 3.0;
      if (!isOnGround()) {
        jumpvector[1] =
            ((float)opponent->torso->position[1] - (float)torso->position[1]);
      }
      //          leftleg->setGravity(false);
      //          rightleg->setGravity(false);
    }

    //#if 0
    if ((!isOnGround()) && ((torso->position[0] < -(float)ARENASIZE + 1.0) ||
                            (torso->position[0] > (float)ARENASIZE - 1.0) ||
                            (torso->position[2] < -(float)ARENASIZE + 1.0) ||
                            (torso->position[2] > (float)ARENASIZE - 1.0))) {
      // le blocko est à peu près sur le rebord, on autorise le jump du dernier
      // recours
      jumpvector[0] += -5.0 * (float)torso->position[0];
      jumpvector[2] += -5.0 * (float)torso->position[2];
    }
    //#endif

    vectorCopy(torso->momentum, jumpvector);
    // torso->momentum[1] = jumpvector[1];
    head->momentum[1] = 0; // jumpvector[1];
    waist->momentum[1] = 0; // jumpvector[1];
    leftleg->momentum[1] = 0; // jumpvector[1];
    rightleg->momentum[1] = 0; // jumpvector[1];
    lefthand->momentum[1] = 0; // jumpvector[1];
    righthand->momentum[1] = 0; // jumpvector[1];
    // vectorSet(head->momentum, 0, 0, 0);
    // jumpphase = 150;
    jumpsound->play();
    jumpenabled = false;
  }
  jumpphase = 2;
}

bool Legoman::isOnGround(void) {
  // if (!isStanding()) return false;
  float wh = waist->position[1];
  if (wh > WAISTHEIGHT + 1.5)
    return false;
  if (fabs(torso->momentum[1]) > 10)
    return false;
  // if (fabs(head->momentum[1]) > 10) return false;
  // if (fabs(waist->momentum[1]) > 3) return false;
  return not isOutOfRing();
}

bool Legoman::isOutOfRing(void) {
  return ((torso->position[0] < -(float)ARENASIZE - 0.5) ||
          (torso->position[0] > (float)ARENASIZE + 0.5) ||
          (torso->position[2] < -(float)ARENASIZE - 0.5) ||
          (torso->position[2] > (float)ARENASIZE + 0.5));
}

bool Legoman::isStanding(void) {
  if (!leftleg->attached && !rightleg->attached)
    return false;
  float headpos[3], torsopos[3];
  headsensor->getPosition(headpos);
  torsosensor->getPosition(torsopos);
  float posdiff[3];
  vectorSub(posdiff, headpos, torsopos);
  float posdifflen = vectorLength(posdiff);
  float angle = acos(posdiff[1] / posdifflen);

  if (angle < BALANCEANGLE)
    return true;
  else
    return false;
}

void Legoman::fallOff(void) {
  if (dead)
    return;
  if (rand() & 1)
    fallsound1->play();
  else
    fallsound2->play();
  die();
  head->energy = 0;
  torso->energy = 0;
  lefthand->energy = 0;
  righthand->energy = 0;
  waist->energy = 0;
  leftleg->energy = 0;
  rightleg->energy = 0;
}

void Legoman::releasePart(BodyPart *part) {
  if (dead)
    return;
  if (part == head) {
    headlinks[0]->enabled = false;
    headlinks[1]->enabled = false;
    headlinks[2]->enabled = false;
    head->attached = false;
    // float move[3];
    // vectorScale(move, &head->rotation[3], 1);
    // vectorAdd(head->position, move);
    die();
  } else if (part == lefthand) {
    lefthandlinks[0]->enabled = false;
    lefthandlinks[1]->enabled = false;
    lefthandlinks[2]->enabled = false;
    lefthand->attached = false;
  } else if (part == righthand) {
    righthandlinks[0]->enabled = false;
    righthandlinks[1]->enabled = false;
    righthandlinks[2]->enabled = false;
    righthand->attached = false;
  } else if (part == leftleg) {
    leftleglinks[0]->enabled = false;
    leftleglinks[1]->enabled = false;
    leftleglinks[2]->enabled = false;
    leftleg->attached = false;
  } else if (part == rightleg) {
    rightleglinks[0]->enabled = false;
    rightleglinks[1]->enabled = false;
    rightleglinks[2]->enabled = false;
    rightleg->attached = false;
  } else if (part == torso) {
    die();
  }
  if (!lefthand->attached && !righthand->attached && !leftleg->attached &&
      !rightleg->attached)
    die();
}

void Legoman::die(void) {
  if (dead)
    return;
  alive = false;
  lll->enabled = false;
  rll->enabled = false;
  gameOver(this);
}

bool Legoman::isAlive(void) { return alive; }

Legoman *Legoman::getOpponent(void) { return opponent; }

void Legoman::drawVisuals(void) {
  headvisual->draw();
  torsovisual->draw();
  lefthandvisual->draw();
  righthandvisual->draw();
  leftlegvisual->draw();
  rightlegvisual->draw();
}

DamageVisual::DamageVisual(BodyPart *object, Texture *texture, bool mirror,
                           float x1, float y1, float x2, float y2) {
  this->object = object;
  this->texture = texture;

  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;

  float d = 3.0 / 512;

  if (mirror) {
    this->tx1 = 1 - d;
    this->tx2 = 0 + d + 0.01;
  } else {
    this->tx1 = 0 + d + 0.01;
    this->tx2 = 1 - d;
  }
  this->ty1 = 0 + d;
  this->ty2 = 1 - d;
}

void DamageVisual::draw(void) {
  float energy = object->energy;
  texture->enable();

  glBegin(GL_QUADS);
  if (energy > 0)
    glColor3f(1 - energy, energy, 0);
  else
    glColor3f(0.3, 0.3, 0.3);

  glTexCoord2f(tx1, ty1);
  glVertex2f(x1, y1);

  glTexCoord2f(tx1, ty2);
  glVertex2f(x1, y2);

  glTexCoord2f(tx2, ty2);
  glVertex2f(x2, y2);

  glTexCoord2f(tx2, ty1);
  glVertex2f(x2, y1);
  glEnd();
}
