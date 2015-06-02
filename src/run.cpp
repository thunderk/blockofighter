#include "main.h"

#include <SDL.h>

#include "run.h"
#include "fight.h"
#include "menu.h"
#include "camera.h"
#include "end.h"
#include "graphics.h"
#include "3dutils.h"
#include "audio.h"
#include "font.h"
#include "legoblocks.h"
#include "glapi.h"

int gamemode;

bool changed;

bool gameinitialized = false;

void initFontTexture(void);

void initScenes(void) {
  knobgllist = glGenLists(1);
  setDetail(detail);

  // Simple loading-screen
  enable2D();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SDL_GL_SwapBuffers();

  initFontTexture();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  print(0.08, 0.4, "Loading...", 0.2);
  SDL_GL_SwapBuffers();

  disable2D();

  SKYBOX = -1;
  initTextures();
  initFight();
  initMenu();
  initEnd();
  changeGameMode(MENUMODE);
  // changeGameMode(ENDMODE);
  gameinitialized = true;
}

void changeGameMode(int newmode) {
  gamemode = newmode;
  changed = true;
}

void calculateFrame(int framecount) {
  switch (gamemode) {
  case MENUMODE:
    calculateMenu(framecount);
    break;
  case FIGHTMODE:
    calculateFight(framecount);
    break;
  case ENDMODE:
    calculateEnd(framecount);
    break;
  }
  updateAudio();
  changed = false;
}

void drawFrame(int framecount) {
  if (changed)
    calculateFrame(framecount);

  /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/

  glMatrixMode(GL_MODELVIEW);

  switch (gamemode) {
  case MENUMODE:
    drawMenu(framecount);
    break;
  case FIGHTMODE:
    drawFight(framecount);
    break;
  case ENDMODE:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawEnd(framecount);
    break;
  }

  SDL_GL_SwapBuffers();
}

/*int SKY_FRONT_ID;
int SKY_BACK_ID;
int SKY_LEFT_ID;
int SKY_RIGHT_ID;
int SKY_TOP_ID;
int SKY_BOTTOM_ID;*/

bool texturesloaded = false;

Texture *flaretexture;
Texture *skyfronttexture;
Texture *skybacktexture;
Texture *skylefttexture;
Texture *skyrighttexture;
Texture *skytoptexture;
Texture *skybottomtexture;
Texture *damageHead;
Texture *damageTorso;
Texture *damageHand;
Texture *damageLeg;
Texture *tuxtexture;
Texture *faceTexture;

void initFontTexture(void) {
  if (!texturesloaded) {
    float trans[3] = {1, 0, 0};
    fonttexture = new Texture();
    fonttexture->loadImage(DATAPATH "font.png", trans);
  } else {
    fonttexture->reload();
  }
}

void initTextures(void) {
  /*SKY_FRONT_ID = DRUID.loadTexture(SKYFRONT);
  SKY_BACK_ID = DRUID.loadTexture(SKYBACK);
  SKY_LEFT_ID = DRUID.loadTexture(SKYLEFT);
  SKY_RIGHT_ID = DRUID.loadTexture(SKYRIGHT);
  SKY_TOP_ID = DRUID.loadTexture(SKYTOP);
  SKY_BOTTOM_ID = DRUID.loadTexture(SKYBOTTOM);*/

  if (!texturesloaded) {
    skyfronttexture = new Texture();
    skyfronttexture->loadImage(SKYFRONT);
    skybacktexture = new Texture();
    skybacktexture->loadImage(SKYBACK);
    skylefttexture = new Texture();
    skylefttexture->loadImage(SKYLEFT);
    skyrighttexture = new Texture();
    skyrighttexture->loadImage(SKYRIGHT);
    skytoptexture = new Texture();
    skytoptexture->loadImage(SKYTOP);
    skybottomtexture = new Texture();
    skybottomtexture->loadImage(SKYBOTTOM);

    float something[3] = {1, 0, 0.5};
    damageHead = new Texture();
    damageHead->loadImage(DAMAGEHEAD, something);
    damageTorso = new Texture();
    damageTorso->loadImage(DAMAGETORSO, something);
    damageHand = new Texture();
    damageHand->loadImage(DAMAGEHAND, something);
    damageLeg = new Texture();
    damageLeg->loadImage(DAMAGELEG, something);
    faceTexture = new Texture();
    something[2] = 1;
    faceTexture->loadImage(FACE, something);

    float zeros[3] = {0, 0, 0};
    flaretexture = new Texture();
    flaretexture->loadImage(DATAPATH "flare.png", zeros);

    float pink[3] = {1, 0, 1};
    tuxtexture = new Texture();
    tuxtexture->loadImage(DATAPATH "tux.png", pink);
  } else {
    skyfronttexture->reload();
    skybacktexture->reload();
    skylefttexture->reload();
    skyrighttexture->reload();
    skytoptexture->reload();
    skybottomtexture->reload();

    damageHead->reload();
    damageTorso->reload();
    damageHand->reload();
    damageLeg->reload();

    flaretexture->reload();

    tuxtexture->reload();
  }
  texturesloaded = true;
}

void setDetail(int detail) {
  switch (detail) {
  case 0:
    knobdetail = 0;
    break;
  case 1:
    knobdetail = 5;
    break;
  case 2:
    knobdetail = 8;
    break;
  case 3:
    knobdetail = 16;
    break;
  }
  initKnob();
}
