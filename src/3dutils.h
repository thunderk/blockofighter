#ifndef __3DUTILS_H_INCLUDED__
#define __3DUTILS_H_INCLUDED__

#include "main.h"
#include "texture.h"

#define SKYFRONT DATAPATH "tback.png"
#define SKYBACK DATAPATH "tfront.png"
#define SKYLEFT DATAPATH "tleft.png"
#define SKYRIGHT DATAPATH "tright.png"
#define SKYTOP DATAPATH "ttop.png"
#define SKYBOTTOM DATAPATH "tbottom.png"

#define DAMAGEHEAD DATAPATH "damagehead.png"
#define DAMAGETORSO DATAPATH "damagetorso.png"
#define DAMAGEHAND DATAPATH "damagehand.png"
#define DAMAGELEG DATAPATH "damageleg.png"
#define FACE DATAPATH "perusnaama3.png"

extern int SKYBOX;

typedef struct { float x, y; } point2d;

typedef struct { float x, y, z; } point3d;

extern Texture *flaretexture;
extern Texture *skyfronttexture;
extern Texture *skybacktexture;
extern Texture *skylefttexture;
extern Texture *skyrighttexture;
extern Texture *skytoptexture;
extern Texture *skybottomtexture;
extern Texture *damageHead;
extern Texture *faceTexture;

void createLathedSurface(point2d *points, point2d *pointderivates, int count,
                         int slices, int stacks);
void createSphere(float r, int slices, int stacks);
void createSphere(float r);

float distanceFromPlane(float point[3], float normal[3], float distance);

void createSkyBox(float x, float y, float z, float w, float h, float l);

// MUST be called in pairs, enable pushes and disable pops
void enable2D(void);
void disable2D(void);

#endif
