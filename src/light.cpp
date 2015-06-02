#include "main.h"

#include "light.h"
#include "camera.h"
#include "vector.h"
#include "glapi.h"

static int glnextlightnum = 0;

static Light *lights[GL_MAX_LIGHTS];

Light::Light(void) {
  setPosition(0, 0, 0);
  setColor(1, 1, 1);
  setSpecular(0, 0, 0);
  setAttenuation(1, 0, 0);
  setEnabled(false);
  glnum = GL_LIGHT0 + glnextlightnum;
  lights[glnextlightnum] = this;
  glnextlightnum++;
}

void Light::setPosition(float x, float y, float z) {
  position[0] = x;
  position[1] = y;
  position[2] = z;
  position[3] = 1;
}

void Light::setDirection(float x, float y, float z) {
  position[0] = -x;
  position[1] = -y;
  position[2] = -z;
  position[3] = 0;
}

void Light::setColor(float red, float green, float blue) {
  diffuse[0] = red;
  diffuse[1] = green;
  diffuse[2] = blue;
  diffuse[3] = 1;
  glLightfv(glnum, GL_DIFFUSE, diffuse);
}

void Light::setSpecular(float red, float green, float blue) {
  specular[0] = red;
  specular[1] = green;
  specular[2] = blue;
  specular[3] = 1;
  glLightfv(glnum, GL_SPECULAR, specular);
}

void Light::setAttenuation(float constant, float linear, float quadratic) {
  attenuation[0] = constant;
  attenuation[1] = linear;
  attenuation[2] = quadratic;
  glLightf(glnum, GL_CONSTANT_ATTENUATION, attenuation[0]);
  glLightf(glnum, GL_LINEAR_ATTENUATION, attenuation[1]);
  glLightf(glnum, GL_QUADRATIC_ATTENUATION, attenuation[2]);
}

void Light::setEnabled(bool enabled) {
  this->enabled = enabled;
  if (enabled)
    glEnable(glnum);
  else
    glDisable(glnum);
}

void Light::glUpdate(void) { glLightfv(glnum, GL_POSITION, position); }

// extern Camera camera;

void Light::createFlare(Camera *camera) {
  glPushMatrix();

  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  int width = viewport[2];
  int height = viewport[3];

  glTranslatef(position[0], position[1], position[2]);

  GLboolean lightingenabled = glIsEnabled(GL_LIGHTING);
  glDisable(GL_LIGHTING);

  /*float cx=cameratarget.x-cameraposition.x;
  float cy=cameratarget.y-cameraposition.y;
  float cz=cameratarget.z-cameraposition.z;
  float len=sqrt(cx*cx+cy*cy+cz*cz);
  cx/=len;
  cy/=len;
  cz/=len;*/
  float dir[3];
  float cameratarget[3], cameraposition[3];
  camera->getTarget(cameratarget);
  camera->getPosition(cameraposition);
  vectorSub(dir, cameratarget, cameraposition);
  vectorNormalize(dir);

  float dir2[3];
  vectorSub(dir2, position, cameraposition);
  float distance = vectorDot(dir2, dir);

  /*float xd=(staticlightpositions[lightnumber].x-cameraposition.x)*cx;
  float yd=(staticlightpositions[lightnumber].y-cameraposition.y)*cy;
  float zd=(staticlightpositions[lightnumber].z-cameraposition.z)*cz;
  float distance=xd+yd+zd;*/

  float screencoords[3];
  /*GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

int width=viewport[2];
  int height=viewport[3];*/

  GLdouble modelviewm[16], projectionm[16];
  glGetDoublev(GL_MODELVIEW_MATRIX, modelviewm);
  glGetDoublev(GL_PROJECTION_MATRIX, projectionm);

  GLdouble wx, wy, wz;
  if (gluProject(0, 0, 0, modelviewm, projectionm, viewport, &wx, &wy, &wz) ==
      GL_FALSE) {
    printf("Failure\n");
  }

  screencoords[0] = (float)(2 * wx - width) / width;
  screencoords[1] = (float)(2 * wy - height) / height;
  screencoords[2] = wz;

  // getPointCoordinates(screencoords);
  // point3d screencoords = getPointCoordinates(0, 0, 0);

  glLoadIdentity();
  glTranslatef(screencoords[0], screencoords[1], 0);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  glBlendFunc(GL_ONE, GL_ONE);
  // glEnable(GL_TEXTURE_2D);
  // glBindTexture(GL_TEXTURE_2D, flaretexture->getId());

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  float sizey =
      6.0 / distance * 1.0; // staticlightflarebrightnesses[lightnumber];
  float sizex = sizey * height / width;

  if (distance > 0.5) {
    glBegin(GL_QUADS);
    // glColor3f(staticlightflarebrightnesses[lightnumber],staticlightflarebrightnesses[lightnumber],staticlightflarebrightnesses[lightnumber]);
    glColor3fv(diffuse);

    glTexCoord2f(0.0, 0.0);
    glVertex2f(-sizex, sizey);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(-sizex, -sizey);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(sizex, -sizey);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(sizex, sizey);
    glEnd();
  }

  // glDisable(GL_TEXTURE_2D);

  glDisable(GL_BLEND);

  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (lightingenabled)
    glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);

  glPopMatrix();
}

void updateLights(void) {
  int i;
  for (i = 0; i < glnextlightnum; i++) {
    Light *light = lights[i];
    light->glUpdate();
  }
}
