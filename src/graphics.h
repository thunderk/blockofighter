#ifndef __GRAPHICS_H_INCLUDED__
#define __GRAPHICS_H_INCLUDED__

#ifdef WIN32
#pragma warning(disable : 4700)
#endif

#include "main.h"
#include "texture.h"
#include "glapi.h"

const int ID_ARRAY_INIT_SIZE = 16;
const int ID_ARRAY_GROW = 8;

#define DRUID GraphicsDruid::getInstance()
#define DIE_DRUID_DIE GraphicsDruid::destroy()
typedef unsigned char byte;
typedef struct jpeg_pixel {
  Uint8 red;
  Uint8 green;
  Uint8 blue;
} jpeg_pixel;

class GraphicsDruid {

private:
  static GraphicsDruid *instance;
  int *idArray;
  int textureCount;
  int reserved;

  GraphicsDruid(void);
  ~GraphicsDruid(void);

  static void init(void);
  static void destroy(void);

public:
  static GraphicsDruid &getInstance(void);
  int loadTexture(SDL_Surface *texture, int id = -1, int format = GL_RGB);
  int loadTexture(char *path, int id = -1);
  int loadTranspTexture(char *path, float *transpColor, int id = -1);
  void freeTexture(int id);
  void freeAll(void);
  int getNewTextureID(int id);
};

#endif
