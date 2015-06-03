#include "texture.h"
#include "graphics.h"

Texture::Texture(void) {
  this->textureId = -1;
  this->enabled = false;
}

Texture::~Texture(void) {
  if (textureId != -1) {
    DRUID.freeTexture(textureId);
    textureId = -1;
    enabled = false;
  }
}

Texture::Texture(int id) {
  if (id > -1) {
    this->textureId = id;
    this->enabled = false;
  } else {
    this->textureId = -1;
    this->enabled = false;
  }
}

bool Texture::loadImage(char *path) {
  format = GL_RGB;

  texture = IMG_Load(path);

  // texture = SDL_DisplayFormatAlpha(texture);

  this->textureId = DRUID.loadTexture(texture, -1);
  // this->textureId = DRUID.loadTexture(path, -1);
  this->enable();
  return this->isValidId();
}

bool Texture::loadImage(char *path, float *trans) {
  format = GL_RGBA;

  texture = IMG_Load(path);

  Uint32 colorKey =
      SDL_MapRGB(texture->format, (Uint8)(trans[0] * 255),
                 (Uint8)(trans[1] * 255), (Uint8)(trans[2] * 255));
  // SDL_SetAlpha(texture, 0, SDL_ALPHA_OPAQUE);

  SDL_SetColorKey(texture, SDL_SRCCOLORKEY, colorKey);

  // SDL_Surface* alphaSurface = SDL_DisplayFormatAlpha(texture);
  texture = SDL_DisplayFormatAlpha(texture);

  this->textureId = DRUID.loadTexture(texture, -1, format);
  this->enable();
  return this->isValidId();
}

void Texture::reload(void) {
  this->textureId = DRUID.loadTexture(texture, -1, format);
  this->enable();
}

void Texture::disable(void) {
  this->enabled = false;
  glDisable(GL_TEXTURE_2D);
}

void Texture::enable(void) {
  if (textureId > -1) {
    this->enabled = true;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId);
  }
}

bool Texture::isEnabled(void) { return this->enabled; }

int Texture::getId(void) { return this->textureId; }

void Texture::setId(int id) {
  if (id > -1) {
    this->textureId = id;
    this->enable();
  }
}

bool Texture::isValidId(void) { return (this->textureId > -1); }
