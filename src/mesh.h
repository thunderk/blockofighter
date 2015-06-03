#ifndef __MESH_H_INCLUDED__
#define __MESH_H_INCLUDED__

#include "object.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

class Vertex {
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

class Polygon {
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

class Edge {
public:
  Vertex *v1, *v2;
  class Polygon *p1, *p2;
};

class Mesh {
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

class MeshObject : public Object {
public:
  Mesh *mesh;

  MeshObject(Mesh *mesh);
};

class MeshAppearance : public Appearance {
private:
  Mesh *mesh;

public:
  MeshAppearance(Mesh *mesh);

  void draw(void);
};

// Geometry of sphere

class MeshShape : public Shape {
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
