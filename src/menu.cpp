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

Camera titlecamera;
Light titlelight;
World *titleworld;

Sound *changesound;
Sound *selectsound;
Sound *menumusic;

bool menuinitialized = false;

void initMenu(void) {
  if (!menuinitialized) {
    titleworld = new World();
  }

  titlelight.setColor(1, 1, 1);
  titlelight.setSpecular(1, 1, 1);
  titlelight.setPosition(-0.5, BLOCKHEIGHT * 16, 0.5);
  titlelight.setAttenuation(0.0, 0.0, 0.01);

  if (!menuinitialized) {
    Object *lamp;
    lamp = new Object();
    lamp->appearance = new LampAppearance();
    lamp->setPosition(-0.5, BLOCKHEIGHT * 15.5, 0.5);
    titleworld->addChild(lamp);

    // Floor
    BasicBlock *floorblock;

    floorblock = new BasicBlock(33, 1, 5);
    floorblock->setPosition(
        -0.5, -BLOCKHEIGHT / 2.0 + BLOCKHEIGHT * (4 * 3 + 1), 0.5 - 5);
    floorblock->setColor(0, 1, 0);
    titleworld->addChild(floorblock);

    floorblock = new BasicBlock(41, 1, 10);
    floorblock->setPosition(8.5 - 5, -BLOCKHEIGHT / 2.0, 0.5 - 2.5);
    floorblock->setColor(0, 1, 0);
    titleworld->addChild(floorblock);

    floorblock = new BasicBlock(1, 4 * 3, 1);
    floorblock->setPosition(-14.5, BLOCKHEIGHT * 4 * 3 / 2.0, 0.5 - 5);
    floorblock->setColor(1, 0, 0);
    titleworld->addChild(floorblock);

    floorblock = new BasicBlock(1, 4 * 3, 1);
    floorblock->setPosition(13.5, BLOCKHEIGHT * 4 * 3 / 2.0, 0.5 - 5);
    floorblock->setColor(1, 0, 0);
    titleworld->addChild(floorblock);

    // Letters

    // B
    /*int Bsize = 8;
    int Bwidth = 5;
    int Bletter[8][4] = {
        {0, 0, 4, 1},
        {0, 4, 3, 1},
        {0, 8, 4, 1},
        {0, 1, 1, 7},
        //{3, 1, 2, 1},
        {2, 3, 3, 1},
        {2, 5, 3, 1},
        //{3, 7, 2, 1},
        {4, 0, 1, 3},
        {4, 6, 1, 3}};*/
    int Bsize = 10;
    int Bwidth = 5;
    int Bletter[10][4] = {{0, 0, 4, 1},
                          {0, 4, 4, 1},
                          {0, 8, 4, 1},
                          {0, 1, 1, 7},
                          {3, 1, 2, 1},
                          {3, 3, 2, 1},
                          {3, 5, 2, 1},
                          {3, 7, 2, 1},
                          {4, 2, 1, 1},
                          {4, 6, 1, 1}};

    // l
    int lsize = 2;
    int lwidth = 4;
    int lletter[2][4] = {{0, 0, 4, 1}, {0, 1, 1, 4}};

    // o
    int osize = 4;
    int owidth = 4;
    int oletter[4][4] = {
        {0, 0, 4, 1}, {0, 4, 4, 1}, {0, 1, 1, 3}, {3, 1, 1, 3}};

    // c
    int csize = 5;
    int cwidth = 4;
    int cletter[5][4] = {
        {0, 0, 4, 1}, {0, 4, 4, 1}, {0, 1, 1, 3}, {3, 1, 1, 1}, {3, 3, 1, 1}};
    /*		{1, 0, 2, 1},
            {1, 4, 2, 1},
            {0, 1, 1, 3},
            {3, 1, 1, 1},
            {3, 3, 1, 1}};*/

    // k
    int ksize = 6;
    int kwidth = 4;
    int kletter[6][4] = {{0, 0, 1, 5},
                         {1, 2, 2, 1},
                         {2, 1, 2, 1},
                         {2, 3, 2, 1},
                         {3, 0, 1, 1},
                         {3, 4, 1, 1}};
    /*		{0, 0, 1, 5},
            {1, 2, 1, 1},
            {2, 1, 1, 1},
            {2, 3, 1, 1},
            {3, 0, 1, 1},
            {3, 4, 1, 1}};*/

    // F
    int Fsize = 3;
    int Fwidth = 3;
    int Fletter[3][4] = {{0, 0, 1, 7}, {0, 4, 3, 1}, {0, 7, 6, 1}};

    // i
    int isize = 1;
    int iwidth = 1;
    int iletter[1][4] = {{0, 0, 1, 4}};

    // g
    int gsize = 5;
    int gwidth = 4;
    int gletter[5][4] = {
        {0, 0, 4, 1}, {0, 4, 4, 1}, {0, 1, 1, 3}, {3, 1, 1, 1}, {2, 2, 2, 1}};

    // h
    int hsize = 3;
    int hwidth = 1;
    int hletter[3][4] = {{0, 0, 1, 5}, {3, 0, 1, 5}, {0, 2, 4, 1}};

    // t
    int tsize = 2;
    int twidth = 4;
    int tletter[2][4] = {{3, 0, 1, 6}, {0, 6, 7, 1}};

    // e
    int esize = 5;
    int ewidth = 4;
    int eletter[5][4] = {
        {0, 0, 4, 1}, {0, 4, 4, 1}, {0, 2, 3, 1}, {0, 1, 1, 1}, {0, 3, 1, 1}};

    // r
    int rsize = 6;
    int rwidth = 4;
    int rletter[6][4] = {{0, 0, 1, 5},
                         {0, 2, 3, 1},
                         {0, 4, 3, 1},
                         {2, 1, 2, 1},
                         {3, 0, 1, 1},
                         {2, 3, 2, 1}};
/*int rsize = 5;
int rwidth = 4;
int rletter[5][4] = {
    {0, 0, 1, 5},
    {0, 2, 3, 1},
    {0, 4, 3, 1},
    {3, 0, 1, 2},
    {3, 3, 1, 1}};*/

#define LETTERCOUNT 6
    int lettersizes[LETTERCOUNT] = {Bsize, lsize, osize, csize, ksize, osize};
    int letterwidths[LETTERCOUNT] = {Bwidth, lwidth, owidth,
                                     cwidth, kwidth, owidth};
    int *letters[LETTERCOUNT] = {&Bletter[0][0], &lletter[0][0],
                                 &oletter[0][0], &cletter[0][0],
                                 &kletter[0][0], &oletter[0][0]};

#define LETTERCOUNT2 7
    int lettersizes2[LETTERCOUNT2] = {Fsize, isize, gsize, hsize,
                                      tsize, esize, rsize};
    int letterwidths2[LETTERCOUNT2] = {Fwidth, iwidth, gwidth, hwidth,
                                       twidth, ewidth, rwidth};
    int *letters2[LETTERCOUNT2] = {
        &Fletter[0][0], &iletter[0][0], &gletter[0][0], &hletter[0][0],
        &tletter[0][0], &eletter[0][0], &rletter[0][0]};
    BasicBlock *letterblock;

    float z = 0.5;
    int i, j;
    int dx = -15;
    int dy = (int)(BLOCKHEIGHT * (4 * 3 + 1));
    int dz = -5;
    for (i = 0; i < LETTERCOUNT; i++) {
      int size = lettersizes[i];
      int width = letterwidths[i];
      for (j = 0; j < size; j++) {
        int x = letters[i][j * 4 + 0];
        int y = letters[i][j * 4 + 1] * 3;
        int w = letters[i][j * 4 + 2];
        int h = letters[i][j * 4 + 3] * 3;
        letterblock = new BasicBlock(w, h, 1);
        letterblock->setPosition(dx + x + w / 2.0,
                                 dy + BLOCKHEIGHT * (y + h / 2.0),
                                 dz + z + randomf(0.1));
        letterblock->setColor(1, 0.5, 1);
        titleworld->addChild(letterblock);
      }
      dx += width + 1;
    }
    dx = -5;
    dy = 0;
    dz = 0;
    for (i = 0; i < LETTERCOUNT2; i++) {
      int size = lettersizes2[i];
      int width = letterwidths2[i];
      for (j = 0; j < size; j++) {
        int x = letters2[i][j * 4 + 0];
        int y = letters2[i][j * 4 + 1] * 3;
        int w = letters2[i][j * 4 + 2];
        int h = letters2[i][j * 4 + 3] * 3;
        letterblock = new BasicBlock(w, h, 1);
        letterblock->setPosition(dx + x + w / 2.0,
                                 dy + BLOCKHEIGHT * (y + h / 2.0),
                                 dz + z + randomf(0.1));
        // float rotate[3] = {0, randomf(0.1), 0};
        // matrixCreateRotation(letterblock->rotation, rotate);
        letterblock->setColor(1, 0.5, 1);
        titleworld->addChild(letterblock);
      }
      dx += width + 1;
    }

    Object *flower;

    flower = new Object();
    flower->appearance =
        new FlowerAppearance(FLOWER_RED, FLOWER_WHITE, FLOWER_YELLOW);
    flower->setPosition(-7.5, 0, 1.5);
    titleworld->addChild(flower);

    flower = new Object();
    flower->appearance =
        new FlowerAppearance(FLOWER_YELLOW, FLOWER_RED, FLOWER_YELLOW);
    flower->setPosition(-11.5, 0, -2.5);
    titleworld->addChild(flower);

    flower = new Object();
    flower->appearance =
        new FlowerAppearance(FLOWER_WHITE, FLOWER_WHITE, FLOWER_RED);
    flower->setPosition(-14.5, 0, 0.5);
    titleworld->addChild(flower);

    changesound = new Sound(DATAPATH "menuchange.wav");
    selectsound = new Sound(DATAPATH "menuselect.wav");
    menumusic = new Sound(DATAPATH "menu.ogg", true);
  }

  titleworld->prepare();

  menuinitialized = true;
}

#define MODEMAIN 0
#define MODEOPTIONS 1

#define MAINSTART 0
#define MAINOPTIONS 1
#define MAINQUIT 2

#define OPTIONSRESOLUTION 0
#define OPTIONSFULLSCREEN 1
#define OPTIONSDETAIL 2
#define OPTIONSRETURN 3

int menuoption = MAINSTART;
int maxoption;
int menumode = MODEMAIN;
bool pressed = false;

float obx1, oby1, obx2, oby2;
float bx1, by1, bx2, by2;
float interpolator = 1.0;

int xres, yres;
int oldresolution;
int resolution = 2;
bool fullscreen = false;
int olddetail;
int detail = 3;

#define RESOLUTIONCOUNT 7
int resolutions[RESOLUTIONCOUNT][2] = {{640, 480},
                                       {800, 600},
                                       {1024, 768},
                                       {1280, 960},
                                       {1280, 1024},
                                       {1600, 1200},
                                       {1920, 1080}};

#define DETAILCOUNT 4
char *details[DETAILCOUNT] = {"Off", "Low", "Medium", "High"};

int menurestartcounter = -1;

void menuRestart(void) { menurestartcounter = 0; }

void menuMain(void) {
  interpolator = 0.0;
  menumode = MODEMAIN;
  menuoption = MAINOPTIONS;
  obx1 = bx1;
  oby1 = by1;
  obx2 = bx2;
  oby2 = by2;
}

float menufade;

int gamestart = 0;

bool loading = true;

void menuStartGame(void) {
  menumusic->fadeOut(300);
  gamestart = 200;
  menurestartcounter = -1;
}

void menuStartGame2(void) {
  titlelight.setEnabled(false);
  changeGameMode(FIGHTMODE);
  startFight();
  menurestartcounter = -1;
}

void menuOptions(void) {
  interpolator = 0.0;
  menumode = MODEOPTIONS;
  menuoption = OPTIONSRESOLUTION;
  obx1 = bx1;
  oby1 = by1;
  obx2 = bx2;
  oby2 = by2;
  oldresolution = resolution;
  olddetail = detail;
}

int quitcounter = -1;

void menuEscPressed(void) {
  menurestartcounter = -1;
  // menumusic->stop();
  menumusic->fadeOut(200);
  quitcounter = 0;
}

void menuQuit(void) { exitProgram(0); }

void menuResolution(int dir) {
  resolution += dir;
  if (resolution < 0)
    resolution = 0;
  if (resolution >= RESOLUTIONCOUNT)
    resolution = RESOLUTIONCOUNT - 1;
  // resolution = (resolution + RESOLUTIONCOUNT) % RESOLUTIONCOUNT;
}

void calculateMenu(int framecount) {
  if (framecount == 1) {
    menumusic->setVolume(0);
    menumusic->play();
    menumusic->fadeIn(300);
  }
  if (menurestartcounter != -1) {
    menurestartcounter++;
    if (menurestartcounter == 300) {
      menumusic->play();
      menumusic->fadeIn(100);
      menurestartcounter = -1;
    }
  }

  menufade = -1;

  titlelight.setEnabled(true);

  if (framecount < 200) {
    menufade = 1 - framecount / 200.0;
  } else {
    loading = false;
  }

  if (gamestart > 0) {
    gamestart--;
    if (gamestart == 0) {
      menuStartGame2();
    }
    menufade = (200 - gamestart) / 200.0;
  }

  if (quitcounter != -1) {
    menufade = quitcounter / 200.0;
    quitcounter++;
    if (quitcounter == 200)
      menuQuit();
  }

  float cameratarget[3] = {0, 0, 0};
  titlecamera.setPosition(sin(framecount * 0.001) * 2 - 8,
                          sin(framecount * 0.0033) * 2 + 15,
                          cos(framecount * 0.001) * 2 + 25);
  titlecamera.setTarget(cameratarget);

  // titlelight.setPosition(sin(framecount*0.01)*5-4, sin(framecount*0.017)*5+5,
  // cos(framecount*0.01)*5+5);

  titleworld->move();

  xres = resolutions[resolution][0];
  yres = resolutions[resolution][1];

  switch (menumode) {
  case MODEMAIN:
    maxoption = 2;

    bx1 = 0.03;
    by1 = 0.49;
    bx2 = 0.68;
    by2 = 0.96;

    break;
  case MODEOPTIONS:
    maxoption = 3;

    bx1 = 0.1;
    by1 = 0.3;
    bx2 = 0.9;
    by2 = 0.8;
    break;
  }

  if (interpolator < 1.0) {
    interpolator += 0.02;
  } else {
    interpolator = 1.0;
    if (menufade == -1) {
      if (keys[SDLK_DOWN]) {
        if (!pressed) {
          /*if (menuoption < maxoption){
              menuoption++;
              changesound->play();
          }*/
          menuoption = (menuoption + 1) % (maxoption + 1);
          changesound->play();
          pressed = true;
        }
      } else if (keys[SDLK_UP]) {
        if (!pressed) {
          /*if (menuoption > 0){
              menuoption--;
              changesound->play();
          }*/
          menuoption = (menuoption + maxoption) % (maxoption + 1);
          changesound->play();
          pressed = true;
        }
      } else if (keys[SDLK_LEFT]) {
        if (!pressed) {
          switch (menumode) {
          case MODEOPTIONS:
            switch (menuoption) {
            case OPTIONSRESOLUTION:
              menuResolution(-1);
              break;
            case OPTIONSDETAIL:
              if (detail > 0)
                detail--;
              break;
            }
            break;
          }
          selectsound->play();
          pressed = true;
        }
      } else if (keys[SDLK_RIGHT]) {
        if (!pressed) {
          switch (menumode) {
          case MODEOPTIONS:
            switch (menuoption) {
            case OPTIONSRESOLUTION:
              menuResolution(1);
              break;
            case OPTIONSDETAIL:
              if (detail < DETAILCOUNT - 1)
                detail++;
              break;
            }
            break;
          }
          selectsound->play();
          pressed = true;
        }
      } else if (keys[SDLK_ESCAPE]) {
        if (!pressed) {
          switch (menumode) {
          case MODEMAIN:
            if (menuoption != MAINQUIT) {
              menuoption = MAINQUIT;
              changesound->play();
            } else
              menuEscPressed();
            break;
          case MODEOPTIONS:
            selectsound->play();
            resolution = oldresolution;
            detail = olddetail;
            menuMain();
            break;
          }
          pressed = true;
        }
      } else if (keys[SDLK_RETURN]) {
        if (!pressed) {
          switch (menumode) {
          case MODEMAIN:
            switch (menuoption) {
            case MAINSTART:
              menuStartGame();
              break;
            case MAINOPTIONS:
              menuOptions();
              break;
            case MAINQUIT:
              menuEscPressed();
              break;
            }
            break;
          case MODEOPTIONS:
            switch (menuoption) {
            case OPTIONSRESOLUTION:
              if (resolution != oldresolution)
                changeResolution(xres, yres, fullscreen);
              oldresolution = resolution;
              break;
            case OPTIONSFULLSCREEN:
              fullscreen = !fullscreen;
              changeResolution(xres, yres, fullscreen);
              break;
            case OPTIONSDETAIL:
              setDetail(detail);
              olddetail = detail;
              break;
            case OPTIONSRETURN:
              if (resolution != oldresolution) {
                changeResolution(xres, yres, fullscreen);
                oldresolution = resolution;
              }
              if (detail != olddetail) {
                setDetail(detail);
                olddetail = detail;
              }
              menuMain();
              break;
            }
            break;
          }
          selectsound->play();
          pressed = true;
        }
      } else
        pressed = false;
    }
  }
}

void drawMenu(int framecount) {
  // createSkyBox(0, -20, 0, 400, 200, 400);
  createSkyBox(-200, -200, -200, 400, 400, 400);
  glLoadIdentity();
  titlecamera.glUpdate();

  updateLights();

  titleworld->draw();

  flaretexture->enable();
  titlelight.createFlare(&titlecamera);
  flaretexture->disable();

  /*//2D-view
  glDisable(GL_LIGHTING);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 1, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();*/
  enable2D();

  glColor3f(1, 1, 1);
  print(0.73, 0.58, "Programming:\n"
                    "  Miika Sell\n"
                    "  Juha Kaarlas\n"
                    "\n"
                    "Graphics:\n"
                    "  Miika Sell\n"
                    "  Juha Kaarlas\n"
                    "\n"
                    "Musics:\n"
                    "  Osmand",
        0.03);

  print(0.35, 0.965, "http://blockofighter.kicks-ass.net/", 0.02);

  print(0.86, 0.96, "Version 2.0", 0.02);

  tuxtexture->enable();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor3f(1, 1, 1);

  float tuxx = 0.9;
  float tuxy = 0.02;
  float tuxw = 0.1 * 3 / 4;
  float tuxh = 0.1;
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(tuxx, tuxy);

  glTexCoord2f(1, 0);
  glVertex2f(tuxx + tuxw, tuxy);

  glTexCoord2f(1, 1);
  glVertex2f(tuxx + tuxw, tuxy + tuxh);

  glTexCoord2f(0, 1);
  glVertex2f(tuxx, tuxy + tuxh);
  glEnd();
  tuxtexture->disable();

  glColor3f(1, 1, 1);
  print(0.88, 0.12, "powaaaaaa", 0.02);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0, 0, 0, 0.5);
  float x1, y1, x2, y2;
  x1 = (1 - interpolator) * obx1 + interpolator * bx1;
  y1 = (1 - interpolator) * oby1 + interpolator * by1;
  x2 = (1 - interpolator) * obx2 + interpolator * bx2;
  y2 = (1 - interpolator) * oby2 + interpolator * by2;
  glBegin(GL_QUADS);
  glVertex2f(x1, y1);
  glVertex2f(x2, y1);
  glVertex2f(x2, y2);
  glVertex2f(x1, y2);
  glEnd();

  if (interpolator == 1.0) {
    switch (menumode) {
    case MODEMAIN:
      glColor3f(1, 1, 1);
      print(0.05, 0.5, "Start game", 0.1);
      print(0.05, 0.65, "Options", 0.1);
      print(0.05, 0.8, "Quit", 0.1);

      x1 = 0.04;
      x2 = 0.67;
      switch (menuoption) {
      case 0:
        y1 = 0.5;
        y2 = 0.65;
        break;
      case 1:
        y1 = 0.65;
        y2 = 0.79;
        break;
      case 2:
        y1 = 0.79;
        y2 = 0.95;
        break;
      }
      break;
    case MODEOPTIONS:
      glColor3f(1, 1, 1);
      char resolutionstring[22];
      sprintf(resolutionstring, "Resolution: %ix%i", xres, yres);
      print(0.12, 0.32, resolutionstring, 0.07);
      print(0.12, 0.42, "Toggle fullscreen", 0.07);
      char detailstring[22];
      sprintf(detailstring, "Detail:     %s", details[detail]);
      print(0.12, 0.52, detailstring, 0.07);
      print(0.12, 0.68, "Save and return", 0.07);

      x1 = 0.11;
      x2 = 0.89;
      switch (menuoption) {
      case 0:
        y1 = 0.32;
        y2 = 0.42;
        break;
      case 1:
        y1 = 0.42;
        y2 = 0.52;
        break;
      case 2:
        y1 = 0.52;
        y2 = 0.62;
        break;
      case 3:
        y1 = 0.68;
        y2 = 0.78;
        break;
      }
      break;
    }

    glLineWidth(2);

    glColor4f(sin(framecount * 0.04) * 0.4 + 0.6,
              sin(framecount * 0.04) * 0.4 + 0.6,
              sin(framecount * 0.04) * 0.4 + 0.6, 0.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
  }

  if (menufade != -1) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0, 0, 0, menufade);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
    glVertex2f(1, 1);
    glVertex2f(0, 1);
    glEnd();
    if (loading) {
      glColor4f(menufade, menufade, menufade, menufade);
      print(0.08, 0.4, "Loading...", 0.2);
    }
  }

  disable2D();
  /*//Back to 3D-view
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);*/
}
