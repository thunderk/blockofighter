#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#undef MAX
#undef MIN
#undef SGN
#undef ABS
#undef CARRE
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define SGN(x) (((x) > 0) ? 1 : (((x) == 0) ? 0 : -1))
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define CARRE(x) ((x) * (x))

#define RAD2DEG(x) ((unsigned int)((x)*180 / M_PI))
#define DEG2RAD(x) ((double)(x)*M_PI / 180.0)

/*retourne la valeur absolue entière de val*/
int iabs(int val);

double carre(double x);

/*retourne x²*/

double dist2d(double x1, double y1, double x2, double y2);

/*calcule la distance entre (x1,y1) et (x2,y2)*/

double dist3d(double x1, double y1, double z1, double x2, double y2, double z2);
/*calcule la distance entre (x1,y1) et (x2,y2)*/

double interpol_lin(double v00, double v10, double v01, double v11, double x,
                    double y);
/*effectue une interpolation linéaire entre les valeurs de 4 coins*/

int imax(int a, int b);

/*maximum de 2 entiers*/

int imin(int a, int b);

/*minimum de 2 entiers*/

float flmax(float a, float b);

/*maximum de 2 réels*/

float flmin(float a, float b);

/*minimum de 2 réels*/

double dmax(double a, double b);

/*maximum de 2 réels*/

double dmin(double a, double b);

/*minimum de 2 réels*/

/*effectue un range modulo mod à partir de base*/
/*la valeur finale se trouve dans [base..base+mod[ */
double modulo(double nb, double base, double mod);

/*angle fait par un point par rapport à l'angle de référence*/
double angle(double x, double y);

/*convertit un entier en chaine formatée d'une certaine longueur completée par
 * des 0*/
void format0(int num, char *st, int nbchar);

/*initialise au mieux le générateur de nombres aléatoires*/
void rnd_init();

/*génère un nombre aléatoire entre base et base+range*/
int rnd(int base, int range);
