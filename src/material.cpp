#include "main.h"

#include "material.h"
#include "glapi.h"
#include "graphics.h"

Material::Material(void) {
  setColor(1, 1, 1, 1);
  this->texture = new Texture;
}

bool Material::loadTexture(char *path) {
  if (!this->texture) {
    this->texture = new Texture;
  }
  if (this->texture->loadImage(path)) {
    setColor(1, 1, 1, 1);
    return true;
  }
  return false;
}

void Material::freeTexture(void) { this->texture->~Texture(); }

void Material::setColor(float red, float green, float blue, float alpha) {
  color[0] = red;
  color[1] = green;
  color[2] = blue;
  color[3] = alpha;
}

const float *Material::getColor(void) { return color; }

void Material::enable(void) {
  enabled = true;
  glColor4fv(color);
  this->texture->enable();
}

void Material::disable(void) {
  enabled = false;
  this->texture->disable();
}

bool Material::isEnabled(void) { return enabled; }

Texture *Material::getTexture(void) { return this->texture; }

void Material::setTexture(Texture *tex) {
  // this->texture->~Texture;
  this->texture = tex;
}
