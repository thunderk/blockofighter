/*
 * $Id: light.h,v 1.5 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: light.h,v $
 * Revision 1.5  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.4  2002/07/15 20:32:35  msell
 * Uudet valot ja ulkoasun parantelua
 *
 * Revision 1.3  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.2  2002/06/03 23:20:43  msell
 * no message
 *
 * Revision 1.1  2002/05/18 12:29:35  msell
 * Valot ja ‰‰nij‰rjestelm‰n parantelua
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __LIGHT_H_INCLUDED__
#define __LIGHT_H_INCLUDED__

class Light{
private:
	float position[4];
	float diffuse[4];
	float specular[4];
	float attenuation[3];
	bool enabled;
	int glnum;

public:
	//Creates DISABLED light
	Light(void);

	void setPosition(float x, float y, float z);
	void setDirection(float x, float y, float z);
	void setColor(float red, float green, float blue);
	void setSpecular(float red, float green, float blue);
	void setAttenuation(float constant, float linear, float quadratic);
	void setEnabled(bool enabled);
	void glUpdate(void);
	void createFlare(void);
};

void updateLights(void);

#endif

