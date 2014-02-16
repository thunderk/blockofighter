/*
 * $Id: legoman.h,v 1.21 2002/07/22 12:07:36 msell Exp $
 *
 *
 * $Log: legoman.h,v $
 * Revision 1.21  2002/07/22 12:07:36  msell
 * Pää kiinni
 *
 * Revision 1.20  2002/07/22 06:08:18  msell
 * Filenimet pienellä
 *
 * Revision 1.19  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 * Revision 1.18  2002/07/21 22:50:39  msell
 * no message
 *
 * Revision 1.17  2002/07/21 20:14:28  msell
 * no message
 *
 * Revision 1.16  2002/07/21 15:16:41  msell
 * no message
 *
 * Revision 1.15  2002/07/21 15:03:12  msell
 * Äänet disabloitu
 *
 * Revision 1.14  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.13  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.12  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.11  2002/07/17 22:45:54  msell
 * Ääniä vähän
 *
 * Revision 1.10  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.9  2002/07/16 07:27:32  jkaarlas
 * nyt latautuu kämmen. paikka ja väri pitää vielä säätää
 *
 * Revision 1.8  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.7  2002/07/14 21:22:39  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.6  2002/07/11 18:33:58  jkaarlas
 * mallit paikoillaan, vaatii säätöä
 *
 * Revision 1.5  2002/07/10 17:13:44  msell
 * Törmäystarkastelun parantelua
 *
 * Revision 1.4  2002/07/08 22:53:38  msell
 * Säätöä
 *
 * Revision 1.3  2002/07/08 18:28:47  msell
 * Törmäystä ja ukkoja
 *
 * Revision 1.2  2002/07/07 23:05:22  msell
 * Osien liimaaminen toisiinsa (kesken)
 *
 * Revision 1.1  2002/07/07 17:53:21  msell
 * Legoukon alku
 *
 *
 *
 * $Date: 2002/07/22 12:07:36 $
 *
 */

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


const char LEFTLEGASC[] = DATAPATH"blockolegscaled.asc";
const char RIGHTLEGASC[] = DATAPATH"blockolegscaled.asc";
const char WAISTASC[] = DATAPATH"blockowaistscaled.asc";
const char TORSOASC[] = DATAPATH"blockotorsoscaled.asc";
const char LEFTARMASC[] = DATAPATH"leftarm.asc";
const char RIGHTARMASC[] = DATAPATH"rightarm.asc";
const char LEFTPALMASC[] = DATAPATH"leftpalm.asc";
const char RIGHTPALMASC[] = DATAPATH"rightpalm.asc";


#define MODELSCALE 0.12
#define TORSOSCALE 0.115


class BodyPart : public Object{
private:
	float energy;
	float strength;
	Legoman *parent;

	bool attached;

	int immortal;

public:
	BodyPart(Legoman *parent, float strength);

	void move(void);

	void hitForce(float speed, float *speed2, Object *source);

	void makeDamage(float amount);

	void reset(void);

	friend class DamageVisual;
	friend class Legoman;
};

class Sensor{
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

class Legoman{
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
	int hitcounter;

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

	void insertToWorld(World *world);
	void heal(void);

	void addHarmfulObject(Object *object);
	bool isHarmfulObject(Object *object);

	void addOpponent(Legoman *opponent);

	//Call once per frame
	void update(void);

	//Lock both legs at the same time by calling
	//lockLeg(LEFTLEG | RIGHTLEG);
	void lockPart(int part);
	void unlockPart(int part);

	//Relative movement
	void move(float *movement);

	void turn(float amount);
	void walk(float amount);

	void jump(void);
	void hit(void);

	bool isAlive(void);
	Legoman *getOpponent(void);

	void drawVisuals();

	friend class BodyPart;
	friend void drawEnd(int framecount);
};



extern Texture *damageHead;
extern Texture *damageTorso;
extern Texture *damageHand;
extern Texture *damageLeg;


class DamageVisual{
private:
	BodyPart *object;
	float x1, y1, x2, y2;
	float tx1, ty1, tx2, ty2;
	Texture *texture;

public:
	DamageVisual(BodyPart *object, Texture *texture, bool mirror,
		float x1, float y1, float x2, float y2);

	void draw(void);
};

#endif

