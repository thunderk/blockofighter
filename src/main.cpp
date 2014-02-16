/*
 * $Id: main.cpp,v 1.30 2002/07/21 15:03:12 msell Exp $
 *
 *
 * $Log: main.cpp,v $
 * Revision 1.30  2002/07/21 15:03:12  msell
 * Äänet disabloitu
 *
 * Revision 1.29  2002/07/19 20:39:31  msell
 * Linux-porttausta
 *
 * Revision 1.28  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.27  2002/07/19 20:06:32  msell
 * Linux-porttausta
 *
 * Revision 1.26  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.25  2002/07/19 12:42:44  msell
 * Loading...
 *
 * Revision 1.24  2002/07/19 12:28:29  msell
 * 2D-mode
 *
 * Revision 1.23  2002/07/18 23:05:31  msell
 * Partikkelit ja kakkospelaajan liike
 *
 * Revision 1.22  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.21  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 * Revision 1.20  2002/07/14 21:40:43  msell
 * Conflictit pois, liikkumiset (hyppy, kävely, lyönti), uusi areena
 *
 * Revision 1.19  2002/07/14 21:22:39  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.18  2002/07/11 18:33:30  jkaarlas
 * turhat äänet pois
 *
 * Revision 1.17  2002/07/08 22:53:38  msell
 * Säätöä
 *
 * Revision 1.16  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.15  2002/06/20 22:50:12  msell
 * Meshit
 *
 * Revision 1.14  2002/06/17 20:49:05  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.13  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.12  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.11  2002/06/15 22:56:37  msell
 * Säätöä
 *
 * Revision 1.10  2002/06/11 23:11:45  msell
 * Törmäystarkistusta
 *
 * Revision 1.9  2002/06/07 21:16:51  msell
 * Fysiikkaenginen alkua
 *
 * Revision 1.8  2002/06/02 16:57:37  msell
 * Objektirakenteen pohja
 *
 * Revision 1.7  2002/05/19 13:40:19  msell
 * Säätöä
 *
 * Revision 1.6  2002/05/18 12:29:35  msell
 * Valot ja äänijärjestelmän parantelua
 *
 * Revision 1.5  2002/05/17 23:13:30  msell
 * Valot
 *
 * Revision 1.4  2002/05/16 18:41:16  msell
 * Vektorifunctioita ja kamera
 *
 * Revision 1.3  2002/05/15 21:07:23  msell
 * Äänisäätöä
 *
 * Revision 1.2  2002/05/15 15:21:00  msell
 * Äänisäätöä
 *
 * Revision 1.1  2002/05/15 14:36:39  msell
 * Yksinkertainen SDL-runko (Kääntyy toistaiseksi vain windowsissa).
 * Mukana myös musiikinsoitto fmodilla.
 *
 *
 *
 * $Date: 2002/07/21 15:03:12 $
 *
 */

#include "main.h"

#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif

#include "audio.h"
#include "run.h"
#include "texture.h"
#include "fight.h"
#include "font.h"
#include "3dutils.h"

#include "glapi.h"

int screenwidth=1024;
int screenheight=768;
int screenbpp;

void exitProgram(int code){
	SDL_Quit();
	//uninitAudio();
	exit(code);
}

void changeResolution(int width, int height, bool fullscreen){
	int mode = SDL_OPENGL;
	if (fullscreen) mode |= SDL_FULLSCREEN;
	if (!SDL_SetVideoMode(width, height, screenbpp, mode)){
		fprintf(stderr,"Couldn't set %i*%i*%i opengl video mode: %s\n",screenwidth,screenheight,screenbpp,SDL_GetError());
		exitProgram(-1);
	}

	setupOpengl(width, height);

	screenwidth = width;
	screenheight = height;

	if (fullscreen) SDL_ShowCursor(SDL_DISABLE);
	else SDL_ShowCursor(SDL_ENABLE);
	
	initScenes();
}


bool keys[SDLK_LAST] = {false};

void handleKeydown(SDL_keysym *keysym){
	keys[keysym->sym] = true;
}


void handleKeyup(SDL_keysym *keysym){
	keys[keysym->sym] = false;
}

void processEvents(void){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		switch (event.type){
		case SDL_KEYDOWN:
			handleKeydown(&event.key.keysym);
			break;
		case SDL_KEYUP:
			handleKeyup(&event.key.keysym);
			break;
		case SDL_VIDEORESIZE:
			screenwidth=event.resize.w;
			screenheight=event.resize.h;
			setupOpengl(screenwidth,screenheight);
			break;
		case SDL_QUIT:
			exitProgram(0);
			break;
		}
	}
}

int getTime(void){
#ifdef WIN32
	return timeGetTime();
#else
	return SDL_GetTicks();
#endif
}

int main(int argc, char *argv[]){
	//printf("Initializing SDL.\n");

	if ((SDL_Init(SDL_INIT_VIDEO)==-1)){
		printf("Could not initialize SDL: %s.\n",SDL_GetError());
		exitProgram(-1);
	}

	const SDL_VideoInfo *info=SDL_GetVideoInfo();
	if (!info){
		printf("Could not get video info with SDL: %s.\n",SDL_GetError());
		exitProgram(-1);
	}
	screenbpp=info->vfmt->BitsPerPixel;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	atexit(SDL_Quit);

	SDL_WM_SetCaption("BlockoFighter 2",NULL);

	initAudio();

	changeResolution(screenwidth, screenheight, false);

	//printf("SDL initialized.\n");



	double calculatefps = 200.0;
	int framecounter, oldframecounter = 0;
	int currenttime;
	int framesdrawn=0;
	int skipframes;
	int starttime = getTime();

	while (1){
		do{
			currenttime = getTime()-starttime;
			framecounter = calculatefps*currenttime/1000.0;
		}	while (oldframecounter == framecounter);
		skipframes = framecounter - oldframecounter;
		for (; skipframes > 0; skipframes--){
			calculateFrame(++oldframecounter);
		}
		//calculateFrame(oldframecounter++);
		processEvents();
		drawFrame(framecounter);
		framesdrawn++;
	}
	return 0;
}