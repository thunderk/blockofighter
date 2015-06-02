#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef HAVE_TIME_H
#include <time.h>
#else
#include "SDL.h"
#endif

#include "fonct.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#undef MAX
#undef MIN
#undef SGN
#undef ABS
#undef CARRE
#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x < y) ? x : y)
#define SGN(x) ((x > 0) ? 1 : ((x == 0) ? 0 : -1))
#define ABS(x) ((x >= 0) ? x : -x)
#define CARRE(x) (x * x)

int iabs(int val) { return ABS(val); }

double carre(double x)
/*retourne x²*/
{
  return CARRE(x);
}

double dist2d(double x1, double y1, double x2, double y2)
/*calcule la distance entre (x1,y1) et (x2,y2)*/
{
  return sqrt(carre(x2 - x1) + carre(y2 - y1));
}

double dist3d(double x1, double y1, double z1, double x2, double y2, double z2)
/*calcule la distance entre (x1,y1) et (x2,y2)*/
{
  return sqrt(carre(x2 - x1) + carre(y2 - y1) + carre(z2 - z1));
}

double interpol_lin(double v00, double v10, double v01, double v11, double x,
                    double y)
/*effectue une interpolation linéaire entre les valeurs de 4 coins*/
{
  double a, b;

  a = v00 + (v01 - v00) * y;
  b = v10 + (v11 - v10) * y;
  return a + (b - a) * x;
}

int imax(int a, int b)
/*maximum de 2 entiers*/
{
  return MAX(a, b);
}

int imin(int a, int b)
/*minimum de 2 entiers*/
{
  return MIN(a, b);
}

float flmax(float a, float b)
/*maximum de 2 réels*/
{
  return MAX(a, b);
}

float flmin(float a, float b)
/*minimum de 2 réels*/
{
  return MIN(a, b);
}

double dmax(double a, double b)
/*maximum de 2 réels*/
{
  return MAX(a, b);
}

double dmin(double a, double b)
/*minimum de 2 réels*/
{
  return MIN(a, b);
}

/**************************************************************************/
/*effectue un range modulo mod à partir de base*/
/*la valeur finale se trouve dans [base..base+mod[ */
double modulo(double nb, double base, double mod) {
  float temp = nb;

  while (temp - base >= mod)
    temp -= mod;
  while (temp < base)
    temp += mod;
  return temp;
}

/*****************************************************************************/
/*angle fait par un point par rapport à l'angle de référence*/
double angle(double x, double y) {
  double nx, ny, d, ret;

  if (x == 0.0) {
    if (y == 0.0) {
      return 0.0;
    } else {
      return M_PI - (SGN(y) * M_PI / 2);
    }
  }

  d = dist2d(0.0, 0.0, x, y);
  nx = x / d;
  ny = y / d;

  ret = asin(ny);
  if (nx < 0.0) {
    ret = M_PI - ret;
  }
  return modulo(ret, 0.0, 2.0 * M_PI);
}

/***********************************************************************************/
/*convertit un entier en chaine formatée d'une certaine longueur completée par
 * des 0*/
void format0(int num, char *st, int nbchar) {
  int n = num;
  int i;

  for (i = 0; i < nbchar; i++) {
    st[i] = 48 + (int)((float)n / pow(10, nbchar - i - 1));
    n = n - (st[i] - 48) * (int)pow(10, nbchar - i - 1);
  }
}

/*******************************************************************************/
/*initialise au mieux le générateur de nombres aléatoires*/
void rnd_init() {
#ifdef HAVE_TIME_H
  srand((unsigned int)time(NULL));
#else
  int i;

  for (i = 0; i < 10000000; i++)
    ; /*pour grapiller des millisecondes aléatoires */
  srand((unsigned int)SDL_GetTicks());
#endif
}

/*******************************************************************************/
/*génère un entier aléatoire entre base et base+range-1 inclus*/
int rnd(int base, int range) {
  if (range == 0) {
    return base;
  }
  return base + (rand() % range);
}
