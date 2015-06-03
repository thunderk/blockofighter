#include <math.h>

#include "main.h"
#include "vector.h"
#include "utils.h"

void vectorSet(float *target, float x, float y, float z) {
  target[0] = x;
  target[1] = y;
  target[2] = z;
}

void vectorCopy(float *target, float *source) {
  target[0] = source[0];
  target[1] = source[1];
  target[2] = source[2];
}

void vectorAdd(float *target, float *source1, float *source2) {
  target[0] = source1[0] + source2[0];
  target[1] = source1[1] + source2[1];
  target[2] = source1[2] + source2[2];
}

void vectorAdd(float *target, float *source) {
  target[0] += source[0];
  target[1] += source[1];
  target[2] += source[2];
}

void vectorSub(float *target, float *source1, float *source2) {
  target[0] = source1[0] - source2[0];
  target[1] = source1[1] - source2[1];
  target[2] = source1[2] - source2[2];
}

void vectorSub(float *target, float *source) {
  target[0] -= source[0];
  target[1] -= source[1];
  target[2] -= source[2];
}

void vectorNegative(float *target, float *source) {
  target[0] = -source[0];
  target[1] = -source[1];
  target[2] = -source[2];
}

void vectorNegative(float *target) {
  target[0] = -target[0];
  target[1] = -target[1];
  target[2] = -target[2];
}

void vectorScale(float *target, float *source, float scale) {
  target[0] = source[0] * scale;
  target[1] = source[1] * scale;
  target[2] = source[2] * scale;
}

void vectorScale(float *target, float scale) {
  target[0] *= scale;
  target[1] *= scale;
  target[2] *= scale;
}

float vectorDot(float *source1, float *source2) {
  return source1[0] * source2[0] + source1[1] * source2[1] +
         source1[2] * source2[2];
}

float vectorNormalizedDot(float *source1, float *source2) {
  return vectorDot(source1, source2) /
         (vectorLength(source1) * vectorLength(source2));
}

float vectorLength(float *source) { return sqrtf(vectorDot(source, source)); }

void vectorCross(float *target, float *source1, float *source2) {
  target[0] = source1[1] * source2[2] - source1[2] * source2[1];
  target[1] = source1[2] * source2[0] - source1[0] * source2[2];
  target[2] = source1[0] * source2[1] - source1[1] * source2[0];
}

void vectorNormalize(float *target, float *source) {
  vectorScale(target, source, 1.0 / vectorLength(source));
}

void vectorNormalize(float *target) {
  vectorScale(target, 1.0 / vectorLength(target));
}

void vectorReflect(float *target, float *source, float *normal) {
  vectorCopy(target, normal);
  vectorScale(target, -vectorDot(source, normal) * 2);
  vectorAdd(target, source);
}

void vectorProject(float *target, float *source1, float *source2) {
  vectorScale(target, source2,
              vectorDot(source1, source2) / vectorDot(source2, source2));
}

bool vectorIsZero(float *vector) {
  if (vector[0] == 0 && vector[1] == 0 && vector[2] == 0)
    return true;
  // if (vectorDot(vector, vector) < 0.00001) return true;
  else
    return false;
}

void vectorSaturate(float *target, float *source, float min, float max) {
  float len = vectorLength(source);
  if (len < min) {
    len = min;
  } else if (len > max) {
    len = max;
  } else {
    if (target != source)
      vectorCopy(target, source);
    return;
  }
  vectorNormalize(target, source);
  vectorScale(target, len);
}

void vectorSaturate(float *vector, float min, float max) {
  vectorSaturate(vector, vector, min, max);
}

void vectorMatrixMultiply(float *target, float *source, float *matrix) {
  float source2[3];
  if (source == target) {
    vectorCopy(source2, source);
    source = source2;
  }
  int x;
  for (x = 0; x < 3; x++) {
    target[x] = source[0] * matrix[0 + x] + source[1] * matrix[3 + x] +
                source[2] * matrix[6 + x];
  }
}

void matrixSet(float *matrix, float x1, float y1, float z1, float x2, float y2,
               float z2, float x3, float y3, float z3) {
  matrix[0] = x1;
  matrix[1] = y1;
  matrix[2] = z1;
  matrix[3] = x2;
  matrix[4] = y2;
  matrix[5] = z2;
  matrix[6] = x3;
  matrix[7] = y3;
  matrix[8] = z3;
}

void matrixSet(float *matrix, float *r1, float *r2, float *r3) {
  vectorCopy(&matrix[0], r1);
  vectorCopy(&matrix[3], r2);
  vectorCopy(&matrix[6], r3);
}

void matrixCopy(float *target, float *source) {
  target[0] = source[0];
  target[1] = source[1];
  target[2] = source[2];
  target[3] = source[3];
  target[4] = source[4];
  target[5] = source[5];
  target[6] = source[6];
  target[7] = source[7];
  target[8] = source[8];
}

void matrixIdentity(float *matrix) {
  matrixSet(matrix, 1, 0, 0, 0, 1, 0, 0, 0, 1);
}

void matrixAdd(float *target, float *source1, float *source2) {
  target[0] = source1[0] + source2[0];
  target[1] = source1[1] + source2[1];
  target[2] = source1[2] + source2[2];
  target[3] = source1[3] + source2[3];
  target[4] = source1[4] + source2[4];
  target[5] = source1[5] + source2[5];
  target[6] = source1[6] + source2[6];
  target[7] = source1[7] + source2[7];
  target[8] = source1[8] + source2[8];
}

void matrixAdd(float *target, float *source) {
  target[0] += source[0];
  target[1] += source[1];
  target[2] += source[2];
  target[3] += source[3];
  target[4] += source[4];
  target[5] += source[5];
  target[6] += source[6];
  target[7] += source[7];
  target[8] += source[8];
}

void matrixMultiply(float *target, float *source1, float *source2) {
  float target2[9];
  float *oldtarget = target;
  bool copy = false;
  if (source1 == target || source2 == target) {
    copy = true;
    target = target2;
  }
  int x, y;
  for (y = 0; y < 3; y++) {
    for (x = 0; x < 3; x++) {
      *target = source1[y * 3 + 0] * source2[x] +
                source1[y * 3 + 1] * source2[3 + x] +
                source1[y * 3 + 2] * source2[6 + x];
      target++;
    }
  }
  if (copy) {
    matrixCopy(oldtarget, target2);
  }
}

/*void matrixMultiply(float *target, float *source){
    matrixMultiply(target, source, source);
}*/

/*void matrixRotate(float *matrix, float *vector){
    float rotmat[9];
    createRotationMatrix(rotmat, vector);
    matrixMultiply(matrix, matrix, rotmat);
}*/

void matrixCreateRotation(float *matrix, float *vector) {
  float angle = vectorLength(vector);
  float n[3];
  vectorNormalize(n, vector);

  float c = cos(angle);
  float s = sin(angle);
  float t = 1 - c;

  float x = n[0];
  float y = n[1];
  float z = n[2];

  matrixSet(matrix, t * x * x + c, t * y * x + s * z, t * z * x - s * y,
            t * x * y - s * z, t * y * y + c, t * z * y + s * x,
            t * x * z + s * y, t * y * z - s * x, t * z * z + c);
}

void matrixTranspose(float *target, float *source) {
  target[0] = source[0];
  target[1] = source[3];
  target[2] = source[6];
  target[3] = source[1];
  target[4] = source[4];
  target[5] = source[7];
  target[6] = source[2];
  target[7] = source[5];
  target[8] = source[8];
}

/*void rotatePointAroundVector(float *target, float *point, float *vector){
    float angle = vectorLength(vector);
    float n[3];
    vectorNormalize(n, vector);

    float c = cos(angle);
    float s = sin(angle);
    float t = 1 - c;

    //r' = r*c + n*(n . r)*t + (r x n)*s
}*/
