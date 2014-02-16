/*
 * $Id: material.cpp,v 1.10 2002/07/19 20:40:44 msell Exp $
 *
 *
 * $Log: material.cpp,v $
 * Revision 1.10  2002/07/19 20:40:44  msell
 * Linux-porttausta
 *
 * Revision 1.9  2002/07/10 22:22:04  jkaarlas
 * getColor
 *
 * Revision 1.8  2002/06/27 21:43:29  jkaarlas
 * lisätty setTexture-funktio
 *
 * Revision 1.7  2002/06/27 00:08:04  msell
 * Kimmotukset palloille myös pyöritettyihin mesheihin
 *
 * Revision 1.6  2002/06/20 00:21:01  jkaarlas
 * materiaali- ja tekstuurihommia edistetty
 *
 * Revision 1.5  2002/06/19 22:45:29  jkaarlas
 * nyt nämä menee järkevästi
 *
 * Revision 1.4  2002/06/17 20:49:05  msell
 * free -> SDL_FreeSurface
 *
 * Revision 1.3  2002/06/16 01:04:58  jkaarlas
 * tulipa säädettyä includejen kanssa. oon tod.näk. eri mieltä aamulla
 *
 * Revision 1.2  2002/06/03 23:06:38  msell
 * no message
 *
 *
 *
 * $Date: 2002/07/19 20:40:44 $
 *
 */

#include "main.h"

#include "material.h"
#include "glapi.h"
#include "graphics.h"

Material::Material(void){
	setColor(1, 1, 1, 1);
  this->texture = new Texture;
}

bool Material::loadTexture(char *path){
  if (!this->texture){
    this->texture = new Texture;
  }
  if (this->texture->loadImage(path)){
    setColor(1, 1, 1, 1);
    return true;
  }
  return false;
}

void Material::freeTexture(void){
  this->texture->~Texture();
}

void Material::setColor(float red, float green, float blue, float alpha){
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
}

const float* Material::getColor(void){
	return color;
}

void Material::enable(void){
  enabled = true;
	glColor4fv(color);
  this->texture->enable();
}

void Material::disable(void){
  enabled = false;
  this->texture->disable();
}

bool Material::isEnabled(void){
  return enabled;
}

Texture* Material::getTexture(void){
  return this->texture;
}

void Material::setTexture(Texture* tex){
  //this->texture->~Texture;
  this->texture = tex;
}
