#include "main.h"

#include "3dutils.h"

#include <math.h>

#include "utils.h"
#include "mesh.h"
#include "vector.h"
#include "texture.h"

#include "glapi.h"

int SKYBOX = -1;

/*
 * Luo pyörähdyskappaleen y-akselin ympäri annetuista pisteistä
 * Parametrina taulukollinen pisteitä,
 *             pisteidein määrä,
 *             jakojen määrä pyörähdyssuunnassa,
 *             jakojen määrä "pysty"suunnassa
 * Jos viimeinen parametri on sama kuin pisteiden määrä,
 * niin pyörähdyskappale vastaa suoraan annettujen pisteiden
 * pyörähdyskappaletta. Muulloin pisteet lasketaan kuutiollisella
 * interpoloinnilla annettujen pisteiden välillä.
 */
void createLathedSurface(point2d *points, point2d *pointderivates, int count,
                         int slices, int stacks) {
  int i, j;
  point2d *h1, *h2;
  point2d *derivates;
  if (pointderivates == NULL)
    derivates = new point2d[count];
  else
    derivates = pointderivates;
  // Derivaatta pisteessä i on (points[i+1]-points[i-1])/2 alkua ja loppua
  // lukuunottamatta
  for (i = 0; i < count; i++) {
    if (pointderivates == NULL ||
        (derivates[i].x == 0 && derivates[i].y == 0)) {
      if (i == 0)
        h1 = &points[0];
      else
        h1 = &points[i - 1];
      if (i == count - 1)
        h2 = &points[count - 1];
      else
        h2 = &points[i + 1];
      float dx, dy;
      dx = (h2->x - h1->x);
      dy = (h2->y - h1->y);
      if (i > 0 && i < count) {
        dx /= 2;
        dy /= 2;
      }
      derivates[i].x = dx;
      derivates[i].y = dy;
    }
  }

  float sif;
  int si;
  point2d newpoint, oldpoint;
  point2d derivate;
  point2d newnormal, oldnormal;
  point2d A, B, C, D;
  oldpoint.x = points[0].x;
  oldpoint.y = points[0].y;
  oldnormal.x = derivates[0].y;
  oldnormal.y = -derivates[0].x;
  point2d *p1, *p2, *d1, *d2;
  int i1, i2;
  float t;
  float x1, y1, z1, x2, y2, z2, nx1, ny1, nz1, nx2, ny2, nz2;
  for (i = 1; i <= stacks - (stacks / count); i++) {
    sif = (float)i * count / stacks;
    si = (int)sif;
    t = sif - si;
    i1 = si;
    i2 = si + 1;
    if (i2 >= count)
      i2 = count - 1;
    p1 = &points[i1];
    p2 = &points[i2];
    d1 = &derivates[i1];
    d2 = &derivates[i2];
    // Hermite-käyrä A*t^3 + B*t^2 + C*t + D
    // Hermite-käyrän derivaatta 3*A*t^2 + 2*B*t + C
    // Vakiot A,B,C ja D ovat laskettu siten, että:
    // 1. H(0)=p1;
    // 2. H(1)=p2;
    // 3. H'(0)=d1;
    // 4. H'(1)=d2;
    //
    // A = d2 - 2*p2 + d1 + 2*p1
    // B = -d2 + 3*p2 - 2*d1 - 3*p1
    // C = d1
    // D = p1
    A.x = d2->x - 2 * p2->x + d1->x + 2 * p1->x;
    A.y = d2->y - 2 * p2->y + d1->y + 2 * p1->y;
    B.x = -d2->x + 3 * p2->x - 2 * d1->x - 3 * p1->x;
    B.y = -d2->y + 3 * p2->y - 2 * d1->y - 3 * p1->y;
    C.x = d1->x;
    C.y = d1->y;
    D.x = p1->x;
    D.y = p1->y;

    newpoint.x = A.x * t * t * t + B.x * t * t + C.x * t + D.x;
    newpoint.y = A.y * t * t * t + B.y * t * t + C.y * t + D.y;

    derivate.x = 3 * A.x * t * t + 2 * B.x * t + C.x;
    derivate.y = 3 * A.y * t * t + 2 * B.y * t + C.y;

    newnormal.x = derivate.y;
    newnormal.y = -derivate.x;

    glBegin(GL_QUAD_STRIP);
    for (j = 0; j <= slices; j++) {
      float angle = j * 2 * PI / slices;

      nx2 = sin(angle) * newnormal.x;
      ny2 = newnormal.y;
      nz2 = cos(angle) * newnormal.x;
      glNormal3f(nx2, ny2, nz2);
      x2 = sin(angle) * newpoint.x;
      y2 = newpoint.y;
      z2 = cos(angle) * newpoint.x;
      glTexCoord2f(j * 1.0 / slices, 1.0 - (i * 1.0 / (stacks - 1)));
      glVertex3f(x2, y2, z2);

      nx1 = sin(angle) * oldnormal.x;
      ny1 = oldnormal.y;
      nz1 = cos(angle) * oldnormal.x;
      glNormal3f(nx1, ny1, nz1);
      x1 = sin(angle) * oldpoint.x;
      y1 = oldpoint.y;
      z1 = cos(angle) * oldpoint.x;
      glTexCoord2f(j * 1.0 / slices, 1.0 - ((i - 1) * 1.0 / (stacks - 1)));
      glVertex3f(x1, y1, z1);
    }
    glEnd();

    oldpoint.x = newpoint.x;
    oldpoint.y = newpoint.y;
    oldnormal.x = newnormal.x;
    oldnormal.y = newnormal.y;
  }
}

GLUquadricObj *spherequadric = gluNewQuadric();

void createSphere(float r, int slices, int stacks) {
  /*float phi, theta;
  int x, y;
  for (y = 0; y < stacks; y++){
      for (x = 0; x < slices; x++){
      }
  }*/
  gluSphere(spherequadric, r, slices, stacks);
}

#define DEFAULTSLICES 20
#define DEFAULTSTACKS 10

void createSphere(float r) { createSphere(r, DEFAULTSLICES, DEFAULTSTACKS); }

bool solvePointInTriangle(float *position, float *normal, Vertex *v1,
                          Vertex *v2, Vertex *v3, float *t, float *u,
                          float *v) {
  float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
  float det, inv_det;

  // find vectors for two edges sharing vert0
  vectorSub(edge1, v2->position, v1->position);
  vectorSub(edge2, v3->position, v1->position);

  // begin calculating determinant - also used to calculate U parameter
  vectorCross(pvec, normal, edge2);

  // if determinant is near zero, ray lies in plane of triangle
  det = vectorDot(edge1, pvec);

  if (det > -EPSILON && det < EPSILON)
    return false;
  inv_det = 1.0 / det;

  // calculate distance from vert0 to ray origin
  vectorSub(tvec, position, v1->position);

  // calculate U parameter and test bounds
  *u = vectorDot(tvec, pvec) * inv_det;
  if (*u < 0.0 || *u > 1.0)
    return false;

  // prepare to test V parameter
  vectorCross(qvec, tvec, edge1);

  // calculate V parameter and test bounds
  *v = vectorDot(normal, qvec) * inv_det;
  if (*v < 0.0 || *u + *v > 1.0)
    return false;

  // calculate t, ray intersects triangle
  *t = vectorDot(edge2, qvec) * inv_det;

  return true;
}

float distanceFromPlane(float point[3], float normal[3], float distance) {
  return vectorDot(point, normal) + distance;
}

void createSkyBox(float x, float y, float z, float w, float h, float l) {
  glEnable(GL_TEXTURE_2D);
  glClear(GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_LIGHTING);
  glShadeModel(GL_FLAT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(1.0, 1.0, 1.0, 0.5);

  float modelview[16];

  glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
  modelview[12] = modelview[13] = modelview[14] = 0.0f;
  glPushMatrix();
  glLoadMatrixf(modelview);

  if (SKYBOX > 0) {
    glCallList(SKYBOX);
  } else {

    SKYBOX = glGenLists(1);

    float d = 1.0 / 512;

    // glPushAttrib(GL_COLOR);

    glNewList(SKYBOX, GL_COMPILE_AND_EXECUTE);

    // glBindTexture(GL_TEXTURE_2D, SKY_BACK_ID);
    skybacktexture->enable();

    glBegin(GL_QUADS);
    glTexCoord2f(1 - d, 1 - d);
    glVertex3f(x + w, y, z);
    glTexCoord2f(1 - d, 0 + d);
    glVertex3f(x + w, y + h, z);
    glTexCoord2f(0 + d, 0 + d);
    glVertex3f(x, y + h, z);
    glTexCoord2f(0 + d, 1 - d);
    glVertex3f(x, y, z);

    glEnd();

    // glBindTexture(GL_TEXTURE_2D, SKY_FRONT_ID);
    skyfronttexture->enable();

    glBegin(GL_QUADS);
    glTexCoord2f(1 - d, 1 - d);
    glVertex3f(x, y, z + l);
    glTexCoord2f(1 - d, 0 + d);
    glVertex3f(x, y + h, z + l);
    glTexCoord2f(0 + d, 0 + d);
    glVertex3f(x + w, y + h, z + l);
    glTexCoord2f(0 + d, 1 - d);
    glVertex3f(x + w, y, z + l);
    glEnd();

    // glBindTexture(GL_TEXTURE_2D, SKY_TOP_ID);
    skytoptexture->enable();

    glBegin(GL_QUADS);
    glTexCoord2f(0 + d, 0 + d);
    glVertex3f(x + w, y + h, z + l);
    glTexCoord2f(1 - d, 0 + d);
    glVertex3f(x + w, y + h, z);
    glTexCoord2f(1 - d, 1 - d);
    glVertex3f(x, y + h, z);
    glTexCoord2f(0 + d, 1 - d);
    glVertex3f(x, y + h, z + l);
    /*glTexCoord2f(1.0f, 0+d); glVertex3f(x + w, y + h, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + w, y + h, z + l);
    glTexCoord2f(0+d, 1.0f); glVertex3f(x,	y + h, z + l);
    glTexCoord2f(0+d, 0+d); glVertex3f(x, y + h, z);*/

    glEnd();

    // glBindTexture(GL_TEXTURE_2D, SKY_BOTTOM_ID);
    skybottomtexture->enable();

    glBegin(GL_QUADS);
    glTexCoord2f(1 - d, 0 + d);
    glVertex3f(x, y, z);
    glTexCoord2f(1 - d, 1 - d);
    glVertex3f(x + w, y, z);
    glTexCoord2f(0 + d, 1 - d);
    glVertex3f(x + w, y, z + l);
    glTexCoord2f(0 + d, 0 + d);
    glVertex3f(x, y, z + l);

    glEnd();

    // glBindTexture(GL_TEXTURE_2D, SKY_LEFT_ID);
    skylefttexture->enable();

    glBegin(GL_QUADS);
    glTexCoord2f(1 - d, 0 + d);
    glVertex3f(x, y + h, z);
    glTexCoord2f(0 + d, 0 + d);
    glVertex3f(x, y + h, z + l);
    glTexCoord2f(0 + d, 1 - d);
    glVertex3f(x, y, z + l);
    glTexCoord2f(1 - d, 1 - d);
    glVertex3f(x, y, z);

    glEnd();

    // glBindTexture(GL_TEXTURE_2D, SKY_RIGHT_ID);
    skyrighttexture->enable();

    glBegin(GL_QUADS);
    glTexCoord2f(0 + d, 1 - d);
    glVertex3f(x + w, y, z);
    glTexCoord2f(1 - d, 1 - d);
    glVertex3f(x + w, y, z + l);
    glTexCoord2f(1 - d, 0 + d);
    glVertex3f(x + w, y + h, z + l);
    glTexCoord2f(0 + d, 0 + d);
    glVertex3f(x + w, y + h, z);

    glEnd();
    glEndList();
  }

  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glDisable(GL_BLEND);
}

void enable2D(void) {
  glDisable(GL_LIGHTING);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 1, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
}

void disable2D(void) {
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
}
