/*
 * $Id: utils.cpp,v 1.3 2002/07/14 21:40:43 msell Exp $
 *
 *
 * $Log: utils.cpp,v $
 * Revision 1.3  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.2  2002/06/14 00:05:05  msell
 * Törmäyssimulaatio kunnossa toivon mukaan
 *
 * Revision 1.1  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 *
 *
 * $Date: 2002/07/14 21:40:43 $
 *
 */

#include <stdlib.h>

void swapInt(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swapFloat(float *a, float *b){
	float temp = *a;
	*a = *b;
	*b = temp;
}

int random(int x){
	return rand() * x / RAND_MAX;
}

float randomf(float x){
	return rand() * x / RAND_MAX;
}

int smod(int val, int mod){
	if (val>=0) return val%mod;
	int temp=-val/mod+1;
	return (val+temp*mod)%mod;
}

double sdes(double val){
	if (val>=0) return val-(int)(val);
	return val-(int)(val)+1;
}

double sfmod(double val, double mod){
	val-=(int)(val/mod)*mod;
	if (val<0) val+=mod;
	return val;
}

