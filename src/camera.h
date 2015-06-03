#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

class Camera {
private:
  float position[3];
  float target[3];
  float matrix[9];
  float *right, *up, *forward;

  void calculateMatrix(void);

public:
  Camera(void);

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
