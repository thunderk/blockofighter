#include "main.h"

#include "glapi.h"

void setupOpengl(int width, int height) {
  // float ratio = (float)width/height;
  float ratio = 4.0 / 3.0;

  glShadeModel(GL_SMOOTH);

  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glClearDepth(1.0);

  glClearColor(0, 0, 0, 0);

  glEnable(GL_COLOR_MATERIAL);

  // Enables lighting with zero initial lights. Lights are created with
  // Light-class
  glEnable(GL_LIGHTING);
  glDisable(GL_LIGHT0);

  float ambient[4] = {0.1, 0.1, 0.1, 1};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

  GLfloat zero[4] = {0, 0, 0, 1};
  GLfloat one[4] = {1, 1, 1, 1};

  // Default frontface lighting
  glMaterialfv(GL_FRONT, GL_AMBIENT, one);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, one);
  GLfloat specular[4] = {2, 2, 2, 1};
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, 120);

  // Never any backface lighting, except ambient
  glMaterialfv(GL_BACK, GL_AMBIENT, one);
  glMaterialfv(GL_BACK, GL_DIFFUSE, zero);
  glMaterialfv(GL_BACK, GL_SPECULAR, zero);

  glViewport(0, 0, width, height);

  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_NORMALIZE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60.0, ratio, 1.0, 1024.0);

  glColorMask(true, true, true, true);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
