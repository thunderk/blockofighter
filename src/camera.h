#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "object.h"

class Camera {
private:
  float position[3];
  float target[3];
  float matrix[9];
  float *right, *up, *forward;

  float positionang[3]; // position angulaire actuelle
  float optimalposition[3]; // position angulaire que doit atteindre la caméra
  // desc: {angh, dist, h}

  bool end; // controle si c'est une caméra placée pour la mort

  void calculateMatrix(void);

public:
  Camera(void);

  void setStart();

  void setAutoNormal(Object *obj1, Object *obj2, bool finish);
  void setAutoCastOut(Object *obj);
  void setAutoBeheaded(Object *head, float angle);
  void setAutoFallHead(Object *head, Object *torso);
  void setPosition(float position[3]);
  void setPosition(float x, float y, float z);
  void getPosition(float *position);
  void setTarget(float target[3]);
  void getTarget(float *target);
  void setUp(float up[3]);
  void getMatrix(float *matrix);

  void moveRight(float amount);
  void moveUp(float amount);
  void moveForward(float amount);

  void glUpdate(void);
};

#endif
