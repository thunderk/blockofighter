#ifndef __RUN_H_INCLUDED__
#define __RUN_H_INCLUDED__

#define MENUMODE 1
#define FIGHTMODE 2
#define ENDMODE 3

void initScenes(void);
void changeGameMode(int newmode);
void calculateFrame(int framecount);
void drawFrame(int framecount);
void initTextures(void);
void setDetail(int detail);

#endif
