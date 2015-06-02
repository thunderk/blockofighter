#include "main.h"

#include <math.h>

#include "legoblocks.h"
#include "utils.h"
#include "3dutils.h"
#include "objectfactory.h"
#include "vector.h"
#include "glapi.h"

BasicBlock::BasicBlock(int width, int height, int depth)
    : MeshObject(
          createBox(-width / 2.0, width / 2.0, -height / 2.0 * BLOCKHEIGHT,
                    BLOCKHEIGHT * height / 2.0, -depth / 2.0, depth / 2.0)) {
  appearance = new BasicBlockAppearance(width, height, depth);
  // geometry = new MeshShape(this);
}

void BasicBlock::setColor(float red, float green, float blue) {
  appearance->getMaterial()->setColor(red, green, blue, 1);
}

BasicBlockAppearance::BasicBlockAppearance(int width, int height, int depth) {
  this->width = width;
  this->height = height;
  this->depth = depth;
  vectorSet(displacement, 0, 0, 0);
  gllist = glGenLists(1);
  usematerial = true;
}

void BasicBlockAppearance::prepare() {
  glNewList(gllist, GL_COMPILE);

  float width = this->width;
  float height = this->height * BLOCKHEIGHT;

  if (usematerial)
    material.enable();
  { // Block
    // Front Face
    glPushMatrix();
    glTranslatef(-width / 2.0, -height / 2.0, depth / 2.0);
    drawDetailRectangle(width, height);
    glPopMatrix();

    // Back Face
    glPushMatrix();
    glTranslatef(width / 2.0, -height / 2.0, -depth / 2.0);
    glRotatef(180, 0, 1, 0);
    drawDetailRectangle(width, height);
    glPopMatrix();

    // Top Face
    glPushMatrix();
    glTranslatef(-width / 2.0, height / 2.0, depth / 2.0);
    glRotatef(-90, 1, 0, 0);
    drawDetailRectangle(width, depth);
    glPopMatrix();

    // Bottom Face
    glPushMatrix();
    glTranslatef(-width / 2.0, -height / 2.0, -depth / 2.0);
    glRotatef(90, 1, 0, 0);
    drawDetailRectangle(width, depth);
    glPopMatrix();

    // Right face
    glPushMatrix();
    glTranslatef(width / 2.0, -height / 2.0, depth / 2.0);
    glRotatef(90, 0, 1, 0);
    drawDetailRectangle(depth, height);
    glPopMatrix();

    // Left Face
    glPushMatrix();
    glTranslatef(-width / 2.0, -height / 2.0, -depth / 2.0);
    glRotatef(-90, 0, 1, 0);
    drawDetailRectangle(depth, height);
    glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(0.5 - width / 2.0, height - height / 2.0, 0.5 - depth / 2.0);
  int x, z;
  for (x = 0; x < width; x++) {
    // glPushMatrix();
    for (z = 0; z < depth; z++) {
      createKnob();
      glTranslatef(0, 0, 1);
    }
    glTranslatef(1, 0, -depth);
    // glPopMatrix();
  }
  glPopMatrix();

  if (usematerial)
    material.disable();
  glEndList();
}

void BasicBlockAppearance::draw() {
  glPushMatrix();
  glTranslatef(displacement[0], displacement[1], displacement[2]);
  glCallList(gllist);
  glPopMatrix();
  // prepare();
}

#define BLOCKDETAILGRID 1

void drawDetailRectangle(float width, float height) {
  glBegin(GL_QUADS);
  float x, y, x2, y2;
  glNormal3f(0, 0, 1);

  for (y = 0; y < height; y += BLOCKDETAILGRID) {
    y2 = y + BLOCKDETAILGRID;
    if (y2 > height)
      y2 = height;
    for (x = 0; x < width; x += BLOCKDETAILGRID) {
      x2 = x + BLOCKDETAILGRID;
      if (x2 > width)
        x2 = width;

      glTexCoord2f(x / width, y / height);
      glVertex3f(x, y, 0);

      glTexCoord2f(x2 / width, y / height);
      glVertex3f(x2, y, 0);

      glTexCoord2f(x2 / width, y2 / height);
      glVertex3f(x2, y2, 0);

      glTexCoord2f(x / width, y2 / height);
      glVertex3f(x, y2, 0);
    }
  }
  glEnd();
}

#define KNOBROUNDNESS 0.03

int knobgllist;
int knobdetail;

void renderKnob(int knobsegments) {
  point2d knobpoints[4];
  knobpoints[0].x = 0.3;
  knobpoints[0].y = 0;
  knobpoints[1].x = 0.3;
  knobpoints[1].y = BLOCKHEIGHT * 0.5 - KNOBROUNDNESS;
  knobpoints[2].x = 0.3 - KNOBROUNDNESS;
  knobpoints[2].y = BLOCKHEIGHT * 0.5;
  knobpoints[3].x = 0;
  knobpoints[3].y = BLOCKHEIGHT * 0.5;

  point2d knobderivates[4];
  knobderivates[0].x = 0;
  knobderivates[0].y = knobpoints[1].y - knobpoints[0].y;
  knobderivates[1].x = 0;
  knobderivates[1].y = knobpoints[2].y - knobpoints[1].y;
  knobderivates[2].x = knobpoints[2].x - knobpoints[1].x;
  knobderivates[2].y = 0;
  knobderivates[3].x = knobpoints[3].x - knobpoints[2].x;
  knobderivates[3].y = 0;

  createLathedSurface(knobpoints, knobderivates, 4, knobsegments, 4);
}

void initKnob(void) {
  glNewList(knobgllist, GL_COMPILE);

  renderKnob(knobdetail);

  glEndList();
}

void createKnob(int knobsegments) {
  if (knobsegments != -1) {
    renderKnob(knobsegments);
    return;
  }
  glCallList(knobgllist);
}

float knobroundness = 0.05;
float pillarroundness = 0.03;

HeadAppearance::HeadAppearance(void) { gllist = glGenLists(1); }

void HeadAppearance::prepare(void) {
  glNewList(gllist, GL_COMPILE);

  glPushMatrix();

  glTranslatef(0, -0.5, 0);

  point2d headpoints[14];

  headpoints[0].x = 0.0;
  headpoints[0].y = BLOCKHEIGHT * (0);
  headpoints[1].x = 0.4;
  headpoints[1].y = BLOCKHEIGHT * (0);
  headpoints[2].x = 0.45;
  headpoints[2].y = BLOCKHEIGHT * (0.35);
  headpoints[3].x = 0.55;
  headpoints[3].y = BLOCKHEIGHT * (0.5);
  headpoints[4].x = 0.62 * 1.0;
  headpoints[4].y = BLOCKHEIGHT * (0.65);
  headpoints[5].x = 0.65 * 1.0;
  headpoints[5].y = BLOCKHEIGHT * (1);
  headpoints[6].x = 0.65 * 1.0;
  headpoints[6].y = BLOCKHEIGHT * (1.75);
  headpoints[7].x = 0.65 * 1.0;
  headpoints[7].y = BLOCKHEIGHT * (2.35);
  headpoints[8].x = 0.62 * 1.0;
  headpoints[8].y = BLOCKHEIGHT * (2.60);
  headpoints[9].x = 0.55 * 1.0;
  headpoints[9].y = BLOCKHEIGHT * (2.80);
  headpoints[10].x = 0.4;
  headpoints[10].y = BLOCKHEIGHT * (2.95);
  headpoints[11].x = 0.3;
  headpoints[11].y = BLOCKHEIGHT * 3.5 - pillarroundness;
  headpoints[12].x = 0.3 - pillarroundness;
  headpoints[12].y = BLOCKHEIGHT * 3.5;
  headpoints[13].x = 0;
  headpoints[13].y = BLOCKHEIGHT * 3.5;
  headpoints[11].x = 0;
  headpoints[11].y = BLOCKHEIGHT * 3.0;

  glColor4f(0.8, 0.8, 0.0, 1.0);

  faceTexture->enable();
  glBlendFunc(GL_ONE, GL_SRC_ALPHA);
  createLathedSurface(headpoints, NULL, 12, 16, 24);
  faceTexture->disable();

  glTranslatef(0, BLOCKHEIGHT * 3 - 0.05, 0);

  createKnob(16);

  glPopMatrix();

  glEndList();
}

void HeadAppearance::draw(void) { glCallList(gllist); }

FlowerAppearance::FlowerAppearance(int color1, int color2, int color3) {
  gllist = glGenLists(1);
  this->color1 = color1;
  this->color2 = color2;
  this->color3 = color3;
}

void FlowerAppearance::prepare(void) {
  glNewList(gllist, GL_COMPILE);

  glPushMatrix();

  int colors[] = {color1, color2, color3};

  glColor3f(0.0, 0.6, 0.0);

  point2d basepoints[8];
  basepoints[0].x = 0.4;
  basepoints[0].y = 0;
  basepoints[1].x = 0.4;
  basepoints[1].y = BLOCKHEIGHT * 1.5 - pillarroundness;
  basepoints[2].x = 0.4 - pillarroundness;
  basepoints[2].y = BLOCKHEIGHT * 1.5;
  basepoints[3].x = 0.3 + pillarroundness;
  basepoints[3].y = BLOCKHEIGHT * 1.5;
  basepoints[4].x = 0.3;
  basepoints[4].y = BLOCKHEIGHT * 1.5 + pillarroundness;
  basepoints[5].x = 0.3;
  basepoints[5].y = BLOCKHEIGHT * 2.0 - pillarroundness;
  basepoints[6].x = 0.3 - pillarroundness;
  basepoints[6].y = BLOCKHEIGHT * 2.0;
  basepoints[7].x = 0;
  basepoints[7].y = BLOCKHEIGHT * 2.0;

  point2d basederivates[8];
  basederivates[0].x = 0;
  basederivates[0].y = basepoints[1].y - basepoints[0].y;
  basederivates[1].x = 0;
  basederivates[1].y = basepoints[2].y - basepoints[1].y;
  basederivates[2].x = basepoints[2].x - basepoints[1].x;
  basederivates[2].y = 0;
  basederivates[3].x = basepoints[4].x - basepoints[3].x;
  basederivates[3].y = 0;
  basederivates[4].x = 0;
  basederivates[4].y = basepoints[4].y - basepoints[3].y;
  basederivates[5].x = 0;
  basederivates[5].y = basepoints[6].y - basepoints[5].y;
  basederivates[6].x = basepoints[6].x - basepoints[5].x;
  basederivates[6].y = 0;
  basederivates[7].x = basepoints[7].x - basepoints[6].x;
  basederivates[7].y = 0;

  createLathedSurface(basepoints, basederivates, 8, 8, 8);

  int i, j;
  for (i = 0; i < 3; i++) {
    glColor3f(0.0, 0.6, 0.0);
    glPushMatrix();
    glTranslatef(0, BLOCKHEIGHT, 0.4);
    glRotatef(20 - 90, 1, 0, 0);
    gluCylinder(gluNewQuadric(), 0.1, 0.1, BLOCKHEIGHT * (3 + i * 0.7), 4, 1);
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, BLOCKHEIGHT * (3 + i * 0.7), 0);

    float r = 0.0, g = 0.0, b = 0.0;
    switch (colors[i]) {
    case FLOWER_RED:
      r = 1.0;
      g = 0.0;
      b = 0.0;
      break;
    case FLOWER_YELLOW:
      r = 1.0;
      g = 1.0;
      b = 0.0;
      break;
    case FLOWER_WHITE:
      r = 1.0;
      g = 1.0;
      b = 1.0;
      break;
    }

    glDisable(GL_CULL_FACE);
    glColor3f(r, g, b);
    createKnob();

    /* Terälehdet tehdään triangle-fanilla */
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    float x, z;
    for (j = 0; j < 24; j += 4) {
      x = sin((j + 0) * 2 * PI / 24) * 0.4;
      z = cos((j + 0) * 2 * PI / 24) * 0.4;
      glVertex3f(x, 0.0, z);
      x = sin((j + 1) * 2 * PI / 24) * 0.55;
      z = cos((j + 1) * 2 * PI / 24) * 0.55;
      glVertex3f(x, 0.0, z);
      x = sin((j + 2) * 2 * PI / 24) * 0.6;
      z = cos((j + 2) * 2 * PI / 24) * 0.6;
      glVertex3f(x, 0.0, z);
      x = sin((j + 3) * 2 * PI / 24) * 0.55;
      z = cos((j + 3) * 2 * PI / 24) * 0.55;
      glVertex3f(x, 0.0, z);
    }
    glVertex3f(0, 0.0, 0.4);
    glEnd();
    glEnable(GL_CULL_FACE);

    glPopMatrix();

    glRotatef(120, 0, 1, 0);
  }

  glPopMatrix();

  glEndList();
}

void FlowerAppearance::draw(void) { glCallList(gllist); }

LampAppearance::LampAppearance(void) { gllist = glGenLists(1); }

void LampAppearance::prepare(void) {
  glNewList(gllist, GL_COMPILE);

  glPushMatrix();

  // glTranslatef(0, -1, 0);

  // glRotatef(180, 1, 0, 0);

  glDisable(GL_LIGHTING);

  point2d lightpoints[11];
  lightpoints[0].x = 0.4;
  lightpoints[0].y = BLOCKHEIGHT * (0);
  lightpoints[1].x = 0.55;
  lightpoints[1].y = BLOCKHEIGHT * (0);
  lightpoints[2].x = 0.62;
  lightpoints[2].y = BLOCKHEIGHT * (0 + 0.15);
  lightpoints[3].x = 0.65;
  lightpoints[3].y = BLOCKHEIGHT * (0 + 0.5);
  lightpoints[4].x = 0.68;
  lightpoints[4].y = BLOCKHEIGHT * (0 + 1.25);
  lightpoints[5].x = 0.65;
  lightpoints[5].y = BLOCKHEIGHT * (0 + 2);
  lightpoints[6].x = 0.62;
  lightpoints[6].y = BLOCKHEIGHT * (0 + 2.35);
  lightpoints[7].x = 0.55;
  lightpoints[7].y = BLOCKHEIGHT * (0 + 2.5);
  lightpoints[8].x = 0.4;
  lightpoints[8].y = BLOCKHEIGHT * (0 + 2.5);
  lightpoints[9].x = 0.4;
  lightpoints[9].y = BLOCKHEIGHT * (0 + 3);
  lightpoints[10].x = 0.0;
  lightpoints[10].y = BLOCKHEIGHT * (0 + 3);
  glColor4f(0.8, 0.8, 0.8, 0.5);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  createLathedSurface(lightpoints, NULL, 11, 8, 11);

  glEnable(GL_LIGHTING);

  /*glColor3f(0.5, 0.5, 0.5);

  glBegin(GL_LINES);
      glVertex3f(0, 1, 0);
      glVertex3f(0, -100, 0);
  glEnd();*/

  /*float screencoords[3]
  getPointCoordinates(0,lighty,0);

  glLoadIdentity();
  glTranslatef(screencoords.x,screencoords.y,0);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  glBlendFunc(GL_ONE,GL_ONE);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,*flaretexture);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  float sizey=8.0/distance*staticlightflarebrightnesses[lightnumber];
  float sizex=sizey*height/width;

  if (distance>0.5){
      glBegin(GL_QUADS);
          glColor3f(staticlightflarebrightnesses[lightnumber],staticlightflarebrightnesses[lightnumber],staticlightflarebrightnesses[lightnumber]);

          glTexCoord2f(0.0, 0.0);
          glVertex2f(-sizex,sizey);

          glTexCoord2f(0.0, 1.0);
          glVertex2f(-sizex,-sizey);

          glTexCoord2f(1.0, 1.0);
          glVertex2f( sizex,-sizey);

          glTexCoord2f(1.0, 0.0);
          glVertex2f( sizex,sizey);
      glEnd();
  }

  glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();*/

  glPopMatrix();

  glEndList();
}

void LampAppearance::draw(void) { glCallList(gllist); }
