#include "main.h"

#include "camera.h"
#include "vector.h"
#include "glapi.h"
#include "fight.h"
#include "fonct.h"

Camera::Camera(void) {
  right = &matrix[0];
  up = &matrix[3];
  forward = &matrix[6];

  // vectorSet(position, 0, 2, 2);
  // vectorSet(target, 0, 0, 0);
  vectorSet(up, 0, 1, 0);

  // vectorSet(positionang, 0, 5, 20);
  this->setStart();

  calculateMatrix();
}

void Camera::setStart() {
  vectorSet(position, 0, 2, 2);
  vectorSet(target, -2, 10, 0); // hum...cela affecte la lumière du menu

  vectorSet(positionang, 3.0 * M_PI / 2.0, 8.0, 5.0);

  this->end = false;
}

void Camera::setAutoNormal(Object *obj1, Object *obj2, bool finish) {
  float diff[3];
  float dist = flmax(fabs(this->position[0]), fabs(this->position[2]));

  vectorSub(diff, obj1->position, obj2->position);

  this->target[0] = (obj1->position[0] + obj2->position[0]) / 2.0;
  this->target[1] = (obj1->position[1] + obj2->position[1]) / 2.0;
  this->target[2] = (obj1->position[2] + obj2->position[2]) / 2.0;

  this->optimalposition[0] = angle(diff[0], diff[2]) + M_PI / 2.0;
  this->optimalposition[1] = flmin(flmax(vectorLength(diff) * 4.0, 5.0), 20.0);
  if (this->target[1] > 8.0) {
    this->optimalposition[1] *= 2.0;
    this->optimalposition[2] = this->target[1] + 5.0;
  } else {
    if (dist < ARENASIZE * 0.8) {
      this->optimalposition[2] = 5.0;
    } else {
      this->optimalposition[2] = dist;
    }
  }

  if (finish) {
    this->positionang[0] = this->optimalposition[0];
    this->positionang[1] = this->optimalposition[1] / 2.0;
  } else {
    this->positionang[0] +=
        modulo(this->optimalposition[0] - this->positionang[0], -M_PI,
               2 * M_PI) /
        250.0;
    this->positionang[1] +=
        (this->optimalposition[1] - this->positionang[1]) / 500.0;
  }
  this->positionang[2] +=
      (this->optimalposition[2] - this->positionang[2]) / 100.0;

  this->position[0] =
      this->target[0] + cos(this->positionang[0]) * this->positionang[1];
  this->position[1] = this->positionang[2];
  this->position[2] =
      this->target[2] + sin(this->positionang[0]) * this->positionang[1];
}

void Camera::setAutoCastOut(Object *obj) {
  if ((obj->position[0] > ARENASIZE) || (obj->position[2] > ARENASIZE)) {
    if (!end) {
      this->position[0] = 5.0 + ARENASIZE;
      this->position[2] = 5.0 + ARENASIZE;
    }
    if (obj->position[0] + 1.0 > this->position[0]) {
      this->position[0] += 0.1;
    }
    if (obj->position[2] + 1.0 > this->position[2]) {
      this->position[2] += 0.1;
    }
  } else {
    if (!end) {
      this->position[0] = -5.0 - ARENASIZE;
      this->position[2] = -5.0 - ARENASIZE;
    }
    if (obj->position[0] - 1.0 < this->position[0]) {
      this->position[0] -= 0.1;
    }
    if (obj->position[2] - 1.0 < this->position[2]) {
      this->position[2] -= 0.1;
    }
  }

  // this->position[1] = -10.0 - obj->position[1] / 2.0;
  this->position[1] = obj->position[1] / 2.0 + 10.0;
  // this->position[1] = 5.0;

  this->target[0] = obj->position[0] * 0.7;
  this->target[1] = obj->position[1];
  this->target[2] = obj->position[2] * 0.7;
  // this->target[1] = -5.0;
  this->end = true;
}

void Camera::setAutoBeheaded(Object *head, float angle) {
  this->target[0] = head->position[0];
  this->target[1] = head->position[1];
  this->target[2] = head->position[2];

  this->position[0] = this->target[0] + 5.0 * cos(angle);
  this->position[2] = this->target[2] + 5.0 * sin(angle);

  this->position[1] = ARENAHEIGHT / 2.0 + 1.0 + cos(angle);
  ;
}

void Camera::setAutoFallHead(Object *head, Object *torso) {
  float angh, d;

  angh = angle(torso->position[0] - head->position[0],
               torso->position[2] - head->position[2]);
  d = dist3d(head->position[0], head->position[1], head->position[2],
             torso->position[0], torso->position[1], torso->position[2]);
  d = MIN(d, 25.0);
  angh += (25.0 - d) * M_PI / 25.0 - M_PI_2;
  d = MAX(d, 10.0);

  this->target[0] = head->position[0];
  this->target[1] =
      head->position[1] + (torso->position[1] - head->position[1]) / 2.0;
  this->target[2] = head->position[2];
  this->position[0] = torso->position[0] + d * cos(angh);
  this->position[1] = d / 2.0 + 3.0;
  this->position[2] = torso->position[2] + d * sin(angh);
}

void Camera::setPosition(float position[3]) {
  vectorCopy(this->position, position);
}

void Camera::setPosition(float x, float y, float z) {
  this->position[0] = x;
  this->position[1] = y;
  this->position[2] = z;
}

void Camera::getPosition(float *position) {
  vectorCopy(position, this->position);
}

void Camera::setTarget(float target[3]) { vectorCopy(this->target, target); }

void Camera::getTarget(float *target) { vectorCopy(target, this->target); }

void Camera::setUp(float up[3]) { vectorCopy(this->up, up); }

void Camera::getMatrix(float *matrix) {
  vectorCopy(&matrix[0], &this->matrix[0]);
  vectorCopy(&matrix[3], &this->matrix[3]);
  vectorCopy(&matrix[6], &this->matrix[6]);
}

void Camera::moveRight(float amount) {
  float movevector[3];
  vectorScale(movevector, right, amount);
  vectorAdd(position, movevector);
  // vectorAdd(target, movevector);
  calculateMatrix();
}

void Camera::moveUp(float amount) {
  float movevector[3];
  vectorScale(movevector, up, amount);
  vectorAdd(position, movevector);
  // vectorAdd(target, movevector);
  calculateMatrix();
}

void Camera::moveForward(float amount) {
  float movevector[3];
  vectorScale(movevector, forward, amount);
  vectorAdd(position, movevector);
  // vectorAdd(target, movevector);
  calculateMatrix();
}

void Camera::glUpdate(void) {
  // glLoadIdentity();

  gluLookAt(position[0], position[1], position[2], target[0], target[1],
            target[2], up[0], up[1], up[2]);
}

void Camera::calculateMatrix(void) {
  vectorSub(forward, target, position);
  vectorNormalize(forward);
  vectorCross(right, forward, up);
}
