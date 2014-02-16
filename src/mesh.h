/*
 * $Id: mesh.h,v 1.12 2002/07/19 20:33:28 msell Exp $
 *
 *
 * $Log: mesh.h,v $
 * Revision 1.12  2002/07/19 20:33:28  msell
 * #pragma once -> #ifndef
 *
 * Revision 1.11  2002/07/19 20:08:28  msell
 * Linux-porttausta
 *
 * Revision 1.10  2002/07/17 20:32:47  msell
 * Detail-optio toimii
 *
 * Revision 1.9  2002/07/15 15:22:08  msell
 * Parantelua
 *
 * Revision 1.8  2002/07/14 21:22:39  jkaarlas
 * skybox ja ukkojen säätö
 *
 * Revision 1.7  2002/07/10 17:13:44  msell
 * Törmäystarkastelun parantelua
 *
 * Revision 1.6  2002/07/07 17:53:21  msell
 * Legoukon alku
 *
 * Revision 1.5  2002/07/04 21:05:41  msell
 * Se toimii!! =)
 * Törmäystarkistukset siis
 *
 * Revision 1.4  2002/06/30 16:05:04  msell
 * Törmäyksien parantelua, transformaatioita mukana
 *
 * Revision 1.3  2002/06/26 22:30:29  jkaarlas
 * lisätty Vertexiin tekstuurikoordinaatit
 *
 * Revision 1.2  2002/06/24 14:12:15  msell
 * Nyt toimii sphere -> mesh -törmäykset, ihan tosi
 *
 * Revision 1.1  2002/06/20 22:50:12  msell
 * Meshit
 *
 *
 *
 * $Date: 2002/07/19 20:33:28 $
 *
 */

#ifndef __MESH_H_INCLUDED__
#define __MESH_H_INCLUDED__

#include "object.h"


#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2


class Vertex{
public:
	float position[3];
	float oldposition[3];
	float normal[3];
  float texcoords[2];

	Vertex(void);
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float nx, float ny, float nz);
  
	void setTexCoords(float u, float v);
};


class Edge;

class Polygon{
public:
	float planenormal[3];
	float planedistance;
	bool smooth;
	bool realsmooth;

	int vertexcount;
	Vertex **vertices;
	int edgecount;
	Edge **edges;

	Polygon(void);
};



class Edge{
public:
	Vertex *v1, *v2;
	class Polygon *p1, *p2;
};



class Mesh{
public:
	int vertexcount;
	Vertex *vertices;

	int polygoncount;
	class Polygon *polygons;

	Edge *edges;
	int edgecount;


	Mesh(void);
	~Mesh(void);

	void createPlanes(void);
	void createVertexnormals(void);
	void createEdges(void);
	float calculateScale(float targetLength, int axis);
	void scale(float targetLength, int axis);
  void scale(float scale);
};



class MeshObject : public Object{
public:
	Mesh *mesh;

	MeshObject(Mesh *mesh);
};



class MeshAppearance : public Appearance{
private:
	Mesh *mesh;

public:
	MeshAppearance(Mesh *mesh);

	void draw(void);
};



//Geometry of sphere

class MeshShape : public Shape{
private:
	Mesh *mesh;

public:
	MeshShape(MeshObject *meshobject);
	MeshShape(Object *object, Mesh *mesh);

	float calculateMomentOfInertia(float *rotationvector);

	bool checkCollision(Object *target);

	bool checkCollisionPeer(SphereShape *target);
	bool checkCollisionPeer(MeshShape *target);

	friend class SphereShape;
};

#endif

