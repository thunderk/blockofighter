#ifndef __LEGOMAN_H_INCLUDED__
#define __LEGOMAN_H_INCLUDED__

class BodyPart;
class Sensor;
class Legoman;
class DamageVisual;

#include "object.h"
#include "world.h"

#define LEGHEIGHT 4
#define WAISTHEIGHT 1
#define TORSOHEIGHT 4
#define HANDHEIGHT 6
#define HEADHEIGHT 3

#define PLAYER1 1
#define PLAYER2 2

#define LEFTLEG 1
#define RIGHTLEG 2
#define LEFTHAND 4
#define RIGHTHAND 8

const char LEFTLEGASC[] = DATAPATH "blockolegscaled.asc";
const char RIGHTLEGASC[] = DATAPATH "blockolegscaled.asc";
const char WAISTASC[] = DATAPATH "blockowaistscaled.asc";
const char TORSOASC[] = DATAPATH "blockotorsoscaled.asc";
const char LEFTARMASC[] = DATAPATH "leftarm.asc";
const char RIGHTARMASC[] = DATAPATH "rightarm.asc";
const char LEFTPALMASC[] = DATAPATH "leftpalm.asc";
const char RIGHTPALMASC[] = DATAPATH "rightpalm.asc";

#define MODELSCALE 0.12
#define TORSOSCALE 0.115

class BodyPart : public Object {
private:
  float energy;
  float strength;
  Legoman *parent;

  bool attached;

  int immortal;

  bool isInContact();

public:
  BodyPart(Legoman *parent, float strength);

  inline bool isAttached() { return attached; }

  void move(void);

  void hitForce(float speed, float *speed2, Object *source);

  void makeDamage(float amount);

  void reset(void);

  friend class DamageVisual;
  friend class Legoman;
};

class Sensor {
private:
  float relativeposition[3];
  Object *object;

  float position[3], oldposition[3];
  float velocity[3], oldvelocity[3];
  float acceleration[3];

public:
  Sensor();

  void attach(Object *object, float *relativeposition);
  void attach(Object *object);
  void update(void);

  void getPosition(float *target);
  void getVelocity(float *target);
  void getAcceleration(float *target);
};

class Legoman {
private:
  int side;

  bool alive;

  BodyPart *head;
  BodyPart *torso;
  BodyPart *waist;
  BodyPart *lefthand, *righthand;
  BodyPart *leftleg, *rightleg;

  DamageVisual *headvisual;
  DamageVisual *torsovisual;
  DamageVisual *lefthandvisual, *righthandvisual;
  DamageVisual *leftlegvisual, *rightlegvisual;

  ObjectLink *leftleglink, *rightleglink;
  ObjectLink *lefthandlink, *righthandlink;
  ObjectLink *lll, *rll;

  ObjectLink *leftleglinks[3], *rightleglinks[3];
  ObjectLink *lefthandlinks[3], *righthandlinks[3];
  ObjectLink *headlinks[3];

  objectlist *harmfulobjects;

  Legoman *opponent;

  Sensor *headsensor, *torsosensor;

  int walkphase, walkdelay;
  int jumpphase;
  int hitside;

  bool jumpenabled;

  World *world;

  void balance(void);
  void updateLegs(void);
  bool isStanding(void);
  bool isOnGround(void);
  float getInvMass(void);

  void fallOff(void);
  void releasePart(BodyPart *part);
  void die(void);

public:
  Legoman(int side);

  inline Object *getMainObject() { return (Object *)torso; }
  inline Object *getHead() { return (Object *)head; }
  inline bool isBeheaded() { return not(Object *)head->isAttached(); }

  bool isOutOfRing(void); // TK

  void insertToWorld(World *world);
  void heal(void);

  void addHarmfulObject(Object *object);
  bool isHarmfulObject(Object *object);

  void addOpponent(Legoman *opponent);

  // Call once per frame
  void update(void);

  // Lock both legs at the same time by calling
  // lockLeg(LEFTLEG | RIGHTLEG);
  void lockPart(int part);
  void unlockPart(int part);

  // Relative movement
  void move(float *movement);

  void turn(float amount);
  void walk(float amount);

  void jump(void);
  void hit(void);

  bool isAlive(void);
  Legoman *getOpponent(void);
  int hitcounter;

  void drawVisuals();

  friend class BodyPart;
  friend void drawEnd(int framecount);
};

extern Texture *damageHead;
extern Texture *damageTorso;
extern Texture *damageHand;
extern Texture *damageLeg;

class DamageVisual {
private:
  BodyPart *object;
  float x1, y1, x2, y2;
  float tx1, ty1, tx2, ty2;
  Texture *texture;

public:
  DamageVisual(BodyPart *object, Texture *texture, bool mirror, float x1,
               float y1, float x2, float y2);

  void draw(void);
};

#endif
