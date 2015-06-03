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
#include "font.h"
#include "run.h"
#include "menu.h"
#include "fight.h"

#include "glapi.h"

Camera endcamera;
Light endlight, endlight2;

// BasicBlockAppearance *endfloor = new BasicBlockAppearance(100, 1, 100);
BasicBlock *endfloor; // = new BasicBlock(20, 1, 15);

void initEnd(void) {
  endlight.setColor(1, 1, 1);
  endlight.setSpecular(1, 1, 1);
  endlight.setPosition(-0.5, BLOCKHEIGHT * 16, 0.5);
  endlight.setAttenuation(0, 0.0, 0.005);

  endlight2.setColor(1, 1, 1);
  endlight2.setSpecular(1, 1, 1);
  endlight2.setAttenuation(1.0, 0.0, 0.0);

  endfloor = new BasicBlock(30, 1, 20);
  // endfloor->material.setColor(0, 1, 0, 1);
  endfloor->setColor(0, 1, 0);
  endfloor->setPosition(-10, -BLOCKHEIGHT * 0.5, 0);
  endfloor->prepare();
}

int endingcounter;

void endRestart(void) {
  endingcounter = 0;
  // initEnd();
  // endfloor->prepare();
}

void stopEnding(void) {
  endlight.setEnabled(false);
  changeGameMode(MENUMODE);
  fightmusic->fadeOut(300);
  menuRestart();
}

float endfade;

void calculateEnd(int framecount) {
  endfade = -1;

  if (endingcounter < 200) {
    endfade = 1 - (float)endingcounter / 200;
  }
  endingcounter++;

  endlight.setEnabled(true);
  // endlight2.setEnabled(true);

  float target[3] = {0, 13, 0};
  endcamera.setTarget(target);
  endcamera.setPosition(10 + sin(framecount * 0.002) * 2,
                        20 + sin(framecount * 0.0017) * 2,
                        25 + cos(framecount * 0.002) * 2);
  // endcamera.setPosition(sin(framecount*0.01)*25, sin(framecount*0.007)*6+20,
  // cos(framecount*0.01)*25);

  // endlight.setPosition(40, 20, 0);
  endlight.setPosition(-sin(framecount * 0.007) * 10, 15,
                       cos(framecount * 0.007) * 2 + 22);

  if (keys[SDLK_ESCAPE]) {
    stopEnding();
  }
}

void drawEnd(int framecount) {
  glLoadIdentity();
  glTranslatef(10, 0, 0);

  endcamera.glUpdate();

  updateLights();

  glEnable(GL_LIGHTING);
  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glDisable(GL_TEXTURE_2D);

  endfloor->draw();

  glColor3f(1, 1, 0);

  drawTrophy();

  glRotatef(270, 0, 1, 0);
  glTranslatef(2 - BLOCKHEIGHT * 0.5, 0, 15 - BLOCKHEIGHT * 0.5);
  glScalef(3, 3, 3);

  winner->head->draw();
  winner->torso->draw();
  winner->lefthand->draw();
  winner->righthand->draw();
  winner->waist->draw();
  winner->leftleg->draw();
  winner->rightleg->draw();

  enable2D();

  glColor3f(1, 1, 1);

  if (winner->side == PLAYER1)
    print(0.05, 0.05, "Player 1 is\nthe winner", 0.09);
  if (winner->side == PLAYER2)
    print(0.05, 0.05, "Player 2 is\nthe winner", 0.09);

  if (endfade != -1) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, endfade);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
    glVertex2f(1, 1);
    glVertex2f(0, 1);
    glEnd();
  }

  disable2D();
}
