#ifndef __LIGHT_H_INCLUDED__
#define __LIGHT_H_INCLUDED__

#include "camera.h"

class Light {
private:
  float position[4];
  float diffuse[4];
  float specular[4];
  float attenuation[3];
  bool enabled;
  int glnum;

public:
  // Creates DISABLED light
  Light(void);

  void setPosition(float x, float y, float z);
  void setDirection(float x, float y, float z);
  void setColor(float red, float green, float blue);
  void setSpecular(float red, float green, float blue);
  void setAttenuation(float constant, float linear, float quadratic);
  void setEnabled(bool enabled);
  void glUpdate(void);
  void createFlare(Camera *camera);
};

void updateLights(void);

#endif
