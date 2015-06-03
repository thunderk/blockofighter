#include "main.h"

#include "mesh.h"
#include "vector.h"
#include "sphere.h"
#include "collision.h"
#include "audio.h"

#include <math.h>

#include "glapi.h"

Vertex::Vertex(void) {
  vectorSet(position, 0, 0, 0);
  vectorSet(normal, 0, 0, 0);
}

Vertex::Vertex(float x, float y, float z) {
  vectorSet(position, x, y, z);
  vectorSet(normal, x, y, z);
  vectorNormalize(normal);
}

Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz) {
  vectorSet(position, x, y, z);
  vectorSet(normal, nx, ny, nz);
}

void Vertex::setTexCoords(float u, float v) {
  this->texcoords[0] = u;
  this->texcoords[1] = v;
}

Polygon::Polygon(void) {
  vertexcount = 0;
  edgecount = 0;
  smooth = false;
  realsmooth = false;
}

Mesh::Mesh(void) {
  vertexcount = 0;
  polygoncount = 0;
  edgecount = 0;
}

Mesh::~Mesh(void) {
  delete[] polygons;
  delete[] vertices;
}

void Mesh::createPlanes(void) {
  int i;
  for (i = 0; i < polygoncount; i++) {
    class Polygon *polygon = &this->polygons[i];
    if (polygon->vertexcount >= 3) {
      float v1[3], v2[3];
      vectorSub(v1, polygon->vertices[1]->position,
                polygon->vertices[0]->position);
      vectorSub(v2, polygon->vertices[2]->position,
                polygon->vertices[0]->position);
      vectorCross(polygon->planenormal, v1, v2);
      vectorNormalize(polygon->planenormal);

      polygon->planedistance =
          -vectorDot(polygon->vertices[0]->position, polygon->planenormal);
    }
  }
}

void Mesh::createVertexnormals(void) {
  int i, j, ii;
  bool connect;
  float normal[3];
  for (i = 0; i < vertexcount; i++) {
    bool found = false;
    vectorSet(normal, 0, 0, 0);
    for (j = 0; j < polygoncount; j++) {
      connect = false;
      class Polygon *polygon = &polygons[j];
      for (ii = 0; ii < polygon->vertexcount; ii++) {
        if (polygons[j].vertices[ii] == &(vertices[i])) {
          connect = true;
        }
      }
      if (connect) {
        vectorAdd(normal, polygon->planenormal);
        found = true;
      }
    }
    if (found) {
      vectorNormalize(vertices[i].normal, normal);
    }
  }
  for (j = 0; j < polygoncount; j++) {
    class Polygon *polygon = &polygons[j];
    if (!polygon->realsmooth)
      polygon->smooth = true;
  }
}

void Mesh::createEdges(void) {
  int maxedgecount = 0;
  int i;
  for (i = 0; i < polygoncount; i++) {
    class Polygon *polygon = &polygons[i];
    maxedgecount += polygon->vertexcount;
  }

  edgecount = 0;
  int j, k;
  Edge *edges = new Edge[maxedgecount];
  for (i = 0; i < polygoncount; i++) {
    class Polygon *polygon = &polygons[i];
    polygon->edges = new Edge *[polygon->vertexcount];
    for (j = 1; j <= polygon->vertexcount; j++) {
      Vertex *v1 = polygon->vertices[j - 1];
      Vertex *v2 = polygon->vertices[j % polygon->vertexcount];

      bool found = false;
      for (k = 0; k < edgecount; k++) {
        if (edges[k].v2 == v1 && edges[k].v1 == v2) {
          found = true;
          edges[k].p2 = polygon;
          break;
        }
      }

      if (!found) {
        edges[edgecount].v1 = v1;
        edges[edgecount].v2 = v2;
        edges[edgecount].p1 = polygon;
        edges[edgecount].p2 = NULL;
        edgecount++;
      }
    }
  }

  this->edges = new Edge[edgecount];
  // printf("%i\n", edgecount);
  for (i = 0; i < edgecount; i++) {
    this->edges[i].v1 = edges[i].v1;
    this->edges[i].v2 = edges[i].v2;
    this->edges[i].p1 = edges[i].p1;
    this->edges[i].p2 = edges[i].p2;

    class Polygon *p;
    p = edges[i].p1;
    p->edges[p->edgecount++] = &this->edges[i];
    p = edges[i].p2;
    p->edges[p->edgecount++] = &this->edges[i];
    // printf("%p, %p\n", edges[i].p1, edges[i].p2);
  }

  delete[] edges;
}

float Mesh::calculateScale(float targetLength, int axis) {

  float min = 0.0;
  float max = 0.0;

  for (int i = 0; i < this->vertexcount; i++) {
    if (this->vertices->position[axis] > max) {
      max = this->vertices->position[axis];
    }
    if (this->vertices->position[axis] < min) {
      min = this->vertices->position[axis];
    }
  }
  return fabs(targetLength / (max - min));
}

/* ei toimi kunnolla kaikille objekteille (kädet ok, jalat ja torso ei) */
void Mesh::scale(float targetLength, int axis) {
  float newscale = this->calculateScale(targetLength, axis);
  this->scale(newscale);
}

/* ei toimi kunnolla kaikille objekteille (kädet ok, jalat ja torso ei)*/
void Mesh::scale(float scale) {
  for (int i = 0; i < this->vertexcount; i++) {
    this->vertices->position[0] *= scale;
    this->vertices->position[1] *= scale;
    this->vertices->position[2] *= scale;
  }
  this->createVertexnormals();
  this->createPlanes();
}

MeshObject::MeshObject(Mesh *mesh) {
  this->mesh = mesh;
  this->appearance = new MeshAppearance(mesh);
  this->geometry = new MeshShape(this);
}

MeshAppearance::MeshAppearance(Mesh *mesh) { this->mesh = mesh; }

void MeshAppearance::draw(void) {
  // glDisable(GL_CULL_FACE);
  glColor4fv(this->material.getColor());
  this->material.enable();

  int i, j;

  for (i = 0; i < mesh->polygoncount; i++) {
    class Polygon *polygon = &mesh->polygons[i];

    glBegin(GL_TRIANGLE_FAN);

    if (!polygon->smooth)
      glNormal3fv(polygon->planenormal);

    for (j = 0; j < polygon->vertexcount; j++) {
      Vertex *vertex = polygon->vertices[j];

      if (polygon->smooth)
        glNormal3fv(vertex->normal);
      glVertex3fv(vertex->position);
    }

    glEnd();
  }

  glDisable(GL_DEPTH);
  glDisable(GL_LIGHTING);
  glLineWidth(5.0);
  glBegin(GL_LINES);
  for (i = 0; i < mesh->edgecount; i++) {
    glColor3f(0, 0, 0);
    glVertex3fv(mesh->edges[i].v1->position);
    glVertex3fv(mesh->edges[i].v2->position);
  }

  glEnd();
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH);

  this->material.disable();
  // glEnable(GL_CULL_FACE);
}

MeshShape::MeshShape(MeshObject *object) : Shape(object) {
  mesh = object->mesh;
}

MeshShape::MeshShape(Object *object, Mesh *mesh) : Shape(object) {
  this->mesh = mesh;
}

bool MeshShape::checkCollision(Object *target) {
  return target->geometry->checkCollisionPeer(this);
}

float MeshShape::calculateMomentOfInertia(float *rotationvector) {
  if (vectorDot(rotationvector, rotationvector) < EPSILON)
    return 0;
  int i;
  float j = 0;
  for (i = 0; i < mesh->vertexcount; i++) {
    float proj[3];
    vectorProject(proj, mesh->vertices[i].position, rotationvector);
    vectorSub(proj, mesh->vertices[i].position, proj);
    // float r = vectorLength(proj);
    float r2 = vectorDot(proj, proj);
    j += r2;
  }
  return j / i;
}

bool MeshShape::checkCollisionPeer(SphereShape *target) {
  float position[3] = {0, 0, 0};
  target->object->transformPoint(position, position);
  object->unTransformPoint(position, position);

  float normal[3];
  float contactpoint[3];
  float r = target->getRadius();

  if (checkSphereMeshCollision(position, r, mesh, normal, contactpoint)) {
    vectorScale(normal, -1);
    object->transformVector(normal, normal);
    object->transformPoint(contactpoint, contactpoint);

    addCollision(object, target->object, normal, contactpoint);

    // vectorAdd(contactnormal, normal);

    return true;
  }

  return false;
}

// extern Sound *shotsound;

bool MeshShape::checkCollisionPeer(MeshShape *target) {
  float normal[3];
  float contactpoint[3];

  bool collided = false;

  int i;

  Mesh *sourcemesh, *targetmesh;

  sourcemesh = this->mesh;
  targetmesh = target->mesh;
  for (i = 0; i < sourcemesh->vertexcount; i++) {
    Vertex *vertex = &sourcemesh->vertices[i];
    float vertexposition[3];
    object->transformPoint(vertexposition, vertex->position);
    target->object->unTransformPoint(vertexposition, vertexposition);

    if (checkPointMeshCollision(vertexposition, targetmesh, normal,
                                contactpoint)) {
      target->object->transformVector(normal, normal);
      target->object->transformPoint(contactpoint, contactpoint);

      if (vectorIsZero(contactpoint)) {
        vectorSet(contactpoint, 0, 0, 0);
      }
      addCollision(object, target->object, normal, contactpoint);
      collided = true;
    }
  }

  sourcemesh = target->mesh;
  targetmesh = this->mesh;
  for (i = 0; i < sourcemesh->vertexcount; i++) {
    Vertex *vertex = &sourcemesh->vertices[i];
    float vertexposition[3];
    target->object->transformPoint(vertexposition, vertex->position);
    object->unTransformPoint(vertexposition, vertexposition);

    if (checkPointMeshCollision(vertexposition, targetmesh, normal,
                                contactpoint)) {
      object->transformVector(normal, normal);
      object->transformPoint(contactpoint, contactpoint);

      addCollision(target->object, object, normal, contactpoint);
      collided = true;
    }
  }

  sourcemesh = this->mesh;
  targetmesh = target->mesh;
  for (i = 0; i < sourcemesh->edgecount; i++) {
    Edge *edge = &sourcemesh->edges[i];
    float v1[3], v2[3];
    object->transformPoint(v1, edge->v1->position);
    target->object->unTransformPoint(v1, v1);

    object->transformPoint(v2, edge->v2->position);
    target->object->unTransformPoint(v2, v2);

    if (checkEdgeMeshCollision(v1, v2, targetmesh, normal, contactpoint)) {
      target->object->transformVector(normal, normal);
      target->object->transformPoint(contactpoint, contactpoint);

      addCollision(object, target->object, normal, contactpoint);
      collided = true;
    }
  }

  return collided;
}
