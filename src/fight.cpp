/*
 * $Id: fight.cpp,v 1.64 2002/07/22 11:40:26 msell Exp $
 *
 *
 * $Log: fight.cpp,v $
 * Revision 1.64  2002/07/22 11:40:26  msell
 * Loppukuvaan lattia
 *
 * Revision 1.63  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 * Revision 1.62  2002/07/21 22:50:39  msell
 * no message
 *
 * Revision 1.61  2002/07/21 20:14:28  msell
 * no message
 *
 * Revision 1.60  2002/07/21 15:03:12  msell
 * Äänet disabloitu
 *
 * Revision 1.59  2002/07/19 22:48:09  msell
 * Säätöä
 *
 * Revision 1.58  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.57  2002/07/19 14:05:51  msell
 * Damagetextuurit näkyy
 *
 * Revision 1.56  2002/07/19 12:48:31  jkaarlas
 * damagepää
 *
 * Revision 1.55  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.54  2002/07/17 22:45:53  msell
 * Ääniä vähän
 *
 * Revision 1.53  2002/07/17 19:06:39  jkaarlas
 * skyboxin keskitys
 *
 * Revision 1.52  2002/07/17 19:02:14  jkaarlas
 * skyboxin keskitys
 *
 * Revision 1.51  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.50  2002/07/16 19:54:38  jkaarlas
 * poistettu turhaa roinaa ja lisätty DATAPATH tiedostonimien eteen
 *
 * Revision 1.49  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 * Revision 1.48  2002/07/16 10:03:42  msell
 * Pikkufixi
 *
 * Revision 1.47  2002/07/16 00:42:43  msell
 * Uusia skyboxeja ja areenan säätöä
 *
 * Revision 1.46  2002/07/15 21:42:58  msell
 * Skybox-testi
 *
 * Revision 1.45  2002/07/15 20:32:35  msell
 * Uudet valot ja ulkoasun parantelua
 *
 * Revision 1.44  2002/07/15 15:22:07  msell
 * Parantelua
 *
 * Revision 1.43  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.42  2002/07/14 21:22:40  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.41  2002/07/10 22:22:53  msell
 * Cartoon-rendaus
 *
 * Revision 1.40  2002/07/10 22:07:23  jkaarlas
 * skaalatut ja käännellyt ruumiinosat
 *
 * Revision 1.39  2002/07/10 17:13:44  msell
 * Törmäystarkastelun parantelua
 *
 * Revision 1.38  2002/07/08 22:53:38  msell
 * Säätöä
 *
 * Revision 1.37  2002/07/08 18:28:47  msell
 * Törmäystä ja ukkoja
 *
 * Revision 1.36  2002/07/07 23:21:11  msell
 * Pientä parantelua
 *
 * Revision 1.35  2002/07/07 23:05:22  msell
 * Osien liimaaminen toisiinsa (kesken)
 *
 * Revision 1.34  2002/07/07 17:53:21  msell
 * Legoukon alku
 *
 * Revision 1.33  2002/07/07 15:29:07  msell
 * Törmäyksien parantelua
 *
 * Revision 1.32  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.31  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.30  2002/06/27 21:57:06  msell
 * glEnd(); lisätty tekstuuritestaukseen
 *
 * Revision 1.29  2002/06/27 21:46:55  jkaarlas
 * lisätty testikoodi transparentille tekstuurille (kommentoitu) vaihdettu tekstuuriquadin koordinaatit oikein päin
 *
 * Revision 1.28  2002/06/27 14:39:48  msell
 * Toimiva maila :)
 * Pyörivät kappaleet siis antaa liike-energiaa liikkuville kappaleille (ei toisin päin vielä)
 *
 * Revision 1.27  2002/06/27 00:08:04  msell
 * Kimmotukset palloille myös pyöritettyihin mesheihin
 *
 * Revision 1.26  2002/06/26 22:32:20  jkaarlas
 * mukana initissä asc-mallin lataus, tosin kommentoituna. samoin yksinkertainen quad, johon voi kokeilla tekstuurin lataamista
 *
 * Revision 1.25  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.24  2002/06/23 20:12:19  msell
 * Parempi törmäystarkistus palloista mesheihin
 *
 * Revision 1.23  2002/06/20 22:50:12  msell
 * Meshit
 *
 * Revision 1.22  2002/06/20 15:31:13  jkaarlas
 * turhat tekstuurilataukset pois
 *
 * Revision 1.21  2002/06/20 00:21:01  jkaarlas
 * materiaali- ja tekstuurihommia edistetty
 *
 * Revision 1.20  2002/06/17 20:49:04  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.19  2002/06/17 20:34:44  jkaarlas
 * kutsuu tekstuurilatausta
 *
 * Revision 1.18  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.17  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.16  2002/06/15 22:56:37  msell
 * Säätöä
 *
 * Revision 1.15  2002/06/15 17:18:37  msell
 * Toimiva törmäystarkastus kiinteille laatikoille
 *
 * Revision 1.14  2002/06/14 19:01:09  msell
 * Säätämistä ja testailua
 *
 * Revision 1.13  2002/06/14 00:26:17  msell
 * 100 kimpoilevaa palloa ja vähän vaimennusta
 *
 * Revision 1.12  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.11  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 * Revision 1.10  2002/06/07 21:16:51  msell
 * Fysiikkaenginen alkua
 *
 * Revision 1.9  2002/06/05 23:55:46  msell
 * Pallo
 *
 * Revision 1.8  2002/06/05 18:39:04  msell
 * Jotain pientä
 *
 * Revision 1.7  2002/06/05 15:00:41  msell
 * Palikoihin lisää detailia, facet jaetaan halutun kokosiin osiin
 *
 * Revision 1.6  2002/06/03 23:06:38  msell
 * no message
 *
 * Revision 1.5  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 * Revision 1.4  2002/05/19 13:40:19  msell
 * Säätöä
 *
 * Revision 1.3  2002/05/18 12:29:35  msell
 * Valot ja äänijärjestelmän parantelua
 *
 * Revision 1.2  2002/05/17 23:13:30  msell
 * Valot
 *
 * Revision 1.1  2002/05/16 18:42:07  msell
 * Vektorifunctioita ja kamera
 *
 *
 *
 * $Date: 2002/07/22 11:40:26 $
 *
 */

#include "main.h"

#include <math.h>

#include "legoblocks.h"
#include "camera.h"
#include "light.h"
#include "audio.h"
#include "object.h"
#include "appearance.h"
#include "sphere.h"
#include "vector.h" 
#include "collision.h"
#include "utils.h"
#include "graphics.h"
#include "objectfactory.h"
#include "world.h"
#include "3dutils.h"
#include "legoman.h"
#include "particle.h"
#include "font.h"
#include "fight.h"
#include "menu.h"
#include "end.h"
#include "run.h"

#include "glapi.h"

Camera camera;
Light light1, light2, light3, light4;
World *arenaworld;

Sound *fightmusic;
Sound *hitsound1, *hitsound2, *hitsound3, *hitsound4;
Sound *softhitsound1, *softhitsound2;
Sound *jumpsound;
Sound *fallsound1, *fallsound2;
Sound *fightsound;
Sound *victorysound;

Legoman *man1, *man2;
int points1, points2;

#define ARENASIZE 10
#define ARENAHEIGHT 10

bool fightinitialized = false;

void initFight(void){
	if (!fightinitialized){
		initCollisions();
		addCollisionLink(COLLISIONGROUP_ARENA, COLLISIONGROUP_PARTICLE);
		//addCollisionLink(COLLISIONGROUP_PARTICLE, COLLISIONGROUP_PARTICLE);

		addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_ARENA);
		//addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_PARTICLE);
		addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_MAN1);
		addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_ARENA);
		//addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_PARTICLE);

		addCollisionLink(COLLISIONGROUP_MAN2, COLLISIONGROUP_ARENA);
		//addCollisionLink(COLLISIONGROUP_MAN2, COLLISIONGROUP_PARTICLE);
		addCollisionLink(COLLISIONGROUP_MAN2, COLLISIONGROUP_MAN2);
		addCollisionLink(COLLISIONGROUP_MAN2HAND, COLLISIONGROUP_ARENA);
		//addCollisionLink(COLLISIONGROUP_MAN2HAND, COLLISIONGROUP_PARTICLE);

		addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_MAN2);
		addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_MAN2HAND);
		addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_MAN2);
		addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_MAN2HAND);

		//Sound* backgroundsong = new Sound("mixdown.mp3");
		Sound* backgroundsong = new Sound(BGSONG, true);
		camera.setPosition(-5, 8, 18);
		
		arenaworld = new World();


		//arenalight.setEnabled(true);
		/*arenalight.setPosition(0, 10, 0);
		Object *lamp = new Object();
		lamp->appearance = new LampAppearance();
		lamp->setPosition(0, 10, 0);
		arenaworld->addChild(lamp);*/

	}

	light1.setColor(1, 1, 1);
	light1.setSpecular(1, 1, 1);
	light1.setPosition(-ARENASIZE+0.5, 5, -ARENASIZE+0.5);
	light1.setAttenuation(0.2, 0.0, 0.02);

	light2.setColor(1, 1, 1);
	light2.setSpecular(1, 1, 1);
	light2.setPosition(ARENASIZE-0.5, 5, -ARENASIZE+0.5);
	light2.setAttenuation(0.2, 0.0, 0.02);
	
	light3.setColor(1, 1, 1);
	light3.setSpecular(1, 1, 1);
	light3.setPosition(-ARENASIZE+0.5, 5, ARENASIZE-0.5);
	light3.setAttenuation(0.2, 0.0, 0.02);

	light4.setColor(1, 1, 1);
	light4.setSpecular(1, 1, 1);
	light4.setPosition(ARENASIZE-0.5, 5, ARENASIZE-0.5);
	light4.setAttenuation(0.2, 0.0, 0.02);


	if (!fightinitialized){
		Object *lamp;

		lamp = new Object();
		lamp->appearance = new LampAppearance();
		lamp->setPosition(-ARENASIZE+0.5, (ARENAHEIGHT+0.5)*BLOCKHEIGHT, -ARENASIZE+0.5);
		arenaworld->addChild(lamp);

		lamp = new Object();
		lamp->appearance = new LampAppearance();
		lamp->setPosition(ARENASIZE-0.5, (ARENAHEIGHT+0.5)*BLOCKHEIGHT, -ARENASIZE+0.5);
		arenaworld->addChild(lamp);

		lamp = new Object();
		lamp->appearance = new LampAppearance();
		lamp->setPosition(-ARENASIZE+0.5, (ARENAHEIGHT+0.5)*BLOCKHEIGHT, ARENASIZE-0.5);
		arenaworld->addChild(lamp);

		lamp = new Object();
		lamp->appearance = new LampAppearance();
		lamp->setPosition(ARENASIZE-0.5, (ARENAHEIGHT+0.5)*BLOCKHEIGHT, ARENASIZE-0.5);
		arenaworld->addChild(lamp);


		//Floor
		BasicBlock *floorblock;
		floorblock = new BasicBlock(ARENASIZE*2, 3, ARENASIZE*2);
		floorblock->setPosition(0, -BLOCKHEIGHT*3/2.0, 0);
		floorblock->setColor(0, 1, 0);
		floorblock->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenaworld->addChild(floorblock);


		//Corners
		BasicBlock *arenacorner;

		arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
		arenacorner->setColor(1, 0, 0);
		//arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenacorner->setPosition(ARENASIZE-0.5, BLOCKHEIGHT*ARENAHEIGHT/2.0, ARENASIZE-0.5);
		arenaworld->addChild(arenacorner);

		arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
		arenacorner->setColor(1, 0, 0);
		//arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenacorner->setPosition(-ARENASIZE+0.5, BLOCKHEIGHT*ARENAHEIGHT/2.0, ARENASIZE-0.5);
		arenaworld->addChild(arenacorner);

		arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
		arenacorner->setColor(1, 0, 0);
		//arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenacorner->setPosition(ARENASIZE-0.5, BLOCKHEIGHT*ARENAHEIGHT/2.0, -ARENASIZE+0.5);
		arenaworld->addChild(arenacorner);

		arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
		arenacorner->setColor(1, 0, 0);
		//arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenacorner->setPosition(-ARENASIZE+0.5, BLOCKHEIGHT*ARENAHEIGHT/2.0, -ARENASIZE+0.5);
		arenaworld->addChild(arenacorner);


		//"Ropes"
		MeshObject *arenaline;
		Mesh *linegeometry;
		MultiAppearance *lineappearance;
		BasicBlockAppearance *line;
		int geometryheight = BLOCKHEIGHT*ARENAHEIGHT;

		linegeometry = createBox(-0.5, 0.5, -geometryheight/2, geometryheight/2-BLOCKHEIGHT, -ARENASIZE, ARENASIZE);
		arenaline = new MeshObject(linegeometry);
		lineappearance = new MultiAppearance();
		line = new BasicBlockAppearance(1, 1, ARENASIZE*2); 
		vectorSet(line->displacement, 0, -BLOCKHEIGHT*2.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(1, 1, ARENASIZE*2); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*0.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(1, 1, ARENASIZE*2); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*3.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		arenaline->appearance = lineappearance;
		arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenaline->setPosition(-ARENASIZE+0.5, geometryheight/2, 0);
		arenaworld->addChild(arenaline);

		linegeometry = createBox(-0.5, 0.5, -geometryheight/2, geometryheight/2-BLOCKHEIGHT, -ARENASIZE, ARENASIZE);
		arenaline = new MeshObject(linegeometry);
		lineappearance = new MultiAppearance();
		line = new BasicBlockAppearance(1, 1, ARENASIZE*2); 
		vectorSet(line->displacement, 0, -BLOCKHEIGHT*2.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(1, 1, ARENASIZE*2); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*0.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(1, 1, ARENASIZE*2); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*3.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		arenaline->appearance = lineappearance;
		arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenaline->setPosition(ARENASIZE-0.5, geometryheight/2, 0);
		arenaworld->addChild(arenaline);

		linegeometry = createBox(-ARENASIZE, ARENASIZE, -geometryheight/2, geometryheight/2-BLOCKHEIGHT, -0.5, 0.5);
		arenaline = new MeshObject(linegeometry);
		lineappearance = new MultiAppearance();
		line = new BasicBlockAppearance(ARENASIZE*2, 1, 1); 
		vectorSet(line->displacement, 0, -BLOCKHEIGHT*2.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(ARENASIZE*2, 1, 1); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*0.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(ARENASIZE*2, 1, 1); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*3.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		arenaline->appearance = lineappearance;
		arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenaline->setPosition(0, geometryheight/2, -ARENASIZE+0.5);
		arenaworld->addChild(arenaline);

		linegeometry = createBox(-ARENASIZE, ARENASIZE, -geometryheight/2, geometryheight/2-BLOCKHEIGHT, -0.5, 0.5);
		arenaline = new MeshObject(linegeometry);
		lineappearance = new MultiAppearance();
		line = new BasicBlockAppearance(ARENASIZE*2, 1, 1); 
		vectorSet(line->displacement, 0, -BLOCKHEIGHT*2.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(ARENASIZE*2, 1, 1); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*0.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		line = new BasicBlockAppearance(ARENASIZE*2, 1, 1); 
		vectorSet(line->displacement, 0, BLOCKHEIGHT*3.5, 0);
		line->material.setColor(1, 0, 0, 1);
		lineappearance->addAppearance(line),
		arenaline->appearance = lineappearance;
		arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
		arenaline->setPosition(0, geometryheight/2, ARENASIZE-0.5);
		arenaworld->addChild(arenaline);

		float movement[3];

		man1 = new Legoman(PLAYER1);
		man1->insertToWorld(arenaworld);
		vectorSet(movement, -4, 0, 0);
		man1->move(movement);
		man1->lockPart(LEFTLEG | RIGHTLEG);

		man2 = new Legoman(PLAYER2);
		man2->insertToWorld(arenaworld);
		vectorSet(movement, 4, 0, 0);
		man2->move(movement);
		man2->lockPart(LEFTLEG | RIGHTLEG);

		man1->addOpponent(man2);
		man2->addOpponent(man1);


		initBloods(arenaworld);


		hitsound1 = new Sound(DATAPATH"hit1.wav");
		softhitsound1 = new Sound(DATAPATH"hitsoft1.wav");
		softhitsound2 = new Sound(DATAPATH"hitsoft2.wav");
		jumpsound = new Sound(DATAPATH"jump.wav");
		fallsound1 = new Sound(DATAPATH"fall1.wav");
		fallsound2 = new Sound(DATAPATH"fall2.wav");
		fightsound = new Sound(DATAPATH"fight.wav");
		victorysound = new Sound(DATAPATH"victory.wav");

		fightmusic = new Sound(DATAPATH"fight.mp3", true);
	}

	float cameraTarget[3] = {0, 6, 0};
	camera.setTarget(cameraTarget);
	arenaworld->prepare();

	points1 = 0;
	points2 = 0;

	winner = man1;
}

#define MAXSCORE 3

int trophycounter = -1;

void resetFight(void){
	float movement[3];
	man1->heal();
	man2->heal();

	vectorSet(movement, -4, 0, 0);
	man1->move(movement);
	vectorSet(movement, 4, 0, 0);
	man2->move(movement);

	man1->lockPart(LEFTLEG | RIGHTLEG);
	man2->lockPart(LEFTLEG | RIGHTLEG);
}

int startcounter, endcounter;

float fightfade;

bool dead;

Legoman *winner;

void gameOver(Legoman *loser){
	endcounter = 0;
	dead = true;
	winner = loser->getOpponent();
}

void startFight(void){
	resetFight();
	fightmusic->setVolume(0);
	fightmusic->play();
	fightmusic->fadeIn(300);
	startcounter = 0;
	trophycounter = -1;
	fightfade = 1;
	dead = false;
	points1 = 0;
	points2 = 0;
}

SDLKey player1left = SDLK_LEFT;
SDLKey player1right = SDLK_RIGHT;
SDLKey player1forward = SDLK_UP;
SDLKey player1backward = SDLK_DOWN;
SDLKey player1jump = SDLK_RSHIFT;
SDLKey player1hit = SDLK_RCTRL;

SDLKey player2left = SDLK_a;
SDLKey player2right = SDLK_d;
SDLKey player2forward = SDLK_w;
SDLKey player2backward = SDLK_s;
SDLKey player2jump = SDLK_LSHIFT;
SDLKey player2hit = SDLK_LCTRL;


void stopGame(void){
	light1.setEnabled(false);
	light2.setEnabled(false);
	light3.setEnabled(false);
	light4.setEnabled(false);
	changeGameMode(MENUMODE);
	fightmusic->fadeOut(300);
	menuRestart();
}

void endGame(void){
	trophycounter = 0;
}

void endGame2(void){
	light1.setEnabled(false);
	light2.setEnabled(false);
	light3.setEnabled(false);
	light4.setEnabled(false);
	changeGameMode(ENDMODE);
	winner->heal();
	endRestart();
}

#define READY 250
#define FIGHT 500
#define VICTORY 300
#define VICTORYEND 700
#define ENDFADE 780
#define STARTOVER 800

#define TROPHYFADE 400

void calculateFight(int framecount){
	fightfade = -1;
	if (startcounter < 200){
		fightfade = (200-startcounter)/200.0;
	}
	if (startcounter == FIGHT - 30){
		fightsound->play();
	}
	startcounter++;

	if (endcounter == VICTORY){
		victorysound->play();
		if (winner == man1) points1++;
		if (winner == man2) points2++;
	}
	if (endcounter >= ENDFADE && endcounter <= STARTOVER){
		fightfade = (endcounter - ENDFADE)/(STARTOVER-ENDFADE);
	}
	if (endcounter == STARTOVER){
		if (points1 == MAXSCORE || points2 == MAXSCORE){
			endGame();
		} else{
			startcounter = 0;
			resetFight();
			dead = false;
			endcounter = 0;
		}
	}
	if (dead)	endcounter++;
	if (trophycounter != -1){
		fightfade = (float)trophycounter/TROPHYFADE;
		trophycounter++;
		if (trophycounter == TROPHYFADE) endGame2();
	}

	/*if (framecount % 10 == 0){
		float pos[3] = {0, 5, 0};
		float vel[3] = {randomf(2)-1, randomf(2)-1, randomf(2)-1};
		createBlood(pos, vel);
	}*/
	//arenalight.setPosition(sin(framecount*0.01)*6, 3, cos(framecount*0.01)*4);
	//light2.setPosition(sin(framecount*0.017)*6, 2, cos(framecount*0.027)*5);
	//light3.setPosition(sin(framecount*0.023)*3, 4, cos(framecount*0.013)*3);
	
	camera.setPosition(sin(framecount*0.0005)*20, sin(framecount*0.0013)*5+15, cos(framecount*0.0005)*20);
	
	//camera.setPosition(8, 5, 5);
	
	float upmovement[3] = {0, 0.001, 0};
	man1->move(upmovement);
	man2->move(upmovement);
	man1->update();
	man2->update();

	if (startcounter >= FIGHT){

		if (man1->isAlive()){
			if (keys[player1left]) man1->turn(5);
			if (keys[player1right]) man1->turn(-5);
			if (keys[player1forward]) man1->walk(0.03);
			if (keys[player1backward]) man1->walk(-0.03);
			if (keys[player1jump]) man1->jump();
			if (keys[player1hit]) man1->hit();
		}

		if (man2->isAlive()){
			if (keys[player2left]) man2->turn(5);
			if (keys[player2right]) man2->turn(-5);
			if (keys[player2forward]) man2->walk(0.03);
			if (keys[player2backward]) man2->walk(-0.03);
			if (keys[player2jump]) man2->jump();
			if (keys[player2hit]) man2->hit();
		}
	}


	if (keys[SDLK_ESCAPE]){
		stopGame();
	} 


	arenaworld->move();
}

void drawDamageMeters(void){
	enable2D();

	glEnable(GL_BLEND);

	glPushMatrix();
	glTranslatef(0.925, 0.22-0.025, 0);
	glScalef(0.08*3/4, 0.08, 0.1);
	man1->drawVisuals();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.075, 0.22-0.025, 0);
	glScalef(0.08*3/4, 0.08, 0.1);
	man2->drawVisuals();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


	glColor3f(1, 1, 0);

	char pointstring[5];
	sprintf(pointstring, "%i", points1);
	print(0.75, 0.05, pointstring, 0.15);

	sprintf(pointstring, "%i", points2);
	print(0.15, 0.05, pointstring, 0.15);

	disable2D();
}

void drawFight(int framecount){
	glLoadIdentity();
	camera.glUpdate();
	//float position[3];
	//camera.getPosition((float*)position);
	//createSkyBox(position[0], position[1], position[2], 50, 20, 50);
	
	createSkyBox(0, 10, 0, 50, 20, 50);
	

	light1.setEnabled(true);
	light2.setEnabled(true);
	light3.setEnabled(true);
	light4.setEnabled(true);

	updateLights();
  
	arenaworld->draw();
	
	drawDamageMeters();


	flaretexture->enable();
	light1.createFlare();
	light2.createFlare();
	light3.createFlare();
	light4.createFlare();
	flaretexture->disable();
	

	enable2D();

	if (fightfade != -1){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0, 0, 0, fightfade);
		glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(1, 0);
			glVertex2f(1, 1);
			glVertex2f(0, 1);
		glEnd();
	}

	if (startcounter >= READY && startcounter < FIGHT){
		float size = 0.2 - (startcounter - READY)*0.0001;
		float alpha = 1 - (float)(startcounter - READY)/(FIGHT - READY);
		float x = 0.5 - size*1.5;
		float y = 0.5 - size*0.5;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(alpha, 0, 0, alpha);
		print(x, y, "Ready", size);
	}
	if (startcounter >= FIGHT && startcounter < FIGHT+200){
		float size = 0.2 + (startcounter - FIGHT)*0.0005;
		float alpha = 1 - (float)(startcounter - FIGHT)/200;
		float x = 0.5 - size*1.4;
		float y = 0.5 - size*0.5;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0, alpha, 0, alpha);
		print(x, y, "Fight!", size);
	}

	if (dead){
		if (endcounter >= VICTORY && endcounter < VICTORYEND){
			float size = 0.18 + (endcounter - VICTORY)*0.0001;
			float alpha = (float)(endcounter - VICTORY)/(VICTORYEND-VICTORY);
			alpha = 1-4*(alpha-0.5)*(alpha-0.5);
			alpha = pow(alpha, 0.5);
			float x = 0.5 - size*1.9;
			float y = 0.3 - size*0.5;

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0, 0, alpha, alpha);
			print(x, y, "Victory!", size);
		}
	}

	disable2D();

	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}
