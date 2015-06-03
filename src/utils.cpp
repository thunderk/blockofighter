#include <stdlib.h>

void swapInt(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void swapFloat(float *a, float *b) {
  float temp = *a;
  *a = *b;
  *b = temp;
}

int random(int x) { return rand() * x / RAND_MAX; }

float randomf(float x) { return rand() * x / RAND_MAX; }

int smod(int val, int mod) {
  if (val >= 0)
    return val % mod;
  int temp = -val / mod + 1;
  return (val + temp * mod) % mod;
}

double sdes(double val) {
  if (val >= 0)
    return val - (int)(val);
  return val - (int)(val) + 1;
}

double sfmod(double val, double mod) {
  val -= (int)(val / mod) * mod;
  if (val < 0)
    val += mod;
  return val;
}
