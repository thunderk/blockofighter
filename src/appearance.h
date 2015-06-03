#ifndef __APPEARANCE_H_INCLUDED__
#define __APPEARANCE_H_INCLUDED__

#include "main.h"

#include "material.h"

/*
 * Abstract class for drawing objects
 */
class Appearance {
private:
public:
  Material material;

  Appearance(void);

  Material *getMaterial(void);
  void setMaterial(Material mat);

  virtual void prepare(void);
  virtual void draw(void) = 0;
};

struct appearancelist {
  Appearance *data;
  appearancelist *next;
};

class MultiAppearance : public Appearance {
private:
  appearancelist *appearances;

public:
  MultiAppearance(void);
  void addAppearance(Appearance *appearance);

  void prepare(void);
  void draw(void);
};

#endif
