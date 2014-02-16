/*
 * $Id: 3dutils.h,v 1.22 2002/07/22 11:50:26 jkaarlas Exp $
 *
 *
 * $Log: 3dutils.h,v $
 * Revision 1.22  2002/07/22 11:50:26  jkaarlas
 * naama
 *
 * Revision 1.21  2002/07/22 11:44:16  jkaarlas
 * naama
 *
 * Revision 1.20  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.19  2002/07/19 18:59:46  msell
 * Alkuhommaa ja säätöä
 *
 * Revision 1.18  2002/07/19 14:05:51  msell
 * Damagetextuurit näkyy
 *
 * Revision 1.17  2002/07/19 12:28:29  msell
 * 2D-mode
 *
 * Revision 1.16  2002/07/17 20:32:47  msell
 * Detail-optio toimii
 *
 * Revision 1.15  2002/07/17 19:06:39  jkaarlas
 * skyboxin keskitys
 *
 * Revision 1.14  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.13  2002/07/16 17:16:34  msell
 * Fontit ja valikot
 *
 * Revision 1.12  2002/07/16 00:42:43  msell
 * Uusia skyboxeja ja areenan säätöä
 *
 * Revision 1.11  2002/07/15 22:03:22  msell
 * MultiAppearance
 *
 * Revision 1.10  2002/07/15 21:42:58  msell
 * Skybox-testi
 *
 * Revision 1.9  2002/07/15 15:22:07  msell
 * Parantelua
 *
 * Revision 1.8  2002/07/14 21:27:48  jkaarlas
 * uudet tekstuurit
 *
 * Revision 1.7  2002/07/14 21:22:40  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.6  2002/06/20 22:50:12  msell
 * Meshit
 *
 * Revision 1.5  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.4  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.3  2002/06/05 23:55:46  msell
 * Pallo
 *
 * Revision 1.2  2002/06/04 16:28:32  msell
 * #pragma once
 *
 * Revision 1.1  2002/06/03 23:06:38  msell
 * no message
 *
 *
 *
 * $Date: 2002/07/22 11:50:26 $
 *
 */

#ifndef __3DUTILS_H_INCLUDED__
#define __3DUTILS_H_INCLUDED__

#include "main.h"
#include "texture.h"



#define SKYFRONT  DATAPATH"tback.png"
#define SKYBACK   DATAPATH"tfront.png"
#define SKYLEFT   DATAPATH"tleft.png"
#define SKYRIGHT  DATAPATH"tright.png"
#define SKYTOP    DATAPATH"ttop.png"
#define SKYBOTTOM DATAPATH"tbottom.png"


#define DAMAGEHEAD DATAPATH"damagehead.png"
#define DAMAGETORSO DATAPATH"damagetorso.png"
#define DAMAGEHAND DATAPATH"damagehand.png"
#define DAMAGELEG DATAPATH"damageleg.png"
#define FACE DATAPATH"perusnaama3.png"

extern int SKYBOX;

typedef struct{
	float x,y;
} point2d;

typedef struct{
	float x,y,z;
} point3d;

extern Texture *flaretexture;
extern Texture *skyfronttexture;
extern Texture *skybacktexture;
extern Texture *skylefttexture;
extern Texture *skyrighttexture;
extern Texture *skytoptexture;
extern Texture *skybottomtexture;
extern Texture *damageHead;
extern Texture *faceTexture;

void createLathedSurface(point2d *points, point2d *pointderivates, int count, int slices, int stacks);
void createSphere(float r, int slices, int stacks);
void createSphere(float r);

float distanceFromPlane(float point[3], float normal[3], float distance);

void createSkyBox(float x, float y, float z, float w, float h, float l);


//MUST be called in pairs, enable pushes and disable pops
void enable2D(void);
void disable2D(void);

#endif

