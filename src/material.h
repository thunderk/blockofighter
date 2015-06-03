#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

#include <SDL_image.h>
#include "texture.h"

class Material {
private:
  Texture *texture;
  float color[4];
  bool enabled;

public:
  Material(void);
  bool loadTexture(char *path);
  void freeTexture(void);

  void setColor(float red, float green, float blue, float alpha);
  const float *getColor(void);
  void enable(void);
  void disable(void);
  bool isEnabled(void);
  Texture *getTexture(void);
  void setTexture(Texture *tex);
};

#endif
