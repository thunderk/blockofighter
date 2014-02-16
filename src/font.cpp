/*
 * $Id: font.cpp,v 1.6 2002/07/21 20:14:28 msell Exp $
 *
 *
 * $Log: font.cpp,v $
 * Revision 1.6  2002/07/21 20:14:28  msell
 * no message
 *
 * Revision 1.5  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.4  2002/07/19 14:05:52  msell
 * Damagetextuurit näkyy
 *
 * Revision 1.3  2002/07/19 12:10:53  msell
 * Hups
 *
 * Revision 1.2  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.1  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 *
 *
 * $Date: 2002/07/21 20:14:28 $
 *
 */

#include "main.h"

#include "font.h"
#include "glapi.h"

Texture *fonttexture;

void drawChar(float x, float y, char ch, float size){
	fonttexture->enable();

	int tx = (ch&15)*64;
	int ty = (ch>>4)*64;

	float w = size, h = size*4/3;

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

	glBegin(GL_QUADS);
		glTexCoord2f((tx)/1024.0, (ty)/1024.0);
		glVertex2f(x, y);

		glTexCoord2f((tx)/1024.0, (ty+64)/1024.0);
		glVertex2f(x, y+h);
		
		glTexCoord2f((tx+64)/1024.0, (ty+64)/1024.0);
		glVertex2f(x+w, y+h);
		
		glTexCoord2f((tx+64)/1024.0, (ty)/1024.0);
		glVertex2f(x+w, y);

	glEnd();

	fonttexture->disable();
}

float letterwidth[256] = {
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	0.5, 0.2, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.45, 0.2, 0.5,
	0.6, 0.5, 0.6, 0.6, 0.65, 0.65, 0.6, 0.65, 0.6, 0.6, 0.2, 1.0, 1.0, 1.0, 1.0, 0.5,
	1.0, 0.7, 0.6, 0.7, 0.7, 0.65, 0.6, 0.7, 0.8, 0.6, 0.7, 0.7, 0.6, 0.9, 0.85, 0.8,
	0.6, 0.9, 0.7, 0.7, 0.7, 0.7, 0.7, 1.0, 0.8, 0.7, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 0.6, 0.6, 0.6, 0.6, 0.6, 0.5, 0.6, 0.6, 0.2, 0.4, 0.6, 0.2, 0.8, 0.5, 0.55,
	0.55, 0.55, 0.5, 0.55, 0.55, 0.55, 0.6, 0.8, 0.6, 0.6, 0.6, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
};

void print(float x, float y, char *text, float size){
	int i;
	int textlength = strlen(text);
	float px = x;
	float py = y;
	for (i = 0; i < textlength; i++){
		char ch = text[i];
		if (ch == '\n'){
			px = x;
			py += size*1.2;
		} else{
			drawChar(px, py, ch, size);
			px += size*letterwidth[ch];
		}
	}
}


