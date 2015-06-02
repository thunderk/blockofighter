#include "main.h"

#include <stdlib.h>
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
Legoman *manout = NULL;
Legoman *beheaded = NULL;
int points1, points2;

int startcounter, endcounter, rockcounter = 0;

float fightfade;

bool dead;

Legoman *winner;

bool fightinitialized = false;

void resetFight(void); // prototype

void initFight(void) {
  if (!fightinitialized) {
    initCollisions();
    addCollisionLink(COLLISIONGROUP_ARENA, COLLISIONGROUP_PARTICLE);
    // addCollisionLink(COLLISIONGROUP_PARTICLE, COLLISIONGROUP_PARTICLE);

    addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_ARENA);
    // addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_PARTICLE);
    addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_MAN1);
    addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_ARENA);
    // addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_PARTICLE);

    addCollisionLink(COLLISIONGROUP_MAN2, COLLISIONGROUP_ARENA);
    // addCollisionLink(COLLISIONGROUP_MAN2, COLLISIONGROUP_PARTICLE);
    addCollisionLink(COLLISIONGROUP_MAN2, COLLISIONGROUP_MAN2);
    addCollisionLink(COLLISIONGROUP_MAN2HAND, COLLISIONGROUP_ARENA);
    // addCollisionLink(COLLISIONGROUP_MAN2HAND, COLLISIONGROUP_PARTICLE);

    addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_MAN2);
    addCollisionLink(COLLISIONGROUP_MAN1, COLLISIONGROUP_MAN2HAND);
    addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_MAN2);
    addCollisionLink(COLLISIONGROUP_MAN1HAND, COLLISIONGROUP_MAN2HAND);

    // Sound* backgroundsong = new Sound("mixdown.mp3");
    // UNUSED//Sound* backgroundsong = new Sound(BGSONG, true);
    // camera.setPosition(-5, 8, 18);

    arenaworld = new World();

    // arenalight.setEnabled(true);
    /*arenalight.setPosition(0, 10, 0);
    Object *lamp = new Object();
    lamp->appearance = new LampAppearance();
    lamp->setPosition(0, 10, 0);
    arenaworld->addChild(lamp);*/
  }

  light1.setColor(1, 1, 1);
  light1.setSpecular(1, 1, 1);
  light1.setPosition(-ARENASIZE + 0.5, 5, -ARENASIZE + 0.5);
  light1.setAttenuation(0.2, 0.0, 0.02);

  light2.setColor(1, 1, 1);
  light2.setSpecular(1, 1, 1);
  light2.setPosition(ARENASIZE - 0.5, 5, -ARENASIZE + 0.5);
  light2.setAttenuation(0.2, 0.0, 0.02);

  light3.setColor(1, 1, 1);
  light3.setSpecular(1, 1, 1);
  light3.setPosition(-ARENASIZE + 0.5, 5, ARENASIZE - 0.5);
  light3.setAttenuation(0.2, 0.0, 0.02);

  light4.setColor(1, 1, 1);
  light4.setSpecular(1, 1, 1);
  light4.setPosition(ARENASIZE - 0.5, 5, ARENASIZE - 0.5);
  light4.setAttenuation(0.2, 0.0, 0.02);

  if (!fightinitialized) {
    Object *lamp;

    lamp = new Object();
    lamp->appearance = new LampAppearance();
    lamp->setPosition(-ARENASIZE + 0.5, (ARENAHEIGHT + 0.5) * BLOCKHEIGHT,
                      -ARENASIZE + 0.5);
    arenaworld->addChild(lamp);

    lamp = new Object();
    lamp->appearance = new LampAppearance();
    lamp->setPosition(ARENASIZE - 0.5, (ARENAHEIGHT + 0.5) * BLOCKHEIGHT,
                      -ARENASIZE + 0.5);
    arenaworld->addChild(lamp);

    lamp = new Object();
    lamp->appearance = new LampAppearance();
    lamp->setPosition(-ARENASIZE + 0.5, (ARENAHEIGHT + 0.5) * BLOCKHEIGHT,
                      ARENASIZE - 0.5);
    arenaworld->addChild(lamp);

    lamp = new Object();
    lamp->appearance = new LampAppearance();
    lamp->setPosition(ARENASIZE - 0.5, (ARENAHEIGHT + 0.5) * BLOCKHEIGHT,
                      ARENASIZE - 0.5);
    arenaworld->addChild(lamp);

    // Floor
    BasicBlock *floorblock;
    floorblock = new BasicBlock(ARENASIZE * 2, 3, ARENASIZE * 2);
    floorblock->setPosition(0, -BLOCKHEIGHT * 3 / 2.0, 0);
    floorblock->setColor(0, 1, 0);
    floorblock->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenaworld->addChild(floorblock);

    // Corners
    BasicBlock *arenacorner;

    arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
    arenacorner->setColor(1, 0, 0);
    // arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenacorner->setPosition(ARENASIZE - 0.5, BLOCKHEIGHT * ARENAHEIGHT / 2.0,
                             ARENASIZE - 0.5);
    arenaworld->addChild(arenacorner);

    arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
    arenacorner->setColor(1, 0, 0);
    // arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenacorner->setPosition(-ARENASIZE + 0.5, BLOCKHEIGHT * ARENAHEIGHT / 2.0,
                             ARENASIZE - 0.5);
    arenaworld->addChild(arenacorner);

    arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
    arenacorner->setColor(1, 0, 0);
    // arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenacorner->setPosition(ARENASIZE - 0.5, BLOCKHEIGHT * ARENAHEIGHT / 2.0,
                             -ARENASIZE + 0.5);
    arenaworld->addChild(arenacorner);

    arenacorner = new BasicBlock(1, ARENAHEIGHT, 1);
    arenacorner->setColor(1, 0, 0);
    // arenacorner->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenacorner->setPosition(-ARENASIZE + 0.5, BLOCKHEIGHT * ARENAHEIGHT / 2.0,
                             -ARENASIZE + 0.5);
    arenaworld->addChild(arenacorner);

    //"Ropes"
    MeshObject *arenaline;
    Mesh *linegeometry;
    MultiAppearance *lineappearance;
    BasicBlockAppearance *line;
    int geometryheight = (int)(BLOCKHEIGHT * ARENAHEIGHT);

    linegeometry =
        createBox(-0.5, 0.5, -geometryheight / 2,
                  geometryheight / 2 - BLOCKHEIGHT, -ARENASIZE, ARENASIZE);
    arenaline = new MeshObject(linegeometry);
    lineappearance = new MultiAppearance();
    line = new BasicBlockAppearance(1, 1, ARENASIZE * 2);
    vectorSet(line->displacement, 0, -BLOCKHEIGHT * 2.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(1, 1, ARENASIZE * 2);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 0.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(1, 1, ARENASIZE * 2);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 3.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line), arenaline->appearance = lineappearance;
    arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenaline->setPosition(-ARENASIZE + 0.5, geometryheight / 2, 0);
    arenaworld->addChild(arenaline);

    linegeometry =
        createBox(-0.5, 0.5, -geometryheight / 2,
                  geometryheight / 2 - BLOCKHEIGHT, -ARENASIZE, ARENASIZE);
    arenaline = new MeshObject(linegeometry);
    lineappearance = new MultiAppearance();
    line = new BasicBlockAppearance(1, 1, ARENASIZE * 2);
    vectorSet(line->displacement, 0, -BLOCKHEIGHT * 2.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(1, 1, ARENASIZE * 2);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 0.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(1, 1, ARENASIZE * 2);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 3.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line), arenaline->appearance = lineappearance;
    arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenaline->setPosition(ARENASIZE - 0.5, geometryheight / 2, 0);
    arenaworld->addChild(arenaline);

    linegeometry = createBox(-ARENASIZE, ARENASIZE, -geometryheight / 2,
                             geometryheight / 2 - BLOCKHEIGHT, -0.5, 0.5);
    arenaline = new MeshObject(linegeometry);
    lineappearance = new MultiAppearance();
    line = new BasicBlockAppearance(ARENASIZE * 2, 1, 1);
    vectorSet(line->displacement, 0, -BLOCKHEIGHT * 2.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(ARENASIZE * 2, 1, 1);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 0.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(ARENASIZE * 2, 1, 1);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 3.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line), arenaline->appearance = lineappearance;
    arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenaline->setPosition(0, geometryheight / 2, -ARENASIZE + 0.5);
    arenaworld->addChild(arenaline);

    linegeometry = createBox(-ARENASIZE, ARENASIZE, -geometryheight / 2,
                             geometryheight / 2 - BLOCKHEIGHT, -0.5, 0.5);
    arenaline = new MeshObject(linegeometry);
    lineappearance = new MultiAppearance();
    line = new BasicBlockAppearance(ARENASIZE * 2, 1, 1);
    vectorSet(line->displacement, 0, -BLOCKHEIGHT * 2.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(ARENASIZE * 2, 1, 1);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 0.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line),
        line = new BasicBlockAppearance(ARENASIZE * 2, 1, 1);
    vectorSet(line->displacement, 0, BLOCKHEIGHT * 3.5, 0);
    line->material.setColor(1, 0, 0, 1);
    lineappearance->addAppearance(line), arenaline->appearance = lineappearance;
    arenaline->setCollisionGroup(COLLISIONGROUP_ARENA);
    arenaline->setPosition(0, geometryheight / 2, ARENASIZE - 0.5);
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

    hitsound1 = new Sound(DATAPATH "hit1.wav");
    softhitsound1 = new Sound(DATAPATH "hitsoft1.wav");
    softhitsound2 = new Sound(DATAPATH "hitsoft2.wav");
    jumpsound = new Sound(DATAPATH "jump.wav");
    fallsound1 = new Sound(DATAPATH "fall1.wav");
    fallsound2 = new Sound(DATAPATH "fall2.wav");
    fightsound = new Sound(DATAPATH "fight.wav");
    victorysound = new Sound(DATAPATH "victory.wav");

    fightmusic = new Sound(DATAPATH "fight.ogg", true);
  }

  // float cameraTarget[3] = {0, 6, 0};
  // camera.setTarget(cameraTarget);
  // camera.setStart();
  arenaworld->prepare();

  resetFight();

  points1 = 0;
  points2 = 0;

}

#define MAXSCORE 3

int trophycounter = -1;

void resetFight(void) {
  arenaworld->setGravity(9.81);
  float movement[3];
  man1->heal();
  man2->heal();

  vectorSet(movement, -4, 0, 0);
  man1->move(movement);
  vectorSet(movement, 4, 0, 0);
  man2->move(movement);

  man1->lockPart(LEFTLEG | RIGHTLEG);
  man2->lockPart(LEFTLEG | RIGHTLEG);

  man1->getMainObject()->setGravity(true);
  man1->getHead()->setGravity(true);
  man2->getMainObject()->setGravity(true);
  man2->getHead()->setGravity(true);

  manout = NULL;
  beheaded = NULL;

  rockcounter = 0;

  camera.setStart();
  removeAllBlood();
}

void gameOver(Legoman *loser) {
  endcounter = 0;
  dead = true;
  winner = loser->getOpponent();
}

void startFight(void) {
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

SDLKey player2left = SDLK_f;
SDLKey player2right = SDLK_h;
SDLKey player2forward = SDLK_t;
SDLKey player2backward = SDLK_g;
SDLKey player2jump = SDLK_s;
SDLKey player2hit = SDLK_x;

void stopGame(void) {
  light1.setEnabled(false);
  light2.setEnabled(false);
  light3.setEnabled(false);
  light4.setEnabled(false);
  changeGameMode(MENUMODE);
  fightmusic->fadeOut(300);
  menuRestart();
}

void endGame(void) { trophycounter = 0; }

void endGame2(void) {
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

void calculateFight(int framecount) {
  fightfade = -1;
  if (startcounter < 200) {
    fightfade = (200 - startcounter) / 200.0;
  }
  if (startcounter == FIGHT - 30) {
    fightsound->play();
  }
  startcounter++;

  if (endcounter == VICTORY) {
    victorysound->play();
    setSpeedFactor(1.0); // TK
    if (winner == man1)
      points1++;
    if (winner == man2)
      points2++;
  }
  if (endcounter >= ENDFADE && endcounter <= STARTOVER) {
    fightfade = (endcounter - ENDFADE) / (STARTOVER - ENDFADE);
  }
  if (endcounter == STARTOVER) {
    if (points1 == MAXSCORE || points2 == MAXSCORE) {
      endGame();
    } else {
      startcounter = 0;
      resetFight();
      dead = false;
      endcounter = 0;
    }
  } else if (endcounter == 1) // ralenti au début de la mort
  {
    // Wythel
    // arenaworld->setGravity(2.0);
    if (man1->isBeheaded() &&
        man1->getHead()->position[1] > ARENAHEIGHT / 2.0 - 2.0) {
      man1->getMainObject()->setGravity(false);
      man1->getHead()->setGravity(false);
      beheaded = man1;
      setSpeedFactor(0.0);
    } else if (man2->isBeheaded() &&
               man2->getHead()->position[1] > ARENAHEIGHT / 2.0 - 2.0) {
      man2->getMainObject()->setGravity(false);
      man2->getHead()->setGravity(false);
      beheaded = man2;
      setSpeedFactor(0.0);
    } else {
      setSpeedFactor(0.3);
    }
  } else if (endcounter == VICTORY / 4) {
    setSpeedFactor(0.5);
  } else if (endcounter == VICTORY / 2) {
    setSpeedFactor(0.5); // au cas ou ca ait été modifié
    man1->getMainObject()->setGravity(true);
    man1->getHead()->setGravity(true);
    man2->getMainObject()->setGravity(true);
    man2->getHead()->setGravity(true);
  }

  if (dead) {
    endcounter++;
  }

  if (trophycounter != -1) {
    fightfade = (float)trophycounter / TROPHYFADE;
    trophycounter++;
    if (trophycounter == TROPHYFADE)
      endGame2();
  }

  /*if (framecount % 10 == 0){
      float pos[3] = {0, 5, 0};
      float vel[3] = {randomf(2)-1, randomf(2)-1, randomf(2)-1};
      createBlood(pos, vel);
  }*/
  // light2.setPosition(sin(framecount*0.017)*6, 2, cos(framecount*0.027)*5);
  // light3.setPosition(sin(framecount*0.023)*3, 4, cos(framecount*0.013)*3);


  // camera.setPosition(8, 5, 5);

  float upmovement[3] = {0, 0.001, 0};
  man1->move(upmovement);
  man2->move(upmovement);
  man1->update();
  man2->update();

  if (startcounter >= FIGHT) {

    if (man1->isAlive()) {
      if (keys[player1left])
        man1->turn(5);
      if (keys[player1right])
        man1->turn(-5);
      if (keys[player1forward])
        man1->walk(0.03);
      if (keys[player1backward])
        man1->walk(-0.03);
      if (keys[player1jump])
        man1->jump();
      if (keys[player1hit]) {
        man1->hit();
        man1->hitcounter = 1;
      } else {
        man1->hitcounter = 0;
      }
    }

    if (man2->isAlive()) {
      if (keys[player2left])
        man2->turn(5);
      if (keys[player2right])
        man2->turn(-5);
      if (keys[player2forward])
        man2->walk(0.03);
      if (keys[player2backward])
        man2->walk(-0.03);
      if (keys[player2jump])
        man2->jump();
      if (keys[player2hit]) {
        man2->hit();
        man2->hitcounter = 1;
      } else {
        man2->hitcounter = 0;
      }
    }
  }

  if (keys[SDLK_ESCAPE]) {
    setSpeedFactor(1.0);
    stopGame();
  }

  arenaworld->move();
}

void drawDamageMeters(void) {
  enable2D();

  glEnable(GL_BLEND);

  glPushMatrix();
  glTranslatef(0.925, 0.22 - 0.025, 0);
  glScalef(0.08 * 3 / 4, 0.08, 0.1);
  man1->drawVisuals();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.075, 0.22 - 0.025, 0);
  glScalef(0.08 * 3 / 4, 0.08, 0.1);
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

void drawFight(int framecount) {
  glLoadIdentity();
  camera.glUpdate();
  // float position[3];
  // camera.getPosition((float*)position);
  // createSkyBox(position[0], position[1], position[2], 50, 20, 50);

  createSkyBox(0, 10, 0, 50, 20, 50);

  light1.setEnabled(true);
  light2.setEnabled(true);
  light3.setEnabled(true);
  light4.setEnabled(true);

  updateLights();

  arenaworld->draw();

  drawDamageMeters();

  flaretexture->enable();
  light1.createFlare(&camera);
  light2.createFlare(&camera);
  light3.createFlare(&camera);
  light4.createFlare(&camera);
  flaretexture->disable();

  enable2D();

  if (fightfade != -1) {
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

  if (startcounter >= READY && startcounter < FIGHT) {
    float size = 0.2 - (startcounter - READY) * 0.0001;
    float alpha = 1 - (float)(startcounter - READY) / (FIGHT - READY);
    float x = 0.5 - size * 1.5;
    float y = 0.5 - size * 0.5;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(alpha, 0, 0, alpha);
    print(x, y, "Ready", size);
  }
  if (startcounter >= FIGHT && startcounter < FIGHT + 200) {
    float size = 0.2 + (startcounter - FIGHT) * 0.0005;
    float alpha = 1 - (float)(startcounter - FIGHT) / 200;
    float x = 0.5 - size * 1.4;
    float y = 0.5 - size * 0.5;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, alpha, 0, alpha);
    print(x, y, "Fight!", size);
  }

  if (dead) {
    if (endcounter >= VICTORY && endcounter < VICTORYEND) {
      float size = 0.18 + (endcounter - VICTORY) * 0.0001;
      float alpha = (float)(endcounter - VICTORY) / (VICTORYEND - VICTORY);
      alpha = 1 - 4 * (alpha - 0.5) * (alpha - 0.5);
      alpha = pow(alpha, 0.5);
      float x = 0.5 - size * 1.9;
      float y = 0.3 - size * 0.5;

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0, 0, alpha, alpha);
      print(x, y, "Victory!", size);
    }

    if (beheaded != NULL) {
      /*            camera.setAutoBeheaded(((Legoman *)beheaded)->getHead(),
         (float)M_PI * (float)(rockcounter++ % 80) / 40.0);
                  if (rockcounter == 80)
                  {
                      beheaded = NULL;
                      setSpeedFactor(0.25);
                  }*/
      if (rockcounter < 80) {
        camera.setAutoBeheaded(((Legoman *)beheaded)->getHead(),
                               (float)M_PI * (float)(rockcounter++ % 80) /
                                   40.0);
      } else if (rockcounter == 80) {
        setSpeedFactor(0.25);
        rockcounter++;
      } else {
        // camera.setAutoNormal(((Legoman *)beheaded)->getHead(), ((Legoman
        // *)beheaded)->getOpponent()->getMainObject(), true);
        camera.setAutoFallHead(((Legoman *)beheaded)->getHead(),
                               ((Legoman *)beheaded)->getMainObject());
      }
    } else if (manout != NULL) {
      camera.setAutoCastOut(manout->getMainObject());
    } else if (man1->isOutOfRing()) {
      manout = man1;
    } else if (man2->isOutOfRing()) {
      manout = man2;
    } else {
      camera.setAutoNormal(man1->getMainObject(), man2->getMainObject(), true);
    }
  } else {
    camera.setAutoNormal(man1->getMainObject(), man2->getMainObject(), false);
  }

  disable2D();

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
}
