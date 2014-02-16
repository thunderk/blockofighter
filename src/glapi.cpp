/*
 * $Id: glapi.cpp,v 1.9 2002/07/21 15:03:12 msell Exp $
 *
 *
 * $Log: glapi.cpp,v $
 * Revision 1.9  2002/07/21 15:03:12  msell
 * Äänet disabloitu
 *
 * Revision 1.8  2002/07/15 20:32:35  msell
 * Uudet valot ja ulkoasun parantelua
 *
 * Revision 1.7  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.6  2002/06/05 18:39:04  msell
 * Jotain pientä
 *
 * Revision 1.5  2002/06/05 15:00:41  msell
 * Palikoihin lisää detailia, facet jaetaan halutun kokosiin osiin
 *
 * Revision 1.4  2002/06/03 23:06:38  msell
 * no message
 *
 * Revision 1.3  2002/05/17 23:13:30  msell
 * Valot
 *
 * Revision 1.2  2002/05/16 18:41:16  msell
 * Vektorifunctioita ja kamera
 *
 * Revision 1.1  2002/05/15 14:36:39  msell
 * Yksinkertainen SDL-runko (Kääntyy toistaiseksi vain windowsissa).
 * Mukana myös musiikinsoitto fmodilla.
 *
 *
 *
 * $Date: 2002/07/21 15:03:12 $
 *
 */

#include "main.h"

#include "glapi.h"

void setupOpengl(int width, int height){
	//float ratio = (float)width/height;
	float ratio = 4.0/3.0;

	glShadeModel(GL_SMOOTH);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);

	glClearColor(0, 0, 0, 0);

	glEnable(GL_COLOR_MATERIAL);

	//Enables lighting with zero initial lights. Lights are created with Light-class
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

  float ambient[4]= {0.1, 0.1, 0.1, 1};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

  GLfloat zero[4] = {0, 0, 0, 1};
	GLfloat one[4] = {1, 1, 1, 1};

	//Default frontface lighting
  glMaterialfv(GL_FRONT, GL_AMBIENT, one);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, one);
	GLfloat specular[4] = {2, 2, 2, 1};
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, 120);

	//Never any backface lighting, except ambient
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


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
