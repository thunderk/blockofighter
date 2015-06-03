#ifndef __LEGOBLOCKS_H_INCLUDED__
#define __LEGOBLOCKS_H_INCLUDED__

//#include "mesh.h"
#include "object.h"
#include "material.h"
#include "mesh.h"

#define BLOCKHEIGHT 0.4

class BasicBlock : public MeshObject {
private:
  int width, height, depth;

public:
  BasicBlock(int width, int height, int depth);

  void setColor(float red, float green, float blue);
};

class BasicBlockAppearance : public Appearance {
private:
  int width, height, depth;
  int gllist;

protected:
  bool usematerial;

public:
  float displacement[3];

  BasicBlockAppearance(int width, int height, int depth);

  virtual void prepare(void);
  virtual void draw(void);
};

void drawDetailRectangle(float width, float height);

extern int knobgllist;
extern int knobdetail;
void initKnob(void);
void createKnob(int knobsegments = -1);

class HeadAppearance : public Appearance {
private:
  int gllist;

public:
  HeadAppearance(void);

  void prepare(void);
  void draw(void);
};

#define FLOWER_RED 1
#define FLOWER_YELLOW 2
#define FLOWER_WHITE 3

class FlowerAppearance : public Appearance {
private:
  int gllist;
  int color1, color2, color3;

public:
  FlowerAppearance(int color1, int color2, int color3);

  void prepare(void);
  void draw(void);
};

class LampAppearance : public Appearance {
private:
  int gllist;

public:
  LampAppearance(void);

  void prepare(void);
  void draw(void);
};

#endif
