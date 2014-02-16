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
