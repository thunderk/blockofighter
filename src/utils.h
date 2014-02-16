/*
 * $Id: utils.h,v 1.6 2002/07/19 20:33:29 msell Exp $
 *
 *
 * $Log: utils.h,v $
 * Revision 1.6  2002/07/19 20:33:29  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.5  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.4  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.3  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.2  2002/06/03 23:06:38  msell
 * no message
 *
 * Revision 1.1  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 *
 *
 * $Date: 2002/07/19 20:33:29 $
 *
 */

#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__


#define PI 3.14159265358979323846

void swapInt(int *a, int *b);
void swapFloat(float *a, float *b);
int random(int x);
float randomf(float x);
int smod(int val, int mod);
double sdes(double val);
double sfmod(double val, double mod);

#endif

