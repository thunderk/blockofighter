#include "main.h"

#include "appearance.h"
#include "utils.h"
#include "3dutils.h"
#include "glapi.h"

Appearance::Appearance(void) {}

void Appearance::prepare(void) {}

/*BoxAppearance::BoxAppearance(void){
    setDimension(-1, 1, -1, 1, -1, 1);
}

BoxAppearance::setDimension(float x1, float x2, float y1, float y2, float z1,
float z2){
    if (x1 > x2) swapFloat(&x1, &x2);
    if (y1 > y2) swapFloat(&y1, &y2);
    if (z1 > z2) swapFloat(&z1, &z2);
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
    this->z1 = z1;
    this->z2 = z2;
}

void BoxAppearance::draw(void){

  this->material.enable();

  glBegin(GL_QUADS);

        //Front Face
        glNormal3f(0, 0, 1);
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);
        // Back Face
        glNormal3f(0, 0, -1);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y1, z1);
        // Top Face
        glNormal3f(0, 1, 0);
        glVertex3f(x1, y2, z1);
        glVertex3f(x1, y2, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y2, z1);
        // Bottom Face
        glNormal3f(0, -1, 0);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);
        // Right face
        glNormal3f(x2, 0, 0);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y1, z2);
        // Left Face
        glNormal3f(x1, 0, 0);
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y1, z2);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y2, z1);
    glEnd();

  this->material.disable();
}*/

Material *Appearance::getMaterial(void) { return &this->material; }

void Appearance::setMaterial(Material matsku) { material = matsku; }

MultiAppearance::MultiAppearance(void) { appearances = NULL; }

void MultiAppearance::addAppearance(Appearance *appearance) {
  appearancelist *node = new appearancelist;
  node->data = appearance;
  node->next = appearances;
  appearances = node;
}

void MultiAppearance::prepare(void) {
  appearancelist *node = appearances;
  while (node != NULL) {
    node->data->prepare();
    node = node->next;
  }
}

void MultiAppearance::draw(void) {
  appearancelist *node = appearances;
  while (node != NULL) {
    node->data->draw();
    node = node->next;
  }
}
