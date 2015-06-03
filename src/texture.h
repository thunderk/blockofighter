#ifndef __TEXTURE_H_INCLUDED__
#define __TEXTURE_H_INCLUDED__

#include <SDL_image.h>
#include "main.h"
class Texture {

public:
  Texture(void);
  Texture(int id);
  ~Texture(void);

  bool loadImage(char *path);
  bool loadImage(char *path, float *trans);
  void enable(void);
  void disable(void);
  bool isEnabled(void);
  int getId(void);
  void setId(int id);
  bool isValidId(void);
  void reload(void);

  // int* getOGLTexture(void);
  // int* getModifiableOGLTexture(void);

private:
  int textureId;
  // int* modTexture;
  bool enabled;

  SDL_Surface *texture;
  int format;
};

#endif
