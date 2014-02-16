/*
 * $Id: graphics.cpp,v 1.17 2002/07/21 15:03:12 msell Exp $
 *
 *
 * $Log: graphics.cpp,v $
 * Revision 1.17  2002/07/21 15:03:12  msell
 * Äänet disabloitu
 *
 * Revision 1.16  2002/07/19 22:01:35  msell
 * Säätöä
 *
 * Revision 1.15  2002/07/19 21:32:54  msell
 * Mipmap pois
 *
 * Revision 1.14  2002/07/19 21:17:06  msell
 * bugifixi
 *
 * Revision 1.13  2002/07/17 16:40:33  msell
 * Resoluution vaihto
 *
 * Revision 1.12  2002/07/14 21:22:39  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.11  2002/06/28 14:51:40  jkaarlas
 * transparenttilatausta korjailtu
 *
 * Revision 1.10  2002/06/27 21:42:32  jkaarlas
 * lisätty transparentin tekstuurin lataus
 *
 * Revision 1.9  2002/06/26 18:54:43  jkaarlas
 * Nyt se lataus vihdoin toimii
 *
 * Revision 1.8  2002/06/20 15:30:22  jkaarlas
 * tekstuurisäätöä
 *
 * Revision 1.7  2002/06/19 22:44:56  jkaarlas
 * lisätty glTexEnvf lataukseen
 *
 * Revision 1.6  2002/06/17 20:49:04  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.5  2002/06/17 20:24:20  jkaarlas
 * pahimmat bugit korjattu
 *
 * Revision 1.4  2002/06/17 19:58:08  msell
 * #includeiden parantelua
 *
 * Revision 1.3  2002/06/17 16:51:38  jkaarlas
 * realloc korjattu
 *
 * Revision 1.2  2002/06/16 01:05:18  jkaarlas
 * vähän lihaa luiden ympärille näihinkin
 *
 * 
 *
 * $Date: 2002/07/21 15:03:12 $
 *
 */

#include "graphics.h"
#include <stdlib.h>

GraphicsDruid *GraphicsDruid::instance = 0;

GraphicsDruid::GraphicsDruid(void){
  this->reserved = 0;
}

GraphicsDruid::~GraphicsDruid(void){
}

void GraphicsDruid::init(void){
  instance->textureCount = 0;
  instance->reserved = ID_ARRAY_INIT_SIZE;
  instance->idArray = (int*) calloc(ID_ARRAY_INIT_SIZE, sizeof(int));

  for (int i=0; i < instance->reserved; i++){
    instance->idArray[i] = -1;
  }
}

void GraphicsDruid::destroy(void){
  if (instance->textureCount > 0){
    glDeleteTextures(GL_TEXTURE_2D, (const unsigned int*)instance->idArray);
  }
  free(instance->idArray);
  instance->idArray = 0;
  delete instance;
  instance = 0;
}

GraphicsDruid &GraphicsDruid::getInstance(void){
  
  if (!instance){
    instance = new GraphicsDruid;
    init();
  }
  return *instance;
}

int GraphicsDruid::loadTexture(SDL_Surface *texture, int id, int format){

  int textureID = id == -1 ? getNewTextureID(id) : id;
  
	// register texture in OpenGL
	glBindTexture (GL_TEXTURE_2D, textureID);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//_MIPMAP_NEAREST);
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   
	//printf("w: %i, h: %i, format: %i, RGBA: %i, pixels: %p\n",
	//	texture->w, texture->h, format, GL_RGBA, texture->pixels);
	//printf("Pitch: %i, Bpp: %i\n", texture->pitch, texture->format->BytesPerPixel);

  /*gluBuild2DMipmaps(GL_TEXTURE_2D,
                    4, 
                    texture->w, 
                    texture->h,
					          format,
					          GL_UNSIGNED_BYTE,
					          texture->pixels);*/
	int w = texture->w;
	int h = texture->h;
	/*int i;
	while (w > 0){
		w >>= 1;
		i++;
	}
	w = 1;
	for (;i > 1; i--) w <<= 1;
	while (h > 0){
		h >>= 1;
		i++;
	}
	h = 1;
	for (;i > 1; i--) h <<= 1;*/
	//glTexImage2D(GL_TEXTURE_2D, 0, texture->format->BytesPerPixel, w, h, 0, format, GL_UNSIGNED_BYTE, texture->pixels);
  if (texture->format->BytesPerPixel == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);
	} else if (texture->format->BytesPerPixel == 4){
		glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
	}
  //SDL_FreeSurface(texture);
  //SDL_FreeSurface(alphaSurface);
  return textureID;
}

int GraphicsDruid::loadTexture(char* path, int id){
  
  SDL_Surface* texture;
  texture = IMG_Load(path);

  if (!texture){
#ifdef _DEBUG
    printf ("Error while loading image: %s\n", SDL_GetError());
#endif
    return -1;
  }
  int textureID = getNewTextureID(id);
  

	// register texture in OpenGL
	glBindTexture (GL_TEXTURE_2D, textureID);

  //glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// NOTE : Making some assumptions about texture parameters
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//printf("w: %i, h: %i, RGBA: %i, pixels: %p\n",
	//	texture->w, texture->h, GL_RGBA, texture->pixels);
	//printf("Pitch: %i, Bpp: %i\n", texture->pitch, texture->format->BytesPerPixel);

  if (texture->format->BytesPerPixel == 3){
    /*gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
                 texture->w,
                 texture->h,
		              GL_RGB, GL_UNSIGNED_BYTE,
		             texture->pixels);*/
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->w, texture->h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);
	}
	else if (texture->format->BytesPerPixel == 4){
		/*gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,
		            texture->w,
		            texture->h,
		             GL_RGBA, GL_UNSIGNED_BYTE,
		            texture->pixels);*/
		glTexImage2D(GL_TEXTURE_2D, 0, 4, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
	}

/*
  
  
	gluBuild2DMipmaps(GL_TEXTURE_2D,
                      0, 
                      texture->w, 
                      texture->h,
					  GL_RGBA,
					  GL_UNSIGNED_BYTE,
					  texture->pixels);
  */
  SDL_FreeSurface(texture);
	return textureID;
}

int GraphicsDruid::loadTranspTexture(char* path, float* transpColor, int id){
  
   SDL_Surface* texture;
  texture = IMG_Load(path);
  if (!texture){
#ifdef _DEBUG
    printf ("Error while loading image: %s\n", SDL_GetError());
#endif
    return -1;
  }
    
  
  Uint32 colorKey = SDL_MapRGB(texture->format, 
                                (Uint8)(transpColor[0] * 255), 
                                (Uint8)(transpColor[1] * 255), 
                                (Uint8)(transpColor[2] * 255));
  //SDL_SetAlpha(texture, 0, SDL_ALPHA_OPAQUE);

  SDL_SetColorKey(texture, SDL_SRCCOLORKEY, colorKey);
      
  //SDL_Surface* alphaSurface = SDL_DisplayFormatAlpha(texture);
  texture = SDL_DisplayFormatAlpha(texture);

	return loadTexture(texture);
}

int GraphicsDruid::getNewTextureID(int id){

	if (id != -1){
		for (int i = 0; i < instance->reserved; i++){
			if (instance->idArray[i] == id){
				freeTexture(id);
				instance->textureCount--;
				break;
			}
		}
	}

	GLuint newId;

	if (id == -1){
		glGenTextures (1, &newId);
	}
	else
		newId = id;
	
	int index = 0;
  while (instance->idArray[index] != -1 && index < instance->reserved){
		index++;
  }

	// out of space, make more
	if (index >= instance->reserved){
		instance->idArray = (int*) realloc(instance->idArray, (instance->reserved + ID_ARRAY_GROW)*sizeof(int));
    
		for (int i = instance->reserved + 1; i < instance->reserved + ID_ARRAY_GROW; i++)
			instance->idArray[i] = -1;

		instance->reserved += ID_ARRAY_GROW;
	}
	else
		instance->idArray[index] = newId;

	
	instance->textureCount++;
	return newId;
}

void GraphicsDruid::freeTexture(int id){
  if (id > -1 && id < instance->reserved){
    instance->idArray[id] = -1;
    const unsigned int helpInt = id;
    glDeleteTextures(1,  &helpInt);
  }
}

