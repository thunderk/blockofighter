/*
 * $Id: run.cpp,v 1.24 2002/07/22 11:44:16 jkaarlas Exp $
 *
 *
 * $Log: run.cpp,v $
 * Revision 1.24  2002/07/22 11:44:16  jkaarlas
 * naama
 *
 * Revision 1.23  2002/07/22 01:14:14  msell
 * Lopetussysteemi
 *
 * Revision 1.22  2002/07/19 22:38:38  msell
 * Pingviini
 *
 * Revision 1.21  2002/07/19 21:17:07  msell
 * bugifixi
 *
 * Revision 1.20  2002/07/19 20:06:32  msell
 * Linux-porttausta
 *
 * Revision 1.19  2002/07/19 19:46:07  msell
 * Makefile
 *
 * Revision 1.18  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.17  2002/07/19 14:05:52  msell
 * Damagetextuurit näkyy
 *
 * Revision 1.16  2002/07/19 12:48:57  jkaarlas
 * damagepää
 *
 * Revision 1.15  2002/07/19 12:42:44  msell
 * Loading...
 *
 * Revision 1.14  2002/07/17 20:32:48  msell
 * Detail-optio toimii
 *
 * Revision 1.13  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.12  2002/07/16 19:57:14  jkaarlas
 * lisätty DATAPATH tiedostonimien eteen
 *
 * Revision 1.11  2002/07/16 17:16:35  msell
 * Fontit ja valikot
 *
 * Revision 1.10  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.9  2002/06/17 20:49:05  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.8  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.7  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.6  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 * Revision 1.5  2002/05/18 12:29:35  msell
 * Valot ja äänijärjestelmän parantelua
 *
 * Revision 1.4  2002/05/17 12:30:26  msell
 * no message
 *
 * Revision 1.3  2002/05/16 18:41:16  msell
 * Vektorifunctioita ja kamera
 *
 * Revision 1.2  2002/05/15 21:07:23  msell
 * Äänisäätöä
 *
 * Revision 1.1  2002/05/15 14:36:39  msell
 * Yksinkertainen SDL-runko (Kääntyy toistaiseksi vain windowsissa).
 * Mukana myös musiikinsoitto fmodilla.
 *
 *
 *
 * $Date: 2002/07/22 11:44:16 $
 *
 */

#include "main.h"

#include <SDL.h>

#include "run.h"
#include "fight.h"
#include "menu.h"
#include "end.h"
#include "graphics.h"
#include "3dutils.h"
#include "audio.h"
#include "font.h"
#include "legoblocks.h"
#include "glapi.h"

int gamemode;

bool changed;

bool gameinitialized = false;

void initFontTexture(void);

void initScenes(void){
	knobgllist = glGenLists(1);
	setDetail(detail);

	
	//Simple loading-screen
	enable2D();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapBuffers();

	initFontTexture();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	print(0.08, 0.4, "Loading...", 0.2);
	SDL_GL_SwapBuffers();

	disable2D();



	SKYBOX = -1;
	initTextures();
	initFight();
	initMenu();
	initEnd();
	changeGameMode(MENUMODE);
	//changeGameMode(ENDMODE);
	gameinitialized = true;
}

void changeGameMode(int newmode){
	gamemode = newmode;
	changed = true;
}

void calculateFrame(int framecount){
	switch(gamemode){
		case MENUMODE:
			calculateMenu(framecount);
			break;
		case FIGHTMODE:
			calculateFight(framecount);
			break;
		case ENDMODE:
			calculateEnd(framecount);
			break;
	}
	updateAudio();
	changed = false;
}

void drawFrame(int framecount){
	if (changed) calculateFrame(framecount);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	
	switch(gamemode){
		case MENUMODE:
			drawMenu(framecount);
			break;
		case FIGHTMODE:
			drawFight(framecount);
			break;
		case ENDMODE:
			drawEnd(framecount);
			break;
	}

	SDL_GL_SwapBuffers();
}

/*int SKY_FRONT_ID;
int SKY_BACK_ID;
int SKY_LEFT_ID;
int SKY_RIGHT_ID;
int SKY_TOP_ID;
int SKY_BOTTOM_ID;*/

bool texturesloaded = false;

Texture *flaretexture;
Texture *skyfronttexture;
Texture *skybacktexture;
Texture *skylefttexture;
Texture *skyrighttexture;
Texture *skytoptexture;
Texture *skybottomtexture;
Texture *damageHead;
Texture *damageTorso;
Texture *damageHand;
Texture *damageLeg;
Texture *tuxtexture;
Texture *faceTexture;

void initFontTexture(void){
	if (!texturesloaded){
		float trans[3] = {1, 0, 0};
		fonttexture = new Texture();
		fonttexture->loadImage(DATAPATH"font.png", trans);
	} else{
		fonttexture->reload();
	}
}

void initTextures(void){
	/*SKY_FRONT_ID = DRUID.loadTexture(SKYFRONT);
	SKY_BACK_ID = DRUID.loadTexture(SKYBACK);
	SKY_LEFT_ID = DRUID.loadTexture(SKYLEFT);
	SKY_RIGHT_ID = DRUID.loadTexture(SKYRIGHT);
	SKY_TOP_ID = DRUID.loadTexture(SKYTOP);
	SKY_BOTTOM_ID = DRUID.loadTexture(SKYBOTTOM);*/

	if (!texturesloaded){
		skyfronttexture = new Texture();
		skyfronttexture->loadImage(SKYFRONT);
		skybacktexture = new Texture();
		skybacktexture->loadImage(SKYBACK);
		skylefttexture = new Texture();
		skylefttexture->loadImage(SKYLEFT);
		skyrighttexture = new Texture();
		skyrighttexture->loadImage(SKYRIGHT);
		skytoptexture = new Texture();
		skytoptexture->loadImage(SKYTOP);
		skybottomtexture = new Texture();
		skybottomtexture->loadImage(SKYBOTTOM);


		float something[3] = {1, 0, 0.5};
		damageHead = new Texture();
		damageHead->loadImage(DAMAGEHEAD, something);
		damageTorso = new Texture();
		damageTorso->loadImage(DAMAGETORSO, something);
		damageHand = new Texture();
		damageHand->loadImage(DAMAGEHAND, something);
		damageLeg = new Texture();
		damageLeg->loadImage(DAMAGELEG, something);
		faceTexture = new Texture();
		something[2] = 1;
		faceTexture->loadImage(FACE, something);

		float zeros[3] = {0, 0, 0};
		flaretexture = new Texture();
		flaretexture->loadImage(DATAPATH"flare.png", zeros);
		

		float pink[3] = {1, 0, 1};
		tuxtexture = new Texture();
		tuxtexture->loadImage(DATAPATH"tux.png", pink);
	} else{
		skyfronttexture->reload();
		skybacktexture->reload();
		skylefttexture->reload();
		skyrighttexture->reload();
		skytoptexture->reload();
		skybottomtexture->reload();

		damageHead->reload();
		damageTorso->reload();
		damageHand->reload();
		damageLeg->reload();

		flaretexture->reload();

		tuxtexture->reload();
	}
	texturesloaded = true;
}

void setDetail(int detail){
	switch(detail){
		case 0:
			knobdetail = 0;
			break;
		case 1:
			knobdetail = 5;
			break;
		case 2:
			knobdetail = 8;
			break;
		case 3:
			knobdetail = 16;
			break;
	}
	initKnob();
}


